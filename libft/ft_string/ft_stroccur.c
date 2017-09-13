/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroccur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:46:05 by lportay           #+#    #+#             */
/*   Updated: 2017/06/29 16:24:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_stroccur(const char *s, char c)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
		i += (*s++ == c) ? 1 : 0;
	return (i);
}
