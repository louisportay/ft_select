/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:34:41 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:05:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the string 's' in the buffer 'buf' and then call write to output
** what's remaining in the buffer
*/

void	ft_putstr(char const *s)
{
	size_t	i;
	char	buf[BUFF_SIZE];

	i = 0;
	while (*s)
		putc_in_buf(*s++, buf, &i);
	write(STDOUT_FILENO, &buf, i % BUFF_SIZE);
}
