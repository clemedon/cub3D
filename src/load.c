/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:08:29 by cvidon            #+#    #+#             */
/*   Updated: 2022/11/15 12:08:30 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
 ** @brief      File line counter
 **
 ** @param[in]  file a file
 ** @return     The line count
 */

static int	ft_line_counter(char *file)
{
	long	r;
	int		fd;
	char	*buf;
	int		count;

	buf = malloc (1);
	if (!buf)
		ft_exit_error (__func__, strerror (errno));
	fd = ft_open (file);
	r = 1;
	count = 0;
	while (r)
	{
		r = read (fd, buf, 1);
		if (r == -1)
		{
			free (buf);
			close (fd);
			ft_exit_error (__func__, strerror (errno));
		}
		count += (*buf == '\n');
	}
	free (buf);
	close (fd);
	return (count - 1);
}

/*
 ** @brief      Duplicate file to dynamic memory
 **
 ** @param[in]  file a file
 ** @return     An array of strings corresponding to each lines
 */

const char	**ft_load_cub(char *file)
{
	int			fd;
	char		*line;
	const char	**ptr[2];
	int			line_count;

	line_count = ft_line_counter (file);
	ptr[0] = malloc (sizeof (char *) * (line_count + 1));
	if (!ptr[0])
		ft_exit_error (__func__, strerror (errno));
	fd = ft_open (file);
	ptr[1] = ptr[0];
	while (1)
	{
		line = ft_get_next_line (fd);
		if (!line)
		{
			*ptr[1] = 0;
			close (fd);
			if ((ptr[1] - ptr[0]) == line_count)
				return (ptr[0]);
			ft_freetab ((void **)ptr[0]);
			ft_exit_error ("ft_get_next_line", strerror (ENOMEM));
		}
		*ptr[1]++ = ft_replace_char (line, '\n', '\0');
	}
}
