/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 19:06:13 by lportay           #+#    #+#             */
/*   Updated: 2017/06/10 19:07:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*create_node(void *data)
{
	t_btree *bt;

	if ((bt = (t_btree *)malloc(sizeof(t_btree))) == NULL)
		return (NULL);
	bt->parent = 0;
	bt->left = 0;
	bt->right = 0;
	bt->data = data;
	return (bt);
}
