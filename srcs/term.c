/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:05:12 by lportay           #+#    #+#             */
/*   Updated: 2017/10/10 18:27:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Apply the Select Terminal Configuration
** Called after a SIGCONT
*/

void	select_term(t_select *env)
{
	tputs(tgetstr("ti", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->tios);
}

/*
** Restore the previous Terminal Configuration
** Called after a SIGTSTP
*/

void	restore_term(t_select *env, bool del)
{
	if (del == true)
		ft_lstdel(&env->files, destroy_file);
	tputs(tgetstr("te", NULL), 1, ft_putchar);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->oldtios);
}
