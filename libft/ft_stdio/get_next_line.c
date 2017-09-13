/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:50:13 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:56:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strjoin_gnl(char **rest, char **buf)
{
	char *buf_free;

	if (!(*rest) && *buf)
		*rest = ft_strdup(*buf);
	else
	{
		buf_free = *rest;
		*rest = ft_strjoin(*rest, *buf);
		ft_strdel(&buf_free);
	}
}

static int	find_nl(char **buf, char **rest, int fd, char **nl)
{
	int	ret;

	*buf = ft_strnew(BUFF_SIZE + 1);
	if ((ret = read(fd, *buf, BUFF_SIZE)) == -1)
		return (-1);
	while (!(*nl = ft_strchr(*buf, '\n')))
	{
		if (ret == 0)
		{
			ft_strdel(buf);
			return ((!(*rest) || ft_strlen(*rest) == 0) ? 0 : 1);
		}
		ft_strjoin_gnl(rest, buf);
		ft_bzero(*buf, BUFF_SIZE);
		ret = read(fd, *buf, BUFF_SIZE);
	}
	return (2);
}

static void	ft_pansement(char **buf, char **rest, char **line, char **nl)
{
	*buf[nl - buf] = '\0';
	ft_strjoin_gnl(rest, buf);
	*line = (!(*rest)) ? NULL : ft_strdup(*rest);
	ft_strdel(rest);
	*rest = ft_strdup(*nl + 1);
	if (ft_strlen(*rest) == 0)
		ft_strdel(rest);
	ft_strdel(buf);
}

/*
** la fonction écrit dans 'line' la ligne lue depuis le 'fd' indiqué, puis lit
** une nouvelle ligne à chaque appel de la fonction. renvoie 1 quand elle a lu
** une ligne, 0 quand le fichier est fini, -1 quand une erreur est survenue.
*/

int			get_next_line(const int fd, char **line)
{
	char		*buf;
	int			ret;
	static char	*rest = NULL;
	char		*nl;

	if (BUFF_SIZE <= 0 || fd < 0)
		return (-1);
	if (rest != NULL && (nl = ft_strchr(rest, '\n')) != NULL)
	{
		rest[nl - rest] = '\0';
		*line = ft_strdup(rest);
		free(rest);
		rest = ft_strdup(nl + 1);
		return (1);
	}
	if ((ret = find_nl(&buf, &rest, fd, &nl)) == -1 || ret == 0 || ret == 1)
	{
		if (ret == -1)
			return (ret);
		*line = (!rest) ? NULL : ft_strdup(rest);
		ft_strdel(&rest);
		return (ret);
	}
	ft_pansement(&buf, &rest, line, &nl);
	return (1);
}
