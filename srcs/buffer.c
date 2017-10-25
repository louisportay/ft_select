/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:57:01 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 18:42:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Returns the adress of the elem in the list that got the most letters
** in common with buf
*/

//SET LE NOMBRE DE FICHIERS MATCHéS
static void 	set_match(t_list *files, char *buf)
{
	while (files)
	{
		if (ft_strncmp(T_FILE(files->content)->filename, buf, ft_strlen(buf)) == 0)
			T_FILE(files->content)->match = 1;
		else
			T_FILE(files->content)->match = 0;
		files = files->next;
	}
}

/*
** Call different functions to set the environment to print only the files with
** the flag 'match' on (flag on by default)
** 
** Get called by fill_buffer and autofill_buffer
*/

static void	dynamic_search(t_select *env)
{
	t_list *cursor_file;
	t_list *first_matched;

	set_match(env->files, env->buf);
	if ((first_matched = addr_first_matched_file(env->files)) == NULL)//TEJ addrmachin
		return ;
	if (T_FILE((cursor_file = addr_cursor_file(env->files))->content)->match == 0)
	{
		T_FILE(cursor_file->content)->cursor = 0;
		T_FILE(first_matched->content)->cursor = 1;
	}
	refresh_window(env);
}

/*
** Fill the buffer with the sent characters, or delete a character or clear the
** whole thing
*/

void	fill_buffer(char c, t_select *env)
{
	if (c == '!')
	{
		ft_bzero(env->buf, 255);
		env->buf_index = 0;
	}
	else if (c == '\\' && env->buf_index > 0)
		env->buf [--(env->buf_index)] = '\0';
	else if (c != '\\' && env->buf_index < 255)
		env->buf[(env->buf_index)++] = c;
	dynamic_search(env);
}

/*
** Fill the buffer with the available files
*/

void	autofill_buffer(t_select *env)
{
	t_list *tmp;
	size_t len;

	len = ft_strlen(env->buf);
	tmp = addr_cursor_file(env->files);
	if (ft_strncmp(T_FILE(tmp->content)->filename, env->buf, len) == 0)
	{
		while (T_FILE(tmp->content)->filename[len] != '\0' && T_FILE(tmp->content)->filename[len - 1] != '/' && len < 255)
		{
			env->buf[len] = T_FILE(tmp->content)->filename[len];
			len++;
			(env->buf_index)++;
		}
	}
	dynamic_search(env);
}
