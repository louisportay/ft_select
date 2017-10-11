/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/10 19:01:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	spacekey(void)
{
	ft_putstr("\nSPACE\n");
}

static void	enterkey(void)
{
	ft_putstr("\nENTER\n");
}


static void	deletekey(void)
{
	ft_putstr("\nDELETE\n");
}

static void	escapekey(t_select *env)
{
	restore_term(env, true);
	exit(EXIT_SUCCESS);
}

/*
** Codes to escape sequences
** space == 32 == ' '
** enter == '\n'
** escape == '\033' == 27
** delete == '\177\' == 127 == \033[3~
*/

void	user_input(char *buf, t_select *env)
{
	if (buf[0] == ' ')
		spacekey();
	else if (buf[0] == '\n')
		enterkey();
	else if (buf[0] == '\177')
		deletekey();
	else if (buf[0] == '\033')
	{
		if (buf[1] == '\0')
			escapekey(env);
		else if (buf[1] == '[')
		{
			if (buf[2] == 'A')
				uparrowkey();
			else if (buf[2] == 'B')
				downarrowkey();
			else if (buf[2] == 'C')
				rightarrowkey();
			else if (buf[2] == 'D')
				leftarrowkey();
			else if (buf[2] == '3' && buf[3] == '~')
				deletekey();
		}
	}
}
