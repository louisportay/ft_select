/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:05:12 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 20:17:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Apply the Select Terminal Configuration
** Function called after a SIGCONT and on launch
*/

void	select_term(t_select *env)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->tios);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_stdin);
}

/*
** Restore the previous Terminal Configuration
** Function called after a SIGTSTP and when quitting the program
*/

void	restore_term(t_select *env, bool del)
{
	if (del == true)
		ft_lstdel(&env->files, &ft_delvoid);
	tputs(tgetstr("te", NULL), 1, ft_putchar_stdin);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_stdin);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->oldtios);
}
