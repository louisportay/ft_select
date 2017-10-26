/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:57:01 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 18:36:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Set on the flag 'match' when the buffer letters are the same as the filename
** Get called by dynamic search
*/

static void 	set_match(t_select *env)
{
	t_list	*tmp;
	bool	first;

	tmp = env->files;
	first = true;
	FMF = NULL;
	MATCHED_FILES = 0;
	while (tmp)
	{
		if (ft_strncmp(T_FILE(tmp->content)->filename, env->buf, ft_strlen(env->buf)) == 0)
		{
			if (first == true)
			{
				FMF = tmp;
				first = false;
			}
			T_FILE(tmp->content)->match = 1;
			MATCHED_FILES++;
		}
		else
			T_FILE(tmp->content)->match = 0;
		tmp = tmp->next;
	}
}

/*
** Call set_match and refresh_window to set the environment to print only the
** files with the flag 'match' on (flag on by default)
** 
** Get called by fill_buffer and autofill_buffer
*/

static void	dynamic_search(t_select *env)
{
	set_match(env);
	if (!FMF)
		return ;
	if (T_FILE(CF->content)->match == 0)
	{
		T_FILE(CF->content)->cursor = 0;
		T_FILE(FMF->content)->cursor = 1;
		CF = FMF;
	}
	refresh_window(env);
}

/*
** Fill the buffer with the sent character, or delete a character or clear the
** whole buffer
*/

void	fill_buffer(char c, t_select *env)
{
	if (c == '!')
	{
		ft_bzero(env->buf, 255);
		BUFI = 0;
	}
	else if (c == '\\' && BUFI > 0)
		env->buf [--BUFI] = '\0';
	else if (c != '\\' && BUFI < 255)
		env->buf[BUFI++] = c;
	dynamic_search(env);
}

/*
** Fill the buffer with the cursor filename 
*/

void	autofill_buffer(t_select *env)
{
	size_t len;

	len = ft_strlen(env->buf);
	if (ft_strncmp(T_FILE(CF->content)->filename, env->buf, len) == 0)
	{
		while (T_FILE(CF->content)->filename[len] != '\0' && T_FILE(CF->content)->filename[len - 1] != '/' && len < 255)
		{
			env->buf[len] = T_FILE(CF->content)->filename[len];
			len++;
			(BUFI)++;
		}
	}
	dynamic_search(env);
}
