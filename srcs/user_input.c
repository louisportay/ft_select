/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 23:44:22 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	spacekey(void)
{

}

static void	enterkey(void)
{

}


static void	deletekey(void)
{

}

static void	escapekey(void)
{

}

/*
** Codes to escape sequences
** space == 32 == ' '
** enter == '\n'
** escape == '\033' == 27
*/

void	user_input(char *buf)
{
	if (buf[0] == ' ')
		spacekey();
	else if (buf[0] == '\n')
		enterkey();
	else if (buf[0] == '\033')
	{
		if (buf[1] == '\n')
			escapekey();
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
