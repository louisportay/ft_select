/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:39:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 17:23:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	dump_err(int errcode)
{
	if (errcode == NOINPUT)
		ft_putstr(NOINPUT_STR);
	else if (errcode == NOTERM)
		ft_putstr(NOTERM_STR);
	else if (errcode == NOTERMDB)
		ft_putstr(NOTERMDB_STR);
	else if (errcode == NOATTR)
		ft_putstr(NOATTR_STR);
	else if (errcode == NOWINDOW)
		ft_putstr(NOWINDOW_STR);
}

/*
** Print the error message and exit
*/
void	fatal_err(int errcode)
{
	dump_err(errcode);
	exit(errcode);
}
