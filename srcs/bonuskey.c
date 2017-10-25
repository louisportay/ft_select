/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:30:15 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 14:11:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Do what the name say it does (select or deselect all files)
*/

void	selectallfiles(t_select *env, bool selectype)
{
	t_list *tmp;

	tmp = env->files;
	while (tmp)
	{
		T_FILE(tmp->content)->select = selectype;
		tmp = tmp->next;
	}
}

/*
** Remove from the list the files that doesn't exist
*/

void	deletefalsefiles(t_select *env)
{
	t_list *tmp;
	
	tmp = env->files;
	while (tmp)
	{
		if (access(T_FILE(tmp->content)->filename, F_OK) == -1)
		{
			tmp = tmp->next;
			ft_lstremove(&env->files, ft_lstindex(env->files, tmp) -1, ft_delvoid);
		}
		else
			tmp = tmp->next;
	}
	if (!env->files)
		return ;
	if ((tmp = addr_cursor_file(env->files)) == NULL)
		T_FILE(env->files->content)->cursor = 1;
	refresh_window(env);
}

