/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:32:05 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 19:31:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	print_key(void)
{
	ft_putstr("\nft_select, an "STRIKETHROUGH"outstanding"RESET
" graphical program by "ITALIC"lportay"RESET"\nHere are keys bindings:\n\n"
"Up|Down|Left|Right key <==> Move in the list\n"
"Space <==> Select/Deselect a File\nEnter <==> Return the selection\n"
"'*' <==> Select all Files\n'-' <==> Deselect all Files\n"
"'&' <==> Remove non-existing Files\n"
"'#' <==> Activate/Deactivate color printing\n"
"[Aa-Zz] [0-9] '.' '/' <==> Activate the dynamic search buffer\n"
"'\\' <==> Delete a character in the search buffer\n"
"'?' <==> Print/Hide the search buffer\n"
"'esc' <==> exit the clean way, do not send any output\n"
"'del' 'backspace' <==> will delete an element in the list\n"
"'tab' <==> Trigger auto-completion feature\n");
}
/*
** Big switch to print the right error message
*/

static void	dump_err(char errcode)
{
	if (errcode == NOINPUT)
		ft_putstr(NOINPUT_STR);
	else if (errcode == NOTERM)
		ft_putstr(NOTERM_STR);
	else if (errcode == NOTERMDB)
		ft_putstr(NOTERMDB_STR);
	else if (errcode == NOATTR)
		ft_putstr(NOATTR_STR);
	else if (errcode == NOWINDOW)
		ft_putstr(NOWINDOW_STR);
	else if (errcode == SHITTYINPUT)
		ft_putstr(SHITTYINPUT_STR);
	else if (errcode == KEY)
		print_key();
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode)
{
	dump_err(errcode);
	exit((int)errcode);
}

/*
** Restore term config, free the list and exit
*/

void		wrap_exit(t_select *env, int status)
{
	restore_term(env, true);
	exit(status);
}
