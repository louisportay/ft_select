/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:35:22 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 18:44:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	int				i;
	char			*s;
	unsigned int	m;

	i = ft_lwidth(nbr);
	m = (nbr < 0) ? -nbr : nbr;
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i--] = '\0';
	s[i--] = (m % 10) + '0';
	while ((m /= 10) != 0)
		s[i--] = (m % 10) + '0';
	s[0] = (nbr < 0) ? '-' : s[0];
	return (s);
}
