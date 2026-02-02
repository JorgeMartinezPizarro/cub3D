#include "cub3d.h"
#include <math.h>
#include <stdlib.h>

/* --- FUNCIONES DE APOYO --- */

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
    render_minimap(g);
    mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}

/* --- HANDLERS DE EVENTOS --- */

int mouse_move(int x, int y, t_game *g)
{
    (void)y;
    if (x == WIDTH / 2)
        return (0);
    g->mouse_x_diff = x - (WIDTH / 2);
    return (0);
}

int game_loop(t_game *g)
{
    if (g->mouse_x_diff != 0)
    {
        g->p.angle += g->mouse_x_diff * 0.002;
        normalize_angle(&g->p.angle);
        g->mouse_x_diff = 0;
        mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
    }
    render(g);
    return (0);
}

void	move_player(t_game *g, double dx, double dy)
{
	double	margin_x;
	double	margin_y;

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

int key(int k, t_game *g)
{
	if (k == KEY_ESC)
        exit(0);
    if (k == KEY_LEFT)
        g->p.angle -= ROT_SPEED;
    else if (k == KEY_RIGHT)
        g->p.angle += ROT_SPEED;
    else if (k == KEY_W)
        move_player(g, cos(g->p.angle) * MOVE_SPEED, sin(g->p.angle) * MOVE_SPEED);
    else if (k == KEY_S)
        move_player(g, -cos(g->p.angle) * MOVE_SPEED, -sin(g->p.angle) * MOVE_SPEED);
    else if (k == KEY_A)
        move_player(g, sin(g->p.angle) * MOVE_SPEED, -cos(g->p.angle) * MOVE_SPEED);
    else if (k == KEY_D)
        move_player(g, -sin(g->p.angle) * MOVE_SPEED, cos(g->p.angle) * MOVE_SPEED);
    normalize_angle(&g->p.angle);
    return (0);
}

/* --- MAIN Y CARGA --- */

void    load_tex(t_game *g, t_img *t, char *path)
{
    t->img = mlx_xpm_file_to_image(g->mlx, path, &t->w, &t->h);
    if (!t->img) exit((write(2, "Error texture\n", 14), 1));
    t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line, &t->endian);
}

int main(void)
{
    t_game  g;

    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Cub3D");
    g.frame.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
    g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp, &g.frame.line, &g.frame.endian);
	g.mouse_x_diff = 0;
    if (!load_map("", &g)) return (1);
    
    load_tex(&g, &g.wall_north, "textures/wall_north.xpm");
    load_tex(&g, &g.wall_south, "textures/wall_south.xpm");
    load_tex(&g, &g.wall_east, "textures/wall_east.xpm");
    load_tex(&g, &g.wall_west, "textures/wall_west.xpm");

    // Ocultar el ratón para mejor experiencia
    mlx_mouse_hide(g.mlx, g.win);
    // Moverlo al centro antes de empezar
    mlx_mouse_move(g.mlx, g.win, WIDTH / 2, HEIGHT / 2);

    mlx_hook(g.win, 2, 1L << 0, key, &g);
    mlx_hook(g.win, 6, 1L << 6, mouse_move, &g); // MotionNotify hook
    mlx_loop_hook(g.mlx, game_loop, &g);
    
    mlx_loop(g.mlx);
    return (0);
}