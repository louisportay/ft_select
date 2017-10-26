/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:23:44 by lportay           #+#    #+#             */
/*   Updated: 2017/10/26 20:27:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
** Implementation with double-linked lists would be more efficient.
** (more complex too)
*/

void	move_cursor(short movement, t_select *env)
{
	if (!FMF)
		return ;
	T_FILE(CF->content)->cursor = 0;
	if (*env->buf == '\0')
		CF = ft_lstaddr(env->files, get_index(movement, ft_lstindex(env->files, CF), MATCHED_FILES, env));
	else
		CF = addrmatchonly(env->files, get_index(movement, index_match(env->files, CF), MATCHED_FILES, env));
	T_FILE(CF->content)->cursor = 1;
}
