/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putns_in_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:07:46 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 15:01:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putns_in_buf(int j, char *s, char *buf, size_t *i)
{
	while (*s && j-- > 0)
		putc_in_buf(*s++, buf, i);
}
