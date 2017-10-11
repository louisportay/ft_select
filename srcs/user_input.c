/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 18:02:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Flip the bit to select the file
*/

static void	spacekey(void)
{
	ft_putstr("\nSPACE\n");
}

/*
** Print on screen to return the results
*/

static void	enterkey(void)
{
	ft_putstr("\nENTER\n");
}

/*
** Delete the file and call refresh_window to recalculate padding and winsize
*/

static void	deletekey(t_select *env)
{
	(void)env;
	ft_putstr("\nDELETE\n");
}

static void	escapekey(t_select *env)
{
	wrap_exit(env, EXIT_SUCCESS);
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
		deletekey(env);
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
		//	else if (buf[2] == '3' && buf[3] == '~') // delete key ?
		//		deletekey(env);
		}
	}
}
