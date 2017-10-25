/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 20:05:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//TODELETE
int nb_match(t_list *files)
{
	int match;

	match = 0;
	while (files)
	{
		if (T_FILE(files->content)->match == 1)
			match++;
		files = files->next;
	}
	return (match);
}

/*
** Return the index number of the cursor file (for every matched file before)
*/

static int index_match(t_list *files, t_list *tmp)
{
	int index;

	index = 0;
	while (files)
	{
		if (files == tmp)
			return (index);
		else if (T_FILE(files->content)->match == 1)
			index++;
		files = files->next;
	}
	return (-1);
}

static t_list *addrmatchonly(t_list *files, int rank)
{
	while (files)
	{
		if (rank == 0 && T_FILE(files->content)->match == 1)
			return (files);
		else if (T_FILE(files->content)->match == 1 && rank != 0)
			rank--;
		files = files->next;
	}
	return (NULL);
}

/*
** Do some kryptico-wizardry computations to get a fancy cursor moving...
**
**				IN 4 DIRECTIONS!
**
** A Complete finite state machine would have been easier to understand
*/

static int	get_index(short movement, int index, int nb_files, t_select *env)
{
	if (index + movement >= nb_files)
	{
		if (movement == 1 || (nb_files <= FBL && index == (nb_files - 1)))
			return (0);
		else
			return (((index % FBL) == (FBL - 1)) ? 0 : ((index % FBL) + 1));
	}
	else if (index + movement < 0)
	{
		if (movement == -1 || (nb_files <= FBL && index == 0))
			return (nb_files - 1);
		else
		{
			if (FBL * MINLIN == nb_files)
				index += (FBL * MINLIN) - 1;
			else
				index += (FBL * (MINLIN - 1)) - 1;
			return (index - ((index >= nb_files) ? FBL : 0));
		}
	}
	else
		return (index + movement);
}

/*
** Get the file with cursor on it, switch it off and switch it on
** 'movement' files later.
**
** High Complexity (move a lot in the linked list)
** implementation with double-linked lists would be more efficient.
** (more complex too)
*/

static void	move_cursor(short movement, t_select *env)
{
	t_list	*tmp;

	if (addr_first_matched_file(env->files) == NULL)//TEJ ca
		return ;
	tmp = addr_cursor_file(env->files);//TEJ ca aussi
	T_FILE(tmp->content)->cursor = 0;
	if (*env->buf == '\0')//replace if by ternary
		tmp = ft_lstaddr(env->files, get_index(movement, ft_lstindex(env->files, tmp), ft_lstcount(env->files), env));//virer lstcount
	else
		tmp = addrmatchonly(env->files, get_index(movement, index_match(env->files, tmp), nb_match(env->files), env));//virer nb_match
	T_FILE(tmp->content)->cursor = 1;
}

/*
** Understand what user typed and call corresponding function
**
** Codes to escape sequences
** space == 32 == ' '
** enter == '\n'
** escape == '\033' == 27
** delete == '\177\' == 127 == \033[3~
*/

void	user_input(char *buf, t_select *env)
{
	if (*buf == ' ')
		spacekey(env);
	else if (*buf == '\n')
		enterkey(env);
	else if (*buf == '\t')
		autofill_buffer(env);
	else if (*buf == '\177')
		deletekey(env);
	else if (ft_isalnum(*buf) == true || *buf == '\\' || *buf == '.' || *buf == '/' || *buf == '!' || *buf == '_')
		fill_buffer(*buf, env);
	else if (*buf == '#')
		env->color = !(env->color);
	else if (*buf == '*')
		selectallfiles(env, true);
	else if (*buf == '-')
		selectallfiles(env, false);
	else if (*buf == '&' && env->dirmode == 0)
		deletefalsefiles(env);
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
			else if (*(buf + 2) == '3' && *(buf + 3) == '~')
				deletekey(env);
		}
	}
}
