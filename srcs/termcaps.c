/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:40:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/06 15:57:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	cursor_mode(bool val)
{
	if (val == true)
	{
		tputs(tgetstr("ti", NULL), 1, ft_putchar);
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
	}
	else if (val == false)
	{
		tputs(tgetstr("te", NULL), 1, ft_putchar);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);

	}
}
