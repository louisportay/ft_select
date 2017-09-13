/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 17:59:02 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:59:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert or modify (if 'overwrite' == 1) an already existing key 'name=value'
** in the 'env' array
*/

static int	modify_env(char *tmp, const char *value, int overwrite,
char **tmp_env)
{
	while (*tmp_env)
		if (ft_strncmp(tmp, *tmp_env++, ft_strlen(tmp)) == 0)
		{
			if (overwrite != 0)
				ft_strrep(--tmp_env, ft_strjoin(tmp, value));
			ft_strdel(&tmp);
			return (0);
		}
	return (1);
}

int			ft_setenv(const char *name, const char *value, int overwrite,
char ***env)
{
	size_t	cells;
	char	**tmp_env;
	char	**new_env;
	char	*tmp;

	cells = 0;
	tmp_env = *env;
	tmp = ft_strjoin(name, "=");
	if (modify_env(tmp, value, overwrite, tmp_env) == 0)
		return (0);
	while (*tmp_env++)
		cells++;
	if (!(new_env = (char **)malloc(sizeof(char *) * (cells + 2))))
		return (-1);
	tmp_env = new_env;
	while (**env)
		*tmp_env++ = *(*env)++;
	*tmp_env++ = ft_strjoin(tmp, value);
	*tmp_env = NULL;
	free(*env - cells);
	*env = new_env;
	ft_strdel(&tmp);
	return (0);
}
