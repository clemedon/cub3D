#include "cube.h"

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

int	ft_return_msg(const char *message, int retval)
{
	ft_putendl_fd ((char *)(unsigned long)message, 2);
	return (retval);
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
