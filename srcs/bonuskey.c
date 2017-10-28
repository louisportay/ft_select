/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:30:15 by lportay           #+#    #+#             */
/*   Updated: 2017/10/27 21:23:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Do what the name say it does (select or deselect all files)
*/

void		selectallfiles(t_select *env, bool selectype)
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
** Verify whether the file must be deleted or not
*/

static bool	to_delete(t_file *file, bool mode)
{
	if (((mode == FALSEMODE && file->exist == 0) || (mode == SELECTMODE &&
		file->select)) && file->match)
		return (true);
	return (false);
}

/*
** Remove from the list the matched files and that doesn't exist (FALSEMODE)
**
** OR
**
** Remove from the list the files that are matched and selected (SELECTMODE)
*/

void		deletefiles(t_select *env, bool mode)
{
	t_list *tmp;

	tmp = env->files;
	while (tmp)
	{
		if (to_delete(T_FILE(tmp->content), mode) == true)
		{
			if (tmp == FMF)
				FMF = next_match_on(FMF);
			if (tmp == CF)
				CF = NULL;
			tmp = tmp->next;
			ft_lstremove(&env->files, ft_lstindex(env->files, tmp) - 1,
					ft_delvoid);
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
