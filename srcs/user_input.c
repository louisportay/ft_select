/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:18:29 by lportay           #+#    #+#             */
/*   Updated: 2017/10/13 17:48:45 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_list	*addr_selected_file(t_list *lst)
{
	while (((t_file *)lst->content)->cursor != 1)
		lst = lst->next;
	return (lst);
}

/*
** Do some kryptico-wizardry computations to get a fancy cursor moving...
**
**				IN 4 DIRECTIONS!
**
** 'col' is the number of real columns in use, FBL is theoretical maximum
** (if not there isn't enough files to fill a single line)
*/

static int	calculate_index(short movement, int index, int nb_files, t_select *env)
{
	int col;

	col = (nb_files < FBL) ? nb_files : FBL;
	if (index + movement >= nb_files) // loop from the end to the beginning
	{
		if (movement == 1)
			return (0);
		else
			return (((index % col) == (col - 1)) ? 0 : ((index % col) + 1));
	}
	else if (index + movement < 0) 	// loop from the beginning to the end
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
		return (index + movement); // normal, average movement
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

	tmp = addr_selected_file(env->files);
	((t_file *)tmp->content)->cursor = 0;
	tmp = ft_lstaddr(env->files, calculate_index(movement, ft_lstindex(env->files, tmp), ft_lstcount(env->files), env));
	((t_file *)tmp->content)->cursor = 1;
}

/*
** Flip the bit to select the file
** Move the cursor one file later
*/

static void	spacekey(t_select *env)
{
	t_list *tmp;

	tmp = addr_selected_file(env->files);
	((t_file *)tmp->content)->cursor = 0;
	((t_file *)tmp->content)->select = ~((t_file *)tmp->content)->select;
	if (tmp->next)
		((t_file *)tmp->next->content)->cursor = 1;
	else
		((t_file *)env->files->content)->cursor = 1;
}

/*
** Print on screen to return the results
*/

static void	enterkey(t_select *env)
{
	restore_term(env, false);
	while (env->files)
	{
		if (((t_file *)env->files->content)->select == 1)
		{
			ft_putstr_fd(STDOUT_FILENO, ((t_file *)env->files->content)->filename);
			ft_putchar_fd(STDOUT_FILENO, ' ');
		}
		env->files = env->files->next;
	}
	ft_lstdel(&env->files, destroy_file);
	exit(EXIT_SUCCESS);
}

/*
** Delete the file and call refresh_window to recalculate padding
*/

static void	deletekey(t_select *env)
{
	t_list *tmp;

	tmp = addr_selected_file(env->files);
	if (tmp->next)
		((t_file *)tmp->next->content)->cursor = 1;
	else
		((t_file *)env->files->content)->cursor = 1;
	ft_lstremove(&env->files, ft_lstindex(env->files, tmp), &destroy_file);
	refresh_window(env);
}

/*
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
	else if (buf[0] == '\033')
	{
		if (buf[1] == '\0')
			wrap_exit(env, EXIT_SUCCESS);
		else if (buf[1] == '[')
		{
			if (buf[2] == 'A') 	//upkey
				move_cursor(-FBL, env);
			else if (buf[2] == 'B')	//downkey
				move_cursor(FBL, env);
			else if (buf[2] == 'C') //rightkey
				move_cursor(1, env);
			else if (buf[2] == 'D') //leftkey
				move_cursor(-1, env);
		//	else if (buf[2] == '3' && buf[3] == '~') // delete key ?
		//		deletekey(env);
		}
	}
}
