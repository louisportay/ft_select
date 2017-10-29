/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:36:10 by lportay           #+#    #+#             */
/*   Updated: 2017/10/27 21:29:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Create a 't_file *' with the fields 'select' and 'cursor' set to 0 and
** 'match'a pointer to the filename is set as well
*/

static t_file	*new_file(char *filename, int access_ret, int st_mode,
		bool mode)
{
	t_file *new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->filename = (mode == DIRMODE) ? ft_strdup(filename) : filename;
	new->st_mode = st_mode;
	new->match = 1;
	new->select = 0;
	new->cursor = 0;
	if (access_ret == 0)
		new->exist = 1;
	else
		new->exist = 0;
	return (new);
}

static void		getdirentry(t_select *env, DIR *dirp, char *av)
{
	char			fpath[512];
	struct stat		buf;
	struct dirent	*direntry;

	buf.st_mode = 0;
	ft_strncpy(fpath, av, 512);
	if (fpath[(ft_strlen(fpath) - 1)] != '/')
		ft_strcat(fpath, "/");
	direntry = readdir(dirp);
	while (direntry)
	{
		if (ft_strncmp(direntry->d_name, ".", 1) != 0)
		{
			ft_strcat(fpath, direntry->d_name);
			lstat(fpath, &buf);
			ft_lstaddend(&env->files, ft_lstnewaddr(new_file(direntry->d_name,
							0, buf.st_mode, DIRMODE), sizeof(t_file)));
			remove_filename(fpath);
			buf.st_mode = 0;
		}
		direntry = readdir(dirp);
	}
	closedir(dirp);
}

static void		wrap_newfile(t_select *env, char *av, bool mode)
{
	struct stat	buf;
	int			ret;

	if (ft_strlen(av) == 0)
		return ;
	buf.st_mode = 0;
	if ((ret = access(av, F_OK)) == 0)
		lstat(av, &buf);
	ft_lstaddend(&env->files, ft_lstnewaddr(new_file(av, ret, buf.st_mode, mode)
				, sizeof(t_file)));
}

/*
** 'directory' option
*/

static void		directory_fill(t_select *env, char **av)
{
	DIR	*dirp;

	env->dirmode = true;
	while (*av)
	{
		dirp = opendir(*av);
		if (dirp)
			getdirentry(env, dirp, *av);
		else
			wrap_newfile(env, *av, DIRMODE);
		av++;
	}
	ft_lstremove(&env->files, 0, ft_delvoid);
}

/*
** Convert the av array in a list of "struct *files"
*/

void			fill_lst(t_select *env, char **av)
{
	env->files = NULL;
	while (*av && ft_strlen(*av) == 0)
		av++;
	if (!(*av))
		return ;
	env->files = ft_lstnew("HEAD", 5);
	if (ft_strcmp(*av, "--directory") == 0)
		return (directory_fill(env, ++av));
	env->dirmode = false;
	while (*av)
		wrap_newfile(env, *av++, NORMAL);
	ft_lstremove(&env->files, 0, ft_delvoid);
}
