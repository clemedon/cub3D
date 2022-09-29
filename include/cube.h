#ifndef CUBE_H
# define CUBE_H

/*
 ** =========[ Includes ]==========
 */

# include "libft.h"
/* # include <unistd.h> */
# include <fcntl.h>
# include <errno.h>
# include <string.h>
/* # include <limits.h> */

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

typedef enum e_player_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_player_direction;

/*
 ** =========[ Struct ]============
 */

typedef struct s_cub
{
	const char	**specs;
	int			f_color_hex;
	int			c_color_hex;
	int			n_texture_fd;
	int			s_texture_fd;
	int			w_texture_fd;
	int			e_texture_fd;
	int			**map;
	int			width;
	int			height;
}	t_cub;

/*
 ** =========[ Proto ]=============
 */

/*
 ** utils.c
 */

char		*ft_replace_char(char *str, char find, char replace);
int			ft_open(const char *file);
int			ft_return_msg(const char *message, int retval);
int			ft_strtab_height (const char **tab);
int			ft_strtab_width (const char **tab);
t_bool		ft_str_onlywith(const char *str, const char *charset);
t_bool		ft_strcharset(const char *str, const char *charset);
void		ft_exit_error(const char *func, const char *strerror);
void		ft_print_chartab(const char **tab);

/*
 ** parse.c
 */

/*
 ** check_cub/
 */

t_bool		ft_check_map_enclosure(char **grid, int width, int height);
char		**ft_mapgrid(const char **map, int width, int height);

t_bool		ft_check_map_limits(const char **map);
t_bool		ft_check_map_spawn(const char **map);
t_bool		ft_check_map_global(const char **map);
t_bool		ft_check_map(const char **specs);

t_bool		ft_check_tex_value(const char *specs);
t_bool		ft_check_tex(const char **specs);

t_bool		ft_check_col_value(const char *specs);
t_bool		ft_check_col(const char **specs);

t_bool		ft_check_cub(const char **specs);

/*
 ** init.c
 */

void		ft_init_cub_color(t_cub *cub, const char **specs);
void		ft_init_cub_texture(t_cub *cub, const char **specs);
void		ft_init_cub_map(t_cub *cub, const char **specs);
void		ft_init_cub(t_cub *cub, const char **specs);

/*
 ** load.c
 */

int			ft_line_counter(char *file);
const char	**ft_load(char *file);

/*
 ** main.c
 */

void		ft_check_arg(const char *arg);
int			main(int argc, char **argv);

#endif
