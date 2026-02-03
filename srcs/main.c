#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

/* --- FUNCIONES DE APOYO --- */


int key_press(int k, t_game *g)
{
    if (k == KEY_ESC) exit(0);
    if (k < 65536) g->keys[k] = 1;
    return (0);
}

int key_release(int k, t_game *g)
{
    if (k < 65536) g->keys[k] = 0;
    return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    normalize_angle(double *angle)
{
    while (*angle < 0)
        *angle += 2 * M_PI;
    while (*angle >= 2 * M_PI)
        *angle -= 2 * M_PI;
}

int get_tex_pixel(t_img *tex, int x, int y)
{
    if (x < 0 || x >= tex->w || y < 0 || y >= tex->h)
        return (0);
    return (*(unsigned int *)(tex->addr + y * tex->line + x * (tex->bpp / 8)));
}

/* --- RAYCASTING Y RENDER --- */

double cast_ray(t_game *g, double angle, double *hitx, double *hity, int *side)
{
    double raydir_x = cos(angle);
    double raydir_y = sin(angle);
    int map_x = (int)g->p.x;
    int map_y = (int)g->p.y;
    double delta_dist_x = fabs(1.0 / raydir_x);
    double delta_dist_y = fabs(1.0 / raydir_y);
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int hit = 0;
    int dda_side;

    if (raydir_x < 0) {
        step_x = -1;
        side_dist_x = (g->p.x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - g->p.x) * delta_dist_x;
    }
    if (raydir_y < 0) {
        step_y = -1;
        side_dist_y = (g->p.y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - g->p.y) * delta_dist_y;
    }
    while (!hit) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            dda_side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            dda_side = 1;
        }
        if (g->world[map_y][map_x] == 1)
            hit = 1;
    }
    double perp_dist;
    if (dda_side == 0)
        perp_dist = (map_x - g->p.x + (1 - step_x) / 2) / raydir_x;
    else
        perp_dist = (map_y - g->p.y + (1 - step_y) / 2) / raydir_y;
    *hitx = g->p.x + perp_dist * raydir_x;
    *hity = g->p.y + perp_dist * raydir_y;
    if (dda_side == 0)
        *side = (raydir_x > 0) ? 2 : 3;
    else
        *side = (raydir_y > 0) ? 1 : 0;
    return (perp_dist);
}

void    draw_column(t_game *g, int x, int start, int end, t_img *tex, double wall_x, int wall_h)
{
    int y;
    int tex_x = (int)(wall_x * tex->w);
    y = 0;
    while (y < start)
        put_pixel(&g->frame, x, y++, CEILING_COLOR);
    while (y < end)
    {
        int tex_y = (y - (HEIGHT / 2 - wall_h / 2)) * tex->h / wall_h;
        put_pixel(&g->frame, x, y++, get_tex_pixel(tex, tex_x, tex_y));
    }
    while (y < HEIGHT)
        put_pixel(&g->frame, x, y++, FLOOR_COLOR);
}

void draw_hand_frame(t_game *g, t_img *sheet, int frame_idx, int offset_y)
{
    int x;
    int y;
    int color;

	// Dimensiones de un solo frame (un cuarto de la imagen total)
    int f_w = 192; 
    int f_h = 128;

    // Calculamos la posición inicial en el XPM (Grid 2x2)
    // frame_idx % 2 nos da la columna (0 o 1)
    // frame_idx / 2 nos da la fila (0 o 1)
    int tex_start_x = (frame_idx % 2) * f_w;
    int tex_start_y = (frame_idx / 2) * f_h;
    
    // Posición en pantalla (centrado horizontal, abajo vertical)
    int screen_x = (WIDTH / 2) - (f_w / 2);
    int screen_y = HEIGHT - f_h + offset_y;

    y = 0;
    while (y < f_h) // Solo recorremos el ALTO de un frame
    {
        x = 0;
        while (x < f_w) // Solo recorremos el ANCHO de un frame
        {
            // Leemos sumando los offsets de fila y columna
            color = get_tex_pixel(sheet, tex_start_x + x, tex_start_y + y);
            
            // Dibujamos solo si no es transparente y está dentro de la pantalla
            if (color != 0x000000 && color > 0)
            {
                put_pixel(&g->frame, screen_x + x, screen_y + y, color);
            }
            x++;
        }
        y++;
    }
}

void    render(t_game *g)
{
    int     x = 0;
    double  fov = M_PI / 3.0;

    while (x < WIDTH)
    {
        double ray_angle = g->p.angle - fov / 2 + (double)x / WIDTH * fov;
        double hx, hy;
        int side;
        double ray_dist = cast_ray(g, ray_angle, &hx, &hy, &side);
        double cam_dist = ray_dist * cos(ray_angle - g->p.angle);
        
        if (cam_dist <= 0.1) cam_dist = 0.1;
        int wall_h = (int)(HEIGHT / cam_dist);
        int start = HEIGHT / 2 - wall_h / 2;
        int end = HEIGHT / 2 + wall_h / 2;

        if (start < 0) start = 0;
        if (end >= HEIGHT) end = HEIGHT - 1;

        t_img *tex;
        double wall_x = (side == 0 || side == 1) ? hx : hy;
        if (side == 0) tex = &g->wall_north;
        else if (side == 1) tex = &g->wall_south;
        else if (side == 2) tex = &g->wall_east;
        else tex = &g->wall_west;

        wall_x -= floor(wall_x);
        draw_column(g, x, start, end, tex, wall_x, wall_h);
        x++;
    }
	draw_hand_frame(g, &g->hand_sheet, g->current_hand_frame, 20);
    render_minimap(g);
	
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	
}

/* --- HANDLERS DE EVENTOS --- */

int mouse_move(int x, int y, t_game *g)
{
    (void)y;
    g->mouse_x = x;
    return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double	margin_x;
	double	margin_y;

	if (get_time() % 7 == 0)
		g->current_hand_frame = (g->current_hand_frame + 1) % 4;
	if (dx > 0)
		margin_x = PLAYER_RADIUS;
	else
		margin_x = -PLAYER_RADIUS;
	if (dy > 0)
		margin_y = PLAYER_RADIUS;
	else
		margin_y = -PLAYER_RADIUS;
	if (g->world[(int)g->p.y][(int)(g->p.x + dx + margin_x)] == 0)
		g->p.x += dx;
	if (g->world[(int)(g->p.y + dy + margin_y)][(int)g->p.x] == 0)
		g->p.y += dy;
}

void apply_movement(t_game *g)
{
    if (g->keys[KEY_W])
        move_player(g, cos(g->p.angle) * MOVE_SPEED, sin(g->p.angle) * MOVE_SPEED);
    if (g->keys[KEY_S])
        move_player(g, -cos(g->p.angle) * MOVE_SPEED, -sin(g->p.angle) * MOVE_SPEED);
    if (g->keys[KEY_A])
        move_player(g, sin(g->p.angle) * MOVE_SPEED, -cos(g->p.angle) * MOVE_SPEED);
    if (g->keys[KEY_D])
        move_player(g, -sin(g->p.angle) * MOVE_SPEED, cos(g->p.angle) * MOVE_SPEED);
    if (g->keys[KEY_LEFT])
        g->p.angle -= ROT_SPEED;
    if (g->keys[KEY_RIGHT])
        g->p.angle += ROT_SPEED;
    normalize_angle(&g->p.angle);
}

/* --- LOOP PRINCIPAL ACTUALIZADO --- */

int game_loop(t_game *g)
{
    static long long last_time = 0;
    long long now = get_time();

    if (now - last_time < 1000 / 60) return (0);
    last_time = now;

    apply_movement(g);

    // --- LÓGICA DE MOVIMIENTO RELATIVO ---
    // Si es la primera vez que entramos, inicializamos old_mouse_x
    if (g->old_mouse_x == 0) 
        g->old_mouse_x = g->mouse_x;

    if (g->mouse_x != g->old_mouse_x)
    {
        int delta_x = g->mouse_x - g->old_mouse_x;

        // Si el salto es demasiado grande (ej: el ratón entra/sale de la ventana)
        // lo ignoramos para evitar que la cámara dé un latigazo.
        if (abs(delta_x) < 200) 
        {
            g->p.angle += delta_x * SENSIBILITY;
            normalize_angle(&g->p.angle);
        }
        
        // Guardamos la posición actual para el próximo frame
        g->old_mouse_x = g->mouse_x;
    }

    render(g);
    return (0);
}
/* --- MAIN Y CARGA --- */

void    load_tex(t_game *g, t_img *t, char *path)
{
    t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
    if (!t->img) exit((write(2, "Error texture\n", 14), 1));
    t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
}

int	exit_program(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	free_game(g);
	exit(0);
	return (0);
}
int main(void)
{
    t_game  g;

	ft_memset(&g, 0, sizeof(t_game));
    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Cub3D");

	g.p.mouse_x = WIDTH / 2;
    g.p.mouse_y = HEIGHT / 2;
	g.current_hand_frame = 0;
    g.frame.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
    g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp, &g.frame.line, &g.frame.endian);
	
	if (!load_map("", &g)) return (1);
    
    load_tex(&g, &g.wall_north, "textures/wall_north.xpm");
    load_tex(&g, &g.wall_south, "textures/wall_south.xpm");
    load_tex(&g, &g.wall_east, "textures/wall_east.xpm");
    load_tex(&g, &g.wall_west, "textures/wall_west.xpm");
	load_tex(&g, &g.hand_sheet, "textures/arms.xpm");

    // Moverlo al centro antes de empezar
    mlx_mouse_move(g.mlx, g.win, WIDTH / 2, HEIGHT / 2);
	// Ocultar el ratón para mejor experiencia
    //mlx_mouse_hide(g.mlx, g.win);
    mlx_hook(g.win, 2, 1L << 0, key_press, &g);   // Detecta cuando pulsas
	mlx_hook(g.win, 3, 1L << 1, key_release, &g); // Detecta cuando sueltas
    mlx_hook(g.win, 6, 1L << 6, mouse_move, &g); // MotionNotify hook

	mlx_hook(g.win, 17, 0, exit_program, &g);

    mlx_loop_hook(g.mlx, game_loop, &g);
    
    mlx_loop(g.mlx);
    return (0);
}