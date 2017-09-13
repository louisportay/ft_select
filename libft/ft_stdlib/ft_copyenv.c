/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 18:02:54 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:57:22 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copyenv(char **env)
{
	char	**heap_env;
	char	**tmp;
	size_t	len;

	len = 0;
	tmp = env;
	while (*tmp++)
		len++;
	if (!(heap_env = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	tmp = heap_env;
	while (len--)
	{
		if (!(*tmp = (char *)malloc(sizeof(char) * ft_strlen(*env) + 1)))
			return (NULL);
		ft_strcpy(*tmp++, *env++);
	}
	*tmp = NULL;
	return (heap_env);
}
