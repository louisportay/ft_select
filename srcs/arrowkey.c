/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 23:29:59 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:37:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//	MAKE IT BOUNCE AROUND

void	uparrowkey(void)
{
	ft_putstr("\n\e[31mUPKEY\e[0m\n");
}

void	downarrowkey(void)
{
	ft_putstr("\n\e[32mDOWNKEY\e[0m\n");
}

void	leftarrowkey(void)
{
	ft_putstr("\n\e[33mLEFTKEY\e[0m\n");
}

void	rightarrowkey(void)
{
	ft_putstr("\n\e[34mRIGHTKEY\e[0m\n");
}

