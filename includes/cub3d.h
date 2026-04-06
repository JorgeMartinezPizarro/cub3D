/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:36:37 by jomarti3          #+#    #+#             */
/*   Updated: 2026/04/06 17:45:24 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

// WINDOW
# define WIDTH 2000
# define HEIGHT 1200
# define MAX_MAP_SIZE 100

// PLAYER
# define HAND_WIDTH 192
# define HAND_HEIGHT 128
# define PLAYER_RADIUS 0.1

// KEYS
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define KEY_E 101
# define KEY_M 109

// GAME SPEED
# define MOVE_SPEED 0.07
# define ROT_SPEED  0.051
# define FPS 30
# define MOUSE_SENS 0.00095

// MINIMAPA
# define MM_SCALE 4
# define MM_OFFSET_X 10
# define MM_OFFSET_Y 10
# define MINIMAP_RADIUS 16
# define COLOR_WALL   0x00FFFFFF
# define COLOR_EMPTY  0x00333333
# define COLOR_PLAYER 0x00FF0000

// ENUM FOR MAP
# define TILE_EMPTY			0
# define TILE_WALL			1
# define TILE_DOOR			2
# define TILE_DOOR_OPEN   	3
# define TILE_DOOR_HALF		4

typedef enum e_error
{
	ERR_MALLOC,
	ERR_EXTENSION,
	ERR_OPEN_FILE,
	ERR_DUP_TEXTURE,
	ERR_EMPTY_LINE,
	ERR_DUP_COLOR,
	ERR_BAD_COLOR,
	ERR_COLOR_RANGE,
	ERR_MISSING_ELEMENT,
	ERR_INVALID_CHAR,
	ERR_INVALID_SPAWN,
	ERR_MAP_NOT_FOUND,
	ERR_MAP_NOT_CLOSED,
	ERR_INVALID_LINE,
	ERR_MAP_TOO_LONG,
	ERR_COUNT
}	t_error;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor[3];
	int		sky[3];
	char	**map;
	int		height;
	int		width;
	double	x_spawn;
	double	y_spawn;
	double	spawn_angle;
	int		no_flag;
	int		so_flag;
	int		we_flag;
	int		ea_flag;
	int		f_flag;
	int		c_flag;
}	t_config;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
	int			w;
	int			h;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	double		mouse_x;
	double		mouse_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		hand_sheet;
	t_img		frame;
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
	t_img		door_open;
	t_img		door_half;
	t_img		door_closed;
	t_player	p;
	int			**world;
	int			height;
	int			width;
	int			current_hand_frame;
	int			keys[65536];
	int			mouse_x_diff;
	int			mouse_lock;
	int			mouse_x;
	int			mouse_y;
	int			old_mouse_x;
	long long	last_time;
	int			ceiling_color;
	int			floor_color;
	long long	last_hand_time;
	int			door_x;
	int			door_y;
	int			door_opening;
	int			mouse_enable;
	long long	door_time;
}	t_game;

typedef struct s_charview
{
	int	tex_x;
	int	tex_y;
	int	screen_x;
	int	screen_y;
}	t_charview;

typedef struct s_ray
{
	double	cam_dist;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	dist;
	double	hit_x;
	double	hit_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit_type;
}	t_ray;

typedef struct s_column
{
	int		x;
	int		start;
	int		end;
	int		wall_h;
	double	wall_x;
	t_img	*tex;
}	t_column;

void		render_minimap(t_game *g);
void		put_pixel(t_img *img, int x, int y, int c);
void		free_game(t_game *game);
void		free_strarr(char **res, int i);
void		ft_free_config(t_config *config);
void		drain_fd(int fd);

int			ft_add_map_line(t_config *config, char *line);
int			ft_parse_texture(char **texture, int *flag, char *line);
int			ft_parse_color(int *color, int *flag, char *line);
int			ft_check_cell(t_config *config, int x, int y, int *spawn_count);
int			ft_validate_map(t_config *config);
int			ft_config_to_game(t_config *config, t_game *game);
void		ft_set_spawn(t_config *config, int x, int y, char c);
t_config	*ft_init_config(void);
int			ft_check_all_flags(t_config *config);
int			ft_check_extension(char *filename);
int			ft_validate_config(t_config *config);
t_config	*ft_parse_cub_file(char *filename);
int			ft_print_errors(t_error err);
void		ft_toggle_door(t_game *g);

int			key_press(int k, t_game *g);
int			key_release(int k, t_game *g);
long long	get_time(void);
void		normalize_angle(double *angle);
int			get_pixel(t_img *tex, int x, int y);
int			rgb_to_hex(int *rgb);
int			exit_program(t_game *g);

double		cast_ray(t_game *g, t_ray *ray);
void		draw_hand_frame(t_game *g, t_img *sheet, int frame_idx);

void		load_handlers(t_game *g);
int			load_game(char *filename, t_game *g);

int			game_loop(t_game *g);
void		render(t_game *g);
void		ft_draw_crosshair(t_game *g);
void		ft_update_doors(t_game *g);

void		toggle_mouse(t_game *g, int enable);

#endif