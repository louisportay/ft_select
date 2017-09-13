/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashIndex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:10:52 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:44:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return the index associated with a given key.
**
** The hashing algorithm is CLEARLY not optimized, doing something to fix that
** may be great.
*/

unsigned	hashindex(char *key)
{
	unsigned hashval;

	hashval = 0;
	while (*key)
		hashval = *key++ + hashval;
	return (hashval % HASHSIZE);
}
