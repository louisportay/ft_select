/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:59:26 by lportay           #+#    #+#             */
/*   Updated: 2017/06/29 14:43:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_array(void **tab)
{
	if (tab != NULL)
	{
		while (*tab != NULL)
			ft_memdel(&(*tab++));
		tab = NULL;
	}
}
