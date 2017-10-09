/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:36:10 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 22:07:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_file	*new_file(char *filename)
{
	t_file *new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->filename = ft_strdup(filename);
	return (new);
}

/*
** Function  to pass to lstdel to delete a file in the list
*/

void	destroy_file(void *content, size_t content_size)
{
	if (content)
		ft_strdel(&((t_file *)content)->filename);
	ft_bzero(content, content_size);
	ft_memdel(&content);
}

void	fill_lst(t_list **files, char **av)
{
	while (*av == NULL || ft_strcmp(*av, "") == 0)
		av++;
	*files = ft_lstnewaddr(new_file(*av), sizeof(t_file));
	if (av != NULL)
		av++;
	while (*av)
	{
		if (*av != NULL && ft_strcmp(*av, "") != 0)
			ft_lstaddend(files, ft_lstnewaddr(new_file(*av), sizeof(t_file)));
		av++;
	}
}
