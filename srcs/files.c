/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:36:10 by lportay           #+#    #+#             */
/*   Updated: 2017/10/18 16:32:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Create a 't_file *' with the fields 'select' and 'cursor' set to 0 and
**  a pointer to the filename is set as well
*/

static t_file	*new_file(char *filename)
{
	t_file *new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->filename = filename;
	new->select = 0;
	new->cursor = 0;
	return (new);
}

/*
** Convert the av array in a list of "struct *files"
*/

void	fill_lst(t_list **files, char **av)
{
	*files = NULL;
	while (*av && ft_strlen(*av) == 0)
		av++;
	if (*av)
		*files = ft_lstnewaddr(new_file(*av++), sizeof(t_file));
	while (*av)
	{
		if (*av && ft_strlen(*av))
			ft_lstaddend(files, ft_lstnewaddr(new_file(*av), sizeof(t_file)));
		av++;
	}
}
