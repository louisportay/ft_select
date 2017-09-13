/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:01:58 by lportay           #+#    #+#             */
/*   Updated: 2017/08/24 21:52:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# define HASHSIZE 32

typedef struct		s_hash
{
	char			*key;
	void			*data;
	size_t			data_size;
	struct s_hash	*next;
}					t_hash;

int					hashdel(t_hash **table, char *key, void (*del)(void **));
unsigned			hashindex(char *key);
int					hashinsert(t_hash **table, t_hash *bucket, int overwrite,
		void (*del)(void **));
t_hash				*hashlookup(t_hash **table, char *key);
t_hash				*hashcreate(char *key, void *data, size_t data_size);

#endif
