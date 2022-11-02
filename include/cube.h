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

/* Map constants */

# define ROWS		13
# define COLS		20
# define TILE_SIZE	64
# define MAP_SCALE	0.2

/* Window dimensions */
# define WIN_HEIGHT	(ROWS * TILE_SIZE)
# define WIN_WIDTH	(COLS * TILE_SIZE)

/* Player direction */
# define LEFT		-1
# define RIGHT		1
# define BACK		-1
# define FRONT		1

/* Player position */
/* # define N			2 */
/* # define S			3 */
/* # define E			4 */
/* # define W			5 */

/* Math constants */

# define PI 		M_PI
# define TWO_PI 	M_PI * 2

# define FOV 		(60 * (PI / 180))
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

typedef struct s_cub
{
	const char		**specs;
	int				width;
	int				height;
	int				**map;
	unsigned long	f_color_hex;
	unsigned long	c_color_hex;
	int				n_texture_fd;
	int				s_texture_fd;
	int				w_texture_fd;
	int				e_texture_fd;
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
	t_player	player;
	t_ray		rays[NUM_RAYS];
	t_mlx		mlx;
}	t_data;

/*
 ** =========[ Proto ]=============
 */

/*
 ** utils.c
 */

unsigned long	ft_create_rgb(int r, int g, int b);
void			ft_print_chartab(const char **tab); // XXX
void			ft_print_inttab(int **tab, int width, int height); // XXX
void			ft_print_readable_map(int **map, int width, int height);
int				ft_return_msg(const char *message, int retval);
char			**ft_gridify(const char **tab, int width, int height);
size_t			ft_strchr_count(char const *s, int c); // XXX
void			ft_exit_error(const char *func, const char *strerror);
int				ft_open(const char *file);
t_bool			ft_strcharset(const char *str, const char *charset);
t_bool			ft_str_onlywith(const char *str, const char *charset);
char			*ft_replace_char(char *str, char find, char replace);
int				ft_strtab_height(const char **tab);
int				ft_strtab_width(const char **tab);

/*
 ** check_cub/
 */

/* t_bool		ft_check_map_enclosure(char **map, int width, int height); */
/* t_bool		ft_check_map_limits(const char **map); */
/* t_bool		ft_check_map_spawn(const char **map); */
/* t_bool		ft_check_map_global(const char **map); */
t_bool			ft_check_map(const char **specs);

/* t_bool		ft_check_tex_value(const char *specs); */
t_bool			ft_check_tex(const char **specs);

/* t_bool		ft_check_col_value(const char *specs); */
t_bool			ft_check_col(const char **specs);

t_bool			ft_check_cub(const char **specs);

/*
 ** wall.c
 */

int				ft_is_wall(t_data *data, float x, float y);

/*
 ** projection.c
 */

void			ft_3d_projection(t_data *data);

/*
 ** rays.c
 */

/* float ft_normalize_angle(float angle); */
/* float ft_dist(float player_x, float player_y, float hit_x, float hit_y); */
/* void			ft_get_ray_orientation(t_cast *c, float ray_angle); */
/* void			ft_horizontal_step(t_data *data, float ray_angle, t_cast *c); */
/* void			ft_horizontal_hit(t_data *data, t_cast *c); */
/* void			ft_vertical_step(t_data *data, float ray_angle, t_cast *c); */
/* void			ft_vertical_hit(t_data *data, t_cast *c); */
/* void			ft_set_dist(t_data *data, t_cast *c); */
/* void			ft_dist_cmp(t_cast *c, t_ray *ray, float ray_angle); */
/* void			ft_cast_ray(t_data *data, float ray_angle, t_ray *ray); */
void			ft_cast_all_rays(t_data *data);

/*
 ** player.c
 */

void			ft_move_up(t_data *data);
void			ft_move_down(t_data *data);
void			ft_move_left(t_data *data);
void			ft_move_right(t_data *data);
void			ft_turn_left(t_data *data);
void			ft_turn_right(t_data *data);
void			ft_side_move(t_data *data);
void			ft_move_player(t_data *data);

/*
 ** quit.c
 */

void			ft_quit(t_data *data);

/*
 ** event.c
 */

void			ft_key_event(int key, t_data *data);
void			ft_mouse_event(t_data *data);
int				ft_waiting_event(t_data *data);

/*
 ** draw.c
 */

/* void		ft_my_mlx_pixel_put(t_*mlx, int x, int y, int color); */
void			ft_draw_line(t_mlx *mlx, t_point begin, t_point end);
/* void		ft_draw_rect(t_data *data, t_point start, int width, int height); */
/* void		ft_draw_mini_map(t_data *data); */
/* void		ft_draw_grid(t_data *data); */
/* void		ft_draw_rays(t_data *data); */
/* void		ft_draw_player(t_data *data); */
int				ft_render(t_data *data);

/*
 ** init.c
 */

void			ft_init_rays(t_data *data);
void			ft_init_mlx(t_data *data);

/*
 ** init_player.c
 */

/* void		ft_get_player_position(t_data *data); */
/* void		ft_get_player_orientation(t_data *data); */
void			ft_init_player(t_data *data);

/*
 ** init_cub.c
 */

/* t_bool	ft_init_cub_color(t_cub *cub, const char **specs); */
/* t_bool	ft_init_cub_texture(t_cub *cub, const char **specs); */
/* int		*ft_maprow_to_int(const char *maprow, int *introw, int width); */
/* int		**ft_map_to_int(const char **charmap, int width, int height); */
/* t_bool	ft_init_cub_map(t_cub *cub, const char **specs); */
void			ft_init_cub(t_cub *cub, const char **specs);

/*
 ** load.c
 */

/* int			ft_line_counter(char *file); */
const char		**ft_load(char *file);

/*
 ** main.c
 */

/* void		ft_check_arg(const char *arg); */
int				main(int argc, char **argv);

#endif
