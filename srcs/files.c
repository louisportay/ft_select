/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:36:10 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 19:29:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Create a 't_file *' with the fields 'select' and 'cursor' set to 0 and
** 'match'a pointer to the filename is set as well
*/

static t_file	*new_file(char *filename)
{
	t_file *new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->filename = filename;
	new->select = 0;
	new->cursor = 0;
	new->match = 1;
	return (new);
}

/*
** Handle temporary lists head creation and deletion.
** Will also delete dirlist if filelist is empty
*/

static void	manage_lists(t_select *env, bool status)
{
	if (status == CREATE)
	{
		env->files = ft_lstnew("HEAD", 5);
		env->dir = ft_lstnew("HEAD", 5);
	}
	else if (status == DELETE)
	{
		ft_lstremove(&env->files, 0, ft_delvoid);
		ft_lstremove(&env->dir, 0, ft_delvoid);
		if (!env->files)
			ft_lstdel(&env->dir, &wrap_closedir);
	}
}

/*
** 'directory' option
*/

static void	directory_fill(t_select *env, char **av)
{
	DIR 		*dirp;
	struct dirent	*direntry;

	manage_lists(env, CREATE);
	env->dirmode = 1;
	while (*av)
	{
		dirp = opendir(*av);
		if (dirp)
		{
			ft_lstaddend(&env->dir, ft_lstnewaddr(dirp, sizeof(struct dirent *)));
			direntry = readdir(dirp);
			while (direntry)
			{
				if (ft_strncmp(direntry->d_name, ".", 1) != 0)
					ft_lstaddend(&env->files, ft_lstnewaddr(new_file(direntry->d_name), sizeof(t_file)));
				direntry = readdir(dirp);
			}
		}
		else
			ft_lstaddend(&env->files, ft_lstnewaddr(new_file(*av), sizeof(t_file)));
		av++;
	}
	manage_lists(env, DELETE);
}

/*
** Convert the av array in a list of "struct *files"
*/

void	fill_lst(t_select *env, char **av)
{
	env->files = NULL;
	env->dir = NULL;
	while (*av && ft_strlen(*av) == 0)
		av++;
	if (!(*av))
		return ;
	if (ft_strcmp(*av, "--directory") == 0)
		return (directory_fill(env, ++av));
	env->dirmode = 0;
	env->files = ft_lstnewaddr(new_file(*av++), sizeof(t_file));
	while (*av)
	{
		if (ft_strlen(*av))
			ft_lstaddend(&env->files, ft_lstnewaddr(new_file(*av),
			sizeof(t_file)));
		av++;
	}
}
