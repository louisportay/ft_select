/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:39:24 by lportay           #+#    #+#             */
/*   Updated: 2017/06/10 17:42:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** n need to be positive
*/

t_list		*ft_lst_at(t_list *lst, size_t n)
{
	while (n-- > 0 && lst->next)
		lst = lst->next;
	return ((lst->next == NULL && n == 0) ? NULL : lst);
}
