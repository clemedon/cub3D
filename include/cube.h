/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:50:59 by athirion          #+#    #+#             */
/*   Updated: 2022/11/15 12:38:04 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

/*
 ** =========[ Includes ]==========
 */

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <float.h>
# include <math.h>

/*
 ** =========[ Defines ]===========
 */

# define TEX_NUM	4
# define TEX_IDS	"NOSOWEEA"
# define COL_NUM	2
# define COL_IDS	"FC"

# define MAP_VALID	"NSEW 01"
# define MAP_INNER	"NSEW01"
# define MAP_SPAWN	"NSEW"
# define MAP_OUTER	" 1"
# define MAP_ROOM	"0"
# define MAP_WALL	"1"

# define ER_USAGE	"Error\nUsage: ./cub3D <path_to_cub_file>.cub"
# define ER_SPECS	"Error\nCub file is not valid"

/* Key codes */
# define ESCAPE		65307
# define MOVE_FRONT	119
# define MOVE_BACK	115
# define MOVE_LEFT	100
# define MOVE_RIGHT	97
# define TURN_LEFT	65361
# define TURN_RIGHT	65363
# define MINIMAP	109
# define RAY		114
# define HELP		104

/* Map constants */

# define TILE_SIZE	64
# define MAP_SCALE	0.5
# define MINIMAP_SIZE 32

/* Window dimensions */
# define WIN_HEIGHT	1200
# define WIN_WIDTH	1600

/* Player constants */
# define LEFT		-1
# define RIGHT		1
# define BACK		-1
# define FRONT		1
# define TURN_SPEED	0.09
# define WALK_SPEED	18

/* Math constants */

# define PI 		3.14159
# define TWO_PI 	6.28318

# define FOV 		1.047196667
# define NUM_RAYS	WIN_WIDTH

/*
 ** =========[ Enum ]==============
 */

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

typedef enum e_texture
{
	NO,
	SO,
	WE,
	EA
}	t_texture;

typedef enum e_map
{
	VOID = -1,
	ROOM,
	WALL,
	N,
	S,
	E,
	W
}	t_map;

/*
 ** =========[ Struct ]============
 */

typedef struct s_text
{
	void	*img;
	char	*addr;
	char	*texel;
	int		bpp;
	int		endian;
	int		line_length;
	int		w;
	int		h;
	char	*path;
}	t_text;

typedef struct s_cub
{
	int				minimap;
	int				ray;
	const char		**specs;
	int				width;
	int				height;
	int				**map;
	unsigned long	f_color_hex;
	unsigned long	c_color_hex;
	t_text			texture[4];
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
}	t_cub;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*addr;
	int		bpp;
	int		endian;
	int		line_length;
}	t_mlx;

typedef struct s_minimap
{
	t_mlx	mlx;
	int		rays;
}	t_minimap;

typedef struct s_point
{
	double	x;
	double	y;
	int		color;
}	t_point;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	d_start;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	int		side_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct s_proj
{
	int		y;
	int		offset[2];
	int		dist_top;
	float	wall_strip_height;
	float	dist_proj_plane;
	float	proj_wall_height;
	float	perpendicular_dist;
	t_point	top_wall;
	t_point	bottom_wall;
}	t_proj;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_right;
	int		ray_facing_left;
	int		wall_hit_content;
	int		was_hit_vertical;
}	t_ray;

typedef struct s_cast
{
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_right;
	int		ray_facing_left;
	float	x_inter;
	float	y_inter;
	float	x_step;
	float	y_step;
	float	current_x;
	float	current_y;
	float	next_horizontal_x;
	float	next_horizontal_y;
	float	next_vertical_y;
	float	next_vertical_x;
	int		horizontal_hit;
	float	horizontal_hit_x;
	float	horizontal_hit_y;
	int		horizontal_content;
	int		vertical_hit;
	float	vertical_hit_x;
	float	vertical_hit_y;
	int		vertical_content;
	float	horizontal_dist;
	float	vertical_dist;
}	t_cast;

typedef struct s_data
{
	t_cub		cub;
	t_minimap	minimap;
	t_player	player;
	t_ray		rays[NUM_RAYS];
	t_mlx		mlx;
}	t_data;

/*
 ** =========[ Proto ]=============
 */

/*
 ** utils/utils.c
 */

char			**ft_gridify(const char **tab, int width, int height);
int				ft_open(const char *file);
unsigned long	ft_create_rgb(int r, int g, int b);
void			ft_exit_error(const char *func, const char *strerror);
void			ft_quit(t_data *data);

/*
 ** utils/strutils.c
 */

char			*ft_replace_char(char *str, char find, char replace);
int				ft_strtab_height(const char **tab);
int				ft_strtab_width(const char **tab);
t_bool			ft_str_onlywith(const char *str, const char *charset);
t_bool			ft_strcharset(const char *str, const char *charset);

/*
 ** minimap.c
 */

void			ft_free_minimap(t_minimap *minimap);
void			ft_pre_init_minimap(t_data *data);
/* int			ft_init_minimap(t_data *data, t_minimap *minimap); */
/* int			ft_render_minimap(t_data *data, t_minimap *minimap); */
void			ft_minimap(t_data *data);

/*
 ** projection.c
 */

/* void			ft_draw_ceiling(t_data *data); */
/* void			ft_draw_floor(t_data *data); */
/* void			ft_init_cast(t_data *data, t_ray *ray, t_proj *p, t_text *t); */
/* t_text		ft_choose_texture(t_ray *ray, t_cub *cub); */
void			ft_3d_projection(t_data *data);

/*
 ** rays_utils.c
 */

float			ft_normalize_angle(float angle);
float			ft_dist(float p_x, float p_y, float hit_x, float hit_y);
void			ft_get_ray_orientation(t_cast *c, float ray_angle);
void			ft_set_dist(t_data *data, t_cast *c);
void			ft_dist_cmp(t_cast *c, t_ray *ray, float ray_angle);

/*
 ** rays_hit.c
 */

int				ft_is_wall(t_data *data, float x, float y);
void			ft_horizontal_step(t_data *data, float ray_angle, t_cast *c);
void			ft_horizontal_hit(t_data *data, t_cast *c);
void			ft_vertical_step(t_data *data, float ray_angle, t_cast *c);
void			ft_vertical_hit(t_data *data, t_cast *c);

/*
 ** rays.c
 */

/* void			ft_cast_ray(t_data *data, float ray_angle, t_ray *ray); */
void			ft_cast_all_rays(t_data *data);

/*
 ** player.c
 */

/* void			ft_side_move(t_data *data, t_point *p); */
/* void			ft_oblique_move(t_data *data, t_point *p); */
/* void			ft_straight_move(t_data *data, t_point *p); */
int				ft_move_player(t_data *data);

/*
 ** event.c
 */

void			ft_key_event(int key, t_data *data);
void			ft_key_release(int key, t_data *data);
void			ft_mouse_event(t_data *data);

/*
 ** draw.c
 */

void			ft_draw_mini_map(t_data *data, t_minimap *minimap);
void			ft_draw_rays(t_data *data, t_minimap *minimap);
void			ft_draw_player(t_data *data, t_minimap *minimap);
int				ft_render(t_data *data);

/*
 ** draw_utils.c
 */

void			ft_my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			ft_draw_line(t_mlx *mlx, t_point begin, t_point end);
void			ft_draw_rect(t_mlx *mlx, t_point start, int width, int height);
void			ft_draw_circle(t_mlx *mlx, t_point center, double radius);

/*
 ** init/init_rays.c
 */

void			ft_init_rays(t_data *data);

/*
 ** init/init_player.c
 */

/* void 		ft_get_player_position(t_data *data); */
/* void 		ft_get_player_orientation(t_data *data); */
void			ft_init_player(t_data *data);

/*
 ** init/init_texture.c
 */

void			ft_free_texture(t_cub *cub, t_mlx *mlx);
/* void			ft_pre_init_texture(t_cub *cub); */
t_bool			ft_init_texture(t_cub *cub, t_mlx *mlx);

/*
 ** init/init_mlx.c
 */

void			ft_free_mlx(t_mlx *mlx);
/* void			ft_pre_init_mlx(t_mlx *mlx); */
int				ft_init_mlx(t_mlx *mlx);

/*
 ** init/init_cub_attr.c
 */

/* char 		**ft_extract_rgb_val(const char *color); */
t_bool			ft_init_cub_color(t_cub *cub, const char **specs);
t_bool			ft_init_cub_texture(t_cub *cub, const char **specs);

/*
 ** init/init_cub_map.c
 */

/* int  		*ft_maprow_to_int(const char *maprow, int *row, int width); */
/* int  		**ft_map_to_int(const char **charmap, int width, int height); */
t_bool			ft_init_cub_map(t_cub *cub, const char **specs);

/*
 ** init/init_cub.c
 */

void			ft_free_cub(t_cub *cub);
/* void			ft_pre_init_cub(t_cub *cub); */
t_bool			ft_init_cub(t_cub *cub, const char **specs);

/*
 ** init/init.c
 */

t_bool			ft_init(t_data *data, const char **specs);

/*
 ** check_cub/check_map_2.c
 */

/* t_bool		ft_check_map_enclosure_2(char **map, int x, int y); */
t_bool			ft_check_map_enclosure(char **map, int width, int height);

/*
 ** check_cub/check_map.c
 */

/* t_bool		ft_check_map_limits(const char **map); */
/* t_bool		ft_check_map_spawn(const char **map); */
/* t_bool		ft_check_map_global(const char **map); */
t_bool			ft_check_map(const char **specs);

/*
 ** check_cub/check_tex.c
 */

/* t_bool		ft_check_tex_value(const char *specs); */
/* t_bool		ft_check_tex_ids(const char **specs); */
t_bool			ft_check_tex(const char **specs);

/*
 ** check_cub/check_col.c
 */

/* t_bool		ft_check_col_value(const char *specs); */
/* t_bool		ft_check_col_ids(const char **specs); */
t_bool			ft_check_col(const char **specs);

/*
 ** check_cub/check_cub.c
 */

/* t_bool		ft_check_cub_elements(const char **specs); */
t_bool			ft_check_cub(const char **specs);

/*
 ** load.c
 */

/* int			ft_line_counter(char *file); */
const char		**ft_load_cub(char *file);

/*
 ** main.c
 */

/* void			ft_check_arg(const char *arg); */
int				main(int argc, char **argv);

#endif
