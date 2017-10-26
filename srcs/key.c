/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:44:49 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 20:11:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Flip the bit to select the file
** Move the cursor one file later
*/

void	spacekey(t_select *env)
{
	T_FILE(CF->content)->cursor = 0;
	T_FILE(CF->content)->select = !T_FILE(CF->content)->select;
	if ((CF = next_match_on(CF)))
		T_FILE(CF->content)->cursor = 1;
	else
	{
		CF = FMF;
		T_FILE(CF->content)->cursor = 1;
	}
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

	tmp = CF;
	if (CF == FMF)
		FMF = next_match_on(FMF);
	if ((CF = next_match_on(CF)))
		T_FILE(CF->content)->cursor = 1;
	else
		reset_cf(env);
	ft_lstremove(&env->files, ft_lstindex(env->files, tmp), ft_delvoid);
	MATCHED_FILES--;
	refresh_window(env);
}
