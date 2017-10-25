/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:39:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 19:58:20 by lportay          ###   ########.fr       */
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

//DELETE THESE.

 t_list		*addr_cursor_file(t_list *lst)
{
	while (lst && T_FILE(lst->content)->cursor == 0)
		lst = lst->next;
	return (lst);
}

t_list		*addr_first_matched_file(t_list *lst)
{
	while (lst && T_FILE(lst->content)->match == 0)
		lst = lst->next;
	return (lst);
}
