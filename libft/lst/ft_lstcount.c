/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:30:35 by lportay           #+#    #+#             */
/*   Updated: 2017/05/12 12:34:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** O(N) complexity
** This function counts the number of elements in the given lst
*/

size_t		ft_lstcount(t_list *lst)
{
	size_t i;

	i = 1;
	while (lst != NULL && (lst = lst->next))
		i++;
	return (i);
}
