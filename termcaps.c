/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 15:24:49 by lportay           #+#    #+#             */
/*   Updated: 2017/08/29 15:24:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h> // def ERR macro
#include <term.h>
#include <stdlib.h>
//#include <unistd.h>

/*
** Read 'man termios' + 'man termcap' + 'man tcgetattr'
*/

int main(void)
{
	char			*name_term;
	struct termios	term;

	if ((name_term = getenv("TERM")) == NULL)
		exit(EXIT_FAILURE);
	if (tgetent(NULL, name_term) == ERR)
		exit(EXIT_FAILURE);
	if (tcgetattr(0, &term) == -1)
     return (-1);
}
