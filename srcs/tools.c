/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:39:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 11:11:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** function written for tputs to output the characters
*/

int		ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

/*
** Close the open file descriptor linked to open directories
** Called by ft_lstdel in restore_term
*/

void		wrap_closedir(void *content, size_t len)
{
	(void)len;
	closedir(content);
	content = NULL;
}

/*
** Find the next file with flag 'match' on and return it, return NULL otherwise
*/

t_list		*next_match_on(t_list *lst)
{
	lst = lst->next;
	while (lst)
	{
		if (T_FILE(lst->content)->match == 1)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
** Will set properly the cursor file
*/

void	reset_cf(t_select *env)
{
	if (FMF)
		CF = FMF;
	else
		CF = env->files;
	T_FILE(CF->content)->cursor = 1;
}
