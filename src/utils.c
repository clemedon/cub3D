#include "cube.h"

/*
 ** @brief      Free textures.
 **
 ** @param[i/o] cub a struct that contains textures
 */

void	ft_free_texture (t_cub *cub)
{
	int	i;

	i = 0;
	ft_free (cub->n_texture);
	ft_free (cub->s_texture);
	ft_free (cub->w_texture);
	ft_free (cub->e_texture);
	/* while (i < 4) */
	/* { */
	/* 	if (cub->texture[i].img) */
	/* 		mlx_destroy_image(data->mlx.mlx_ptr, cub->texture[i].img); */
	/* 	i ++; */
	/* } */
	/* while (i < 4) */
	/* { */
	/* 	if (cub->texture[i].img) */
	/* 		free(cub->texture[i].img); */
	/* 	i ++; */
	/* } */
}

/*
 ** @brief      Create rgb value
 **
 ** @param[in]  r the red value
 ** @param[in]  g the green value
 ** @param[in]  b the blue value
 ** @return     An rgb number
 */

unsigned long ft_create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

/*
 ** @brief      Print a char tab.
 **
 ** @param[in]  tab a 2D array.
 */

void	ft_print_chartab(const char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf ("'%s'\n", tab[i]);
}

/*
 ** @brief      Print an int tab.
 **
 ** @param[in]  tab a 2D array
 ** @param[in]  w 2D array width
 ** @param[in]  h 2D array height
 */

void	ft_print_inttab(int **tab, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf ("%i", tab[y][x]);
			x++;
		}
		y++;
		printf ("\n");
	}
}

/*
 ** @brief      Print a readable map
 **
 ** Replace the numbers with corresponding chars at display for readability.
 **
 ** @param[in]  tab a 2D array
 ** @param[in]  width 2D array width
 ** @param[in]  height 2D array height
 */

void	ft_print_readable_map(int **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		write (1, "'", 1);
		while (x < width)
		{
			if (map[y][x] == -1)
				write (1, " ", 1);
			if (map[y][x] == 0)
				write (1, "0", 1);
			if (map[y][x] == 1)
				write (1, "1", 1);
			if (map[y][x] == 2)
				write (1, "N", 1);
			if (map[y][x] == 3)
				write (1, "S", 1);
			if (map[y][x] == 4)
				write (1, "E", 1);
			if (map[y][x] == 5)
				write (1, "W", 1);
			x++;
		}
		write (1, "'", 1);
		y++;
		write (1, "\n", 1);
	}
}

int	ft_return_msg(const char *message, int retval)
{
	ft_putendl_fd ((char *)(unsigned long)message, 2);
	return (retval);
}

/*
 ** @brief      Turn 2D array into grid
 **
 ** "A rectangular array of elements of equal length."
 **
 ** The grid width should correspond to its longest row width.
 **
 ** @param[in]  map the cub specs map
 ** @return     A pointer to the grid
 */

char	**ft_gridify(const char **tab, int width, int height)
{
	int		y;
	char	**grid;

	grid = malloc (sizeof (char *) * (height + 1));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < height)
	{
		grid[y] = malloc (sizeof (char) * (width + 1));
		if (!grid[y])
		{
			grid[y] = 0;
			ft_freetab ((void **)grid);
			return (NULL);
		}
		ft_memset ((void *)grid[y], ' ', width);
		ft_memcpy ((void *)grid[y], (void *)tab[y], ft_strlen (tab[y]));
		grid[y][width] = 0;
		y++;
	}
	grid[y] = 0;
	return (grid);
}

/*
 ** @brief      Count occurences in string
 **
 ** @param[in]  s a string
 ** @param[in]  c a character
 ** @return     The number of occurence of c in s.
 */

size_t	ft_strchr_count(char const *s, int c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			count++;
		++s;
	}
	return (count);
}

/*
 ** @brief      Print an error message and exit.
 **
 ** @param[in]  func the function causing the error.
 ** @param[in]  strerror the message to print.
 **
 ** TODO rename ft_exit_errmsg
 */

void	ft_exit_error(const char *func, const char *strerror)
{
	if (!strerror)
	{
		ft_putstr_fd ((char *)(unsigned long)func, 2);
		ft_putendl_fd (": undefined error", 2);
	}
	else if (!func)
	{
		ft_putendl_fd ((char *)(unsigned long)strerror, 2);
	}
	else
	{
		ft_putstr_fd ((char *)(unsigned long)func, 2);
		ft_putstr_fd (": ", 2);
		ft_putendl_fd ((char *)(unsigned long)strerror, 2);
	}
	exit (errno);
}

/*
 ** @brief      Open a file.
 **
 ** @param[in]  file a file.
 ** return      A file descriptor.
 */

int	ft_open(const char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		ft_exit_error (__func__, strerror (errno));
	return (fd);
}

/*
 ** @brief      Check if string has character from charset.
 **
 ** The terminating null character is not considered to be part of the string.
 **
 ** @param[in] str the string to inspect.
 ** @param[in] charset the set of characters to find.
 ** @return    True or false.
 */

t_bool	ft_strcharset(const char *str, const char *charset)
{
	int	i;

	i = 0;
	while (*charset)
	{
		while (str[i])
		{
			if (str[i] == *charset)
				return (TRUE);
			i++;
		}
		i = 0;
		charset++;
	}
	return (FALSE);
}

/*
 ** @brief      Check if a string is only made of the charset characters.
 **
 ** The terminating null character is not considered to be part of the string.
 **
 ** @param[in] str the string to inspect.
 ** @param[in] charset the set of characters.
 ** @return    True or false.
 **
 ** TODO Create str_without.
 */

t_bool	ft_str_onlywith(const char *str, const char *charset)
{
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (ft_strchr (charset, *str) == NULL)
			return (FALSE);
		else
			str++;
	}
	return (TRUE);
}

/*
 ** @brief      Replace all the occurence of a character in a string.
 **
 ** @param[in]  str the string to modify.
 ** @param[in]  find the old character.
 ** @param[in]  replace the new character.
 ** @return     A pointer to the initial string.
 */

char	*ft_replace_char(char *str, char find, char replace)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == find)
			*ptr = replace;
		ptr++;
	}
	return (str);
}

/*
 ** @brief      Return string tab height.
 **
 ** @param[in]  tab an array of strings
 ** @return     The tab height.
 */

int	ft_strtab_height(const char **tab)
{
	int	height;
	int	y;

	y = 0;
	height = 0;
	while (tab[y++])
		height++;
	return (height);
}

/*
 ** @brief      Return string tab width.
 **
 ** The longest string will give its len to the tab width.
 **
 ** @param[in]  tab an array of strings
 ** @return     The tab width.
 */

int	ft_strtab_width(const char **tab)
{
	int	width;
	int	x;
	int	y;

	y = 0;
	x = 0;
	width = 0;
	while (tab[y])
	{
		while (tab[y][x])
			x++;
		if (x > width)
			width = x;
		x = 0;
		y++;
	}
	return (width);
}
