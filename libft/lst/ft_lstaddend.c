/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:01 by lportay           #+#    #+#             */
/*   Updated: 2017/05/11 17:28:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Complexity O(n)
*/

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
