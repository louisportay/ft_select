/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:44:49 by lportay           #+#    #+#             */
/*   Updated: 2017/10/20 17:19:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Flip the bit to select the file
** Move the cursor one file later
*/

void	spacekey(t_select *env)
{
	t_list *tmp;

	tmp = addr_cursor_file(env->files);
	T_FILE(tmp->content)->cursor = 0;
	T_FILE(tmp->content)->select = !T_FILE(tmp->content)->select;
	if (tmp->next)
		T_FILE(tmp->next->content)->cursor = 1;
	else
		T_FILE(env->files->content)->cursor = 1;
}

/*
** Print on screen to return the results
*/

void	enterkey(t_select *env)
{
	t_list *tmp;

	tmp = env->files;
	restore_term(env, false);
	while (tmp)
	{
		if (T_FILE(tmp->content)->select == 1)
		{
			ft_putstr(T_FILE(tmp->content)->filename);
			write(STDOUT_FILENO, " ", 1);
		}
		tmp = tmp->next;
	}
	ft_lstdel(&env->files, ft_delvoid);
	exit(EXIT_SUCCESS);
}

/*
** Delete the file and call refresh_window to recalculate padding
*/

void	deletekey(t_select *env)
{
	t_list *tmp;

	tmp = addr_cursor_file(env->files);
	if (tmp->next)
		T_FILE(tmp->next->content)->cursor = 1;
	else
		T_FILE(env->files->content)->cursor = 1;
	ft_lstremove(&env->files, ft_lstindex(env->files, tmp), ft_delvoid);
	refresh_window(env);
}
