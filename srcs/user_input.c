/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/28 01:44:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Understand what user typed and call corresponding function
**
** escape == '\033' == 27
** delete == '\177' == 127 == \033[3~
*/

void	user_input(char *buf, t_select *env)
{
	if (*buf == ' ' && T_FILE(CF->content)->match)
		spacekey(env);
	else if (*buf == '\n')
		enterkey(env);
	else if (*buf == '\t' && T_FILE(CF->content)->match)
		autofill_buffer(env);
	else if (*buf == '\177' && T_FILE(CF->content)->match)
		deletekey(env);
	else if (ft_isalnum(*buf) == true || *buf == '\\' || *buf == '.' || *buf == '/' || *buf == '!' || *buf == '_' || *buf == '`')
		fill_buffer(*buf, env);
	else if (*buf == '#')
		env->color = !(env->color);
	else if (*buf == '*')
		selectallfiles(env, true);
	else if (*buf == '-')
		selectallfiles(env, false);
	else if (*buf == '&')
		deletefiles(env, FALSEMODE);
	else if (*buf == '^')
		deletefiles(env, SELECTMODE);
	else if (*buf == '?')
		env->print_buf = !env->print_buf;
	else if (*buf == '\033')
	{
		if (*(buf + 1) == '\0')
			wrap_exit(env, EXIT_SUCCESS);
		else if (*(buf + 1) == '[')
		{
			if (*(buf + 2) == 'A')
				move_cursor(-FBL, env);
			else if (*(buf + 2) == 'B')
				move_cursor(FBL, env);
			else if (*(buf + 2) == 'C')
				move_cursor(1, env);
			else if (*(buf + 2) == 'D')
				move_cursor(-1, env);
			else if (*(buf + 2) == '3' && *(buf + 3) == '~' && T_FILE(CF->content)->match)
				deletekey(env);
		}
	}
}
