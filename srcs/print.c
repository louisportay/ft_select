/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 20:29:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Look for an extension at the end of the filename and print the corrsponding
** color escape sequence
*/

void	check_extension(char *filename)
{
	char *tmp;

	if ((tmp = ft_strstr(filename, ".c")) && (*(tmp + 2) == '\0'))
		ft_putstr(BLUE);
	if ((tmp = ft_strstr(filename, ".o")) && (*(tmp + 2) == '\0'))
		ft_putstr(CYAN);
	else if ((tmp = ft_strstr(filename, ".h")) && (*(tmp + 2) == '\0'))
		ft_putstr(DARK_GRAY);
	else if ((tmp = ft_strstr(filename, ".out")) && (*(tmp + 4) == '\0'))
		ft_putstr(RED);
	else if ((tmp = ft_strstr(filename, ".py")) && (*(tmp + 3) == '\0'))
		ft_putstr(LIGHT_GREEN);
	else if ((tmp = ft_strstr(filename, ".php")) && (*(tmp + 4) == '\0'))
		ft_putstr(YELLOW);
	else if ((tmp = ft_strstr(filename, ".cpp")) && (*(tmp + 4) == '\0'))
		ft_putstr(LIGHT_MAGENTA);
	else if ((tmp = ft_strstr(filename, ".rb")) && (*(tmp + 3) == '\0'))
		ft_putstr(LIGHT_RED);
}

/*
** This could be done with escape sequences as well, but it's a termcaps project
** Activate underline and/or reverse video printing and/or colors
*/

static void	activate_print_options(t_file *file, t_select *env)
{
	struct stat buf;

	if (env->color == true)
	{
		if (env->dirmode == 1 || access(file->filename, F_OK) == 0)
		{
			buf.st_mode = 0;
			lstat(file->filename, &buf);
			if (S_ISDIR(buf.st_mode))
				ft_putstr(LIGHT_BLUE);
			else if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
				ft_putstr(LIGHT_YELLOW);
			else if (S_ISLNK(buf.st_mode))
				ft_putstr(LIGHT_CYAN);
			else
				check_extension(file->filename);
		}
		else
			ft_putstr(ITALIC);
	}
	if (file->select & 1)
		tputs(tgetstr("mr", NULL), 1, ft_putchar_stdin);
	if (file->cursor & 1)
		tputs(tgetstr("us", NULL), 1, ft_putchar_stdin);
}

/*
** Deactivate underline and/or reverse video printing and/or colors
*/

static void	deactivate_print_options(t_file *file)
{
	ft_putstr(RESET);
	if (file->select & 1)
		tputs(tgetstr("me", NULL), 1, ft_putchar_stdin);
	if (file->cursor & 1)
		tputs(tgetstr("ue", NULL), 1, ft_putchar_stdin);
}

/*
** Print the filenames correctly (in the right order, with padding and termcaps)
*/

static void	display(t_select *env)
{
	t_list	*tmp;
	int	i;

	tmp = env->files;
	i = 0;
	while (tmp != NULL)
	{
		if (T_FILE(tmp->content)->match == 1)
		{
			activate_print_options((t_file *)tmp->content, env);
				ft_putstr_fd(STDIN_FILENO, T_FILE(tmp->content)->filename);
			deactivate_print_options((t_file *)tmp->content);
			ft_putnchar_fd(STDIN_FILENO, ' ', MINCOL - ft_strlen(T_FILE(tmp->content)->filename));

			if ((++i % env->filesbyline) == 0)
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
		if (addr_first_matched_file(env->files))//virer ca
			display(env);
		else
			ft_putstr_fd(STDIN_FILENO, BOLD"No Match"RESET);
		if (env->print_buf == true)
			ft_printf("\033[%d;0H%s", env->ws.ws_row, env->buf);
	}
	else
		ft_putstr_fd(STDIN_FILENO, BLUE"\'Too "WHITE"Small"RED" Window\'\n"
					BLUE"by the "WHITE"\'French Tech"RED"Club\' ©"\n"DEFAULT);
}
