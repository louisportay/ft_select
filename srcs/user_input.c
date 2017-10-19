/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 17:46:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_list	*addr_cursor_file(t_list *lst)
{
	while (lst && ((t_file *)lst->content)->cursor != 1)
		lst = lst->next;
	return (lst);
}

/*
** Do some kryptico-wizardry computations to get a fancy cursor moving...
**
**				IN 4 DIRECTIONS!
**
** 'col' is the number of real columns in use, FBL is only theoretical maximum
** (if not there isn't enough files to fill a single line)
*/

static int	calculate_index(short movement, int index, int nb_files, t_select *env)
{
	int col;

	col = (nb_files < FBL) ? nb_files : FBL;
	if (index + movement >= nb_files)
	{
		if (movement == 1)
			return (0);
		else
			return (((index % col) == (col - 1)) ? 0 : ((index % col) + 1));
	}
	else if (index + movement < 0)
	{
		if (movement == -1)
			return (nb_files - 1);
		else
		{
			if (FBL * MINLIN == nb_files)
				index += (col * MINLIN) - 1;
			else
				index += (col * (MINLIN - 1)) - 1;
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
	t_list *tmp;

	tmp = addr_cursor_file(env->files);
	((t_file *)tmp->content)->cursor = 0;
	tmp = ft_lstaddr(env->files, calculate_index(movement,
ft_lstindex(env->files, tmp), ft_lstcount(env->files), env));
	((t_file *)tmp->content)->cursor = 1;
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
	if (buf[0] == ' ')
		spacekey(env);
	else if (buf[0] == '\n')
		enterkey(env);
	else if (buf[0] == '\177')
		deletekey(env);
	else if (ft_isalnum(buf[0]) == true || buf[0] == '\\' || buf[0] == '.' || buf[0] == '/')
		dynamic_search(buf[0], env);
	else if (buf[0] == '#')
		env->color = !(env->color);
	else if (buf[0] == '*')
		selectallfiles(env, true);
	else if (buf[0] == '-')
		selectallfiles(env, false);
	else if (buf[0] == '&')
		deletefalsefiles(env);
	else if (buf[0] == '\033')
	{
		if (buf[1] == '\0')
			wrap_exit(env, EXIT_SUCCESS);
		else if (buf[1] == '[')
		{
			if (buf[2] == 'A')
				move_cursor(-FBL, env);
			else if (buf[2] == 'B')
				move_cursor(FBL, env);
			else if (buf[2] == 'C')
				move_cursor(1, env);
			else if (buf[2] == 'D')
				move_cursor(-1, env);
		//	else if (buf[2] == '3' && buf[3] == '~') // delete key ?
		//		deletekey(env);
		}
	}
}
