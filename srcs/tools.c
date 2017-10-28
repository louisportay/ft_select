/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:39:57 by lportay           #+#    #+#             */
/*   Updated: 2017/10/27 18:55:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** function written for tputs to output the characters
*/

int			ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

/*
** Close the open file descriptor linked to open directories
** Called by ft_lstdel in restore_term
*/

void		wrap_closedir(void *content, size_t len)
{
	(void)len;
	closedir(content);
	content = NULL;
}

/*
** Find the next file with flag 'match' on and return it, return NULL otherwise
*/

t_list		*next_match_on(t_list *lst)
{
	lst = lst->next;
	while (lst)
	{
		if (T_FILE(lst->content)->match == 1)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
** Will set properly the cursor file
*/

void		reset_cf(t_select *env)
{
	if (FMF)
		CF = FMF;
	else
		CF = env->files;
	T_FILE(CF->content)->cursor = 1;
}

/*
** Delete the lasts char of the string until it finds a slash character
*/

int			remove_filename(char *str)
{
	char	*tmp;
	int		del_char;

	tmp = str;
	del_char = 0;
	while (*tmp)
		tmp++;
	tmp--;
	while (*tmp != '/')
	{
		del_char++;
		*tmp = '\0';
		if (tmp == str)
			break ;
		tmp--;
	}
	return (del_char);
}
