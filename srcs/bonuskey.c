/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:30:15 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 20:00:40 by lportay          ###   ########.fr       */
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
		if (T_FILE(tmp->content)->match)
			T_FILE(tmp->content)->select = selectype;
		tmp = tmp->next;
	}
}

/*
** Remove from the list the files that are matched and doesn't exist
*/

void	deletefalsefiles(t_select *env)
{
	t_list *tmp;

	tmp = env->files;
	while (tmp)
	{
		if (access(T_FILE(tmp->content)->filename, F_OK) == -1 && T_FILE(tmp->content)->match)
		{
			if (tmp == FMF)	
				FMF = next_match_on(FMF);
			if (tmp == CF)
				CF = NULL;
			tmp = tmp->next;
			ft_lstremove(&env->files, ft_lstindex(env->files, tmp) -1, ft_delvoid);
			MATCHED_FILES--;
		}
		else
			tmp = tmp->next;
	}
	if (!env->files)
		return ;
	if (CF == NULL)
		reset_cf(env);
	refresh_window(env);
}
