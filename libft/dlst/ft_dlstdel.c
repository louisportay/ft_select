/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2017/03/16 20:57:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist *tmp;

	tmp = *alst;
	while (tmp)
	{
		*alst = (*alst)->next;
		(*del)(tmp->content, tmp->content_size);
		free(tmp);
		tmp = *alst;
	}
	free(*alst);
	*alst = NULL;
}
