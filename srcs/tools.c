/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:39:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/20 17:01:10 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Big switch to print the right error message
*/

static void	dump_err(int errcode)
{
	if (errcode == NOINPUT)
		ft_putstr_fd(STDIN_FILENO, NOINPUT_STR);
	else if (errcode == NOTERM)
		ft_putstr_fd(STDIN_FILENO, NOTERM_STR);
	else if (errcode == NOTERMDB)
		ft_putstr_fd(STDIN_FILENO, NOTERMDB_STR);
	else if (errcode == NOATTR)
		ft_putstr_fd(STDIN_FILENO, NOATTR_STR);
	else if (errcode == NOWINDOW)
		ft_putstr_fd(STDIN_FILENO, NOWINDOW_STR);
	else if (errcode == SHITTYINPUT)
		ft_putstr_fd(STDIN_FILENO, SHITTYINPUT_STR);
}

/*
** Print the error message and exit
*/

void		fatal_err(int errcode)
{
	dump_err(errcode);
	exit(errcode);
}

/*
** Restore term config, free the list and exit
*/

void		wrap_exit(t_select *env, int status)
{
	restore_term(env, true);
	exit(status);
}

int	ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

t_list	*addr_cursor_file(t_list *lst)
{
	while (lst && ((t_file *)lst->content)->cursor != 1)
		lst = lst->next;
	return (lst);
}
