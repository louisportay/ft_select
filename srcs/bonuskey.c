/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuskey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:30:15 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 17:37:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Do what the name say it does (select or deselect all files)
*/

void	selectallfiles(t_select *env, bool selectype)
{
	t_list *tmp;

	tmp = env->files;
	while (tmp)
	{
		((t_file *)tmp->content)->select = selectype;
		tmp = tmp->next;
	}
}

/*
** Remove from the list the files that doesn't exist
*/

void	deletefalsefiles(t_select *env)
{
	t_list *tmp;
	
	tmp = env->files;
	while (tmp)
	{
		if (access(((t_file *)tmp->content)->filename, F_OK) == -1)
		{
			tmp = tmp->next;
			ft_lstremove(&env->files, ft_lstindex(env->files, tmp) -1, ft_delvoid);
		}
		else
			tmp = tmp->next;
	}
	if ((tmp = addr_cursor_file(env->files)) == NULL)
		((t_file *)env->files->content)->cursor = 1;
	refresh_window(env);
}

/*
** Returns the adress of the elem in the list that got the most letters
** in common with buf
*/

static t_list 	*match_expr(t_list *files, char *buf)
{
	t_list		*match;
	int		ret;
	unsigned char	char_matched;

	match = NULL;
	char_matched = 0;
	while (files)
	{
		if ((ret = ft_strmatch(((t_file *)files->content)->filename, buf)) > char_matched)
		{
			char_matched = ret;
			match = files;
		}
		files = files->next;
	}
	return (match);
}

/*
** Place the cursor over the elem which has  the most similar name with buf
*/

void	dynamic_search(char c, t_select *env)
{
	static unsigned char i = 0;

	t_list *match;
	t_list *cursor_file;

	if (c == '\\' && i > 0)
		env->buf [--i] = '\0';
	else if (c != '\\' && i < 255)
		env->buf[i++] = c;

	match = match_expr(env->files, env->buf);
	if (match && match != (cursor_file = addr_cursor_file(env->files)))
	{
		((t_file *)cursor_file->content)->cursor = 0;
		((t_file *)match->content)->cursor = 1;
	}
}
