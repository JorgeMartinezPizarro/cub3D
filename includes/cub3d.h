#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
#include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600
# define TEX 64

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define PLAYER_RADIUS 0.2
# define MOVE_SPEED 0.029
# define ROT_SPEED  0.039
# define SENSIBILITY 0.0003
# define MINIMAP_RADIUS 15

# define FLOOR_COLOR 0x444444
# define CEILING_COLOR 0xAAAAAA

#define MM_SCALE 4      // tamaño de cada celda en píxeles
#define MM_OFFSET_X 10  // margen desde la izquierda
#define MM_OFFSET_Y 10  // margen desde arriba

#define COLOR_WALL   0x00FFFFFF
#define COLOR_EMPTY  0x00333333
#define COLOR_PLAYER 0x00FF0000

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	
	/*colors*/
	int		floor[3];
	int		sky[3];
	int		**map;
	int		height;
	int		width;
	// Usamos t_game->t_player para estas variables
	double	x_spawn;
	double	y_spawn;
	double	spawn_angle;
	/*flags*/
	int		no_flag;
	int		so_flag;
	int		we_flag;
	int		ea_flag;
	int		f_flag;
	int		c_flag;

} t_config;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double		mouse_x;
	double		mouse_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
	t_player	p;
	int			**world;
	int			height;
	int			width;
	int			keys[65536]; // Array para estados de teclas
	double		mouse_x_diff;
}	t_game;

int		load_map(char *filename, t_game *game);
void	render_minimap(t_game *g);
void	put_pixel(t_img *img, int x, int y, int c);
void	free_game(t_game *game);

# endif