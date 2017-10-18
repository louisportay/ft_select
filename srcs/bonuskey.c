/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:30:15 by lportay           #+#    #+#             */
/*   Updated: 2017/10/18 21:12:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	selectallfiles(t_select *env, bool selectype)
{
	t_list *tmp;

	tmp = env->files;
	while (tmp)
	{
		((t_file *)tmp->content)->select = selectype;
		tmp = tmp->next;
	}
}

void	deletefalsefiles(t_select *env)
{
	t_list *tmp;
	
	tmp = env->files;
	while (tmp)
	{
		if (access(((t_file *)tmp->content)->filename, F_OK) == -1)
		{
			tmp = tmp->next;
			ft_lstremove(&env->files, ft_lstindex(env->files, tmp) -1, ft_delvoid);
		}
		else
			tmp = tmp->next;
	}
	if ((tmp = addr_cursor_file(env->files)) == NULL)
		((t_file *)env->files->content)->cursor = 1;
	refresh_window(env);
}
