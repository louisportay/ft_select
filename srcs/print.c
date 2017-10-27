/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/27 23:42:21 by lportay          ###   ########.fr       */
/*   Updated: 2017/10/25 20:29:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Look for an extension at the end of the filename and print the corrsponding
** color escape sequence
*/

static void	print_colors(t_file *file)
{
	char *tmp;

	if (S_ISDIR(file->st_mode))
		ft_putstr_fd(STDIN_FILENO, LIGHT_BLUE);
	else if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		ft_putstr_fd(STDIN_FILENO, LIGHT_YELLOW);
	else if (S_ISLNK(file->st_mode))
		ft_putstr_fd(STDIN_FILENO, LIGHT_CYAN);
	else if ((tmp = ft_strstr(file->filename, ".c")) && (*(tmp + 2) == '\0'))
		ft_putstr_fd(STDIN_FILENO, BLUE);
	else if ((tmp = ft_strstr(file->filename, ".o")) && (*(tmp + 2) == '\0'))
		ft_putstr_fd(STDIN_FILENO, CYAN);
	else if ((tmp = ft_strstr(file->filename, ".h")) && (*(tmp + 2) == '\0'))
		ft_putstr_fd(STDIN_FILENO, DARK_GRAY);
	else if ((tmp = ft_strstr(file->filename, ".out")) && (*(tmp + 4) == '\0'))
		ft_putstr_fd(STDIN_FILENO, RED);
	else if ((tmp = ft_strstr(file->filename, ".py")) && (*(tmp + 3) == '\0'))
		ft_putstr_fd(STDIN_FILENO, LIGHT_GREEN);
	else if ((tmp = ft_strstr(file->filename, ".php")) && (*(tmp + 4) == '\0'))
		ft_putstr_fd(STDIN_FILENO, YELLOW);
	else if ((tmp = ft_strstr(file->filename, ".cpp")) && (*(tmp + 4) == '\0'))
		ft_putstr_fd(STDIN_FILENO, LIGHT_MAGENTA);
	else if ((tmp = ft_strstr(file->filename, ".rb")) && (*(tmp + 3) == '\0'))
		ft_putstr_fd(STDIN_FILENO, LIGHT_RED);
}

/*
** Activate underline and/or reverse video printing and/or colors
**
** Underline and reverse-video mode could be done with escape sequences as well,
** But it's a termcaps project infortunately...
*/

static void	activate_print_options(t_select *env, t_file *file)
{
	if (env->color == true)
	{
		if (file->exist)
			print_colors(file);
		else
			ft_putstr_fd(STDIN_FILENO, ITALIC);
	}
	if (file->select & 1)
		tputs(env->mr, 1, ft_putchar_stdin);
	if (file->cursor & 1)
		tputs(env->us, 1, ft_putchar_stdin);
}

/*
** Deactivate underline and/or reverse video printing and/or colors
*/

static void	deactivate_print_options(t_select *env, t_file *file)
{
	ft_putstr_fd(STDIN_FILENO, RESET);
	if (file->select & 1)
		tputs(env->me, 1, ft_putchar_stdin);
	if (file->cursor & 1)
		tputs(env->ue, 1, ft_putchar_stdin);
}

/*
** Print the filenames correctly (in the right order, with padding and termcaps)
*/

static void	display(t_select *env)
{
	t_list		*tmp;
	unsigned short	i;

	tmp = env->files;
	i = 0;
	while (tmp != NULL)
	{
		if (T_FILE(tmp->content)->match)
		{
			activate_print_options(env, T_FILE(tmp->content));
				ft_putstr_fd(STDIN_FILENO, T_FILE(tmp->content)->filename);
			deactivate_print_options(env, T_FILE(tmp->content));
			ft_putnchar_fd(STDIN_FILENO, ' ', MINCOL - ft_strlen(T_FILE(tmp->content)->filename));
			if ((++i % FBL) == 0)
				write(STDIN_FILENO, "\n", 1);
		}
		tmp = tmp->next;
	}
}

/*
** Exit if no files left in the list, print error message if window's too small
** Call the printing function if everything's OK
**
** This function get called many times over the program's life
*/

void	print_files(t_select *env)
{
	if (ft_lstcount(env->files) == 0)
		wrap_exit(env, EXIT_SUCCESS);
	tputs(tgetstr("cl", NULL), 1, ft_putchar_stdin);
	if (FBL != 0 && MINLIN < env->ws.ws_row)
	{
		if (FMF)
			display(env);
		else
			ft_putstr_fd(STDIN_FILENO, BOLD"No Match"RESET);
		if (env->print_buf == true)
			ft_printf("\033[%d;0H%s", env->ws.ws_row, env->buf);
	}
	else
		ft_putstr_fd(STDIN_FILENO, BLUE"\'Too "WHITE"Small "RED"Window\'"RESET"©\n");
}
