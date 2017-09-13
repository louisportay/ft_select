/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2017/05/12 18:37:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*maillon;
	char	*s;

	if (!(maillon = malloc(sizeof(t_dlist))))
		return (NULL);
	maillon->previous = NULL;
	maillon->next = NULL;
	if (!content)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
		return (maillon);
	}
	if (!(s = (char *)malloc(sizeof(char) * content_size)))
		return (NULL);
	ft_memcpy(s, content, content_size);
	maillon->content = s;
	maillon->content_size = content_size;
	return (maillon);
}
