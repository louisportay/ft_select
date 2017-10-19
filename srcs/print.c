/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 17:39:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Look for an extension at the end of the filename and print the corrsponding
** color sequence
*/

void	check_extension(char *filename)
{
	char *tmp;

	if ((tmp = ft_strstr(filename, ".c")) && (*(tmp + 2) == '\0'))
		ft_putstr(BLUE);
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

static void	activate_print_options(t_file *file, bool color)
{
	struct stat buf;

	if (color == true)
	{
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
	ft_putstr(DEFAULT);
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
		activate_print_options((t_file *)tmp->content, env->color);
		ft_putstr_fd(STDIN_FILENO, ((t_file *)tmp->content)->filename);
		deactivate_print_options((t_file *)tmp->content);
		ft_putnchar_fd(STDIN_FILENO, ' ', MINCOL - ft_strlen(((t_file *)tmp->content)->filename));
		if ((++i % env->filesbyline) == 0)
			write(STDIN_FILENO, "\n", 1);
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
		display(env);
	//	tputs(tgetstr("do", NULL), 1, ft_putchar_stdin);
	//	tputs(tgetstr("DO", NULL), env->ws.ws_row - MINLIN, ft_putchar_stdin);	
	//	ft_putnchar_fd(STDIN_FILENO, '\n', env->ws.ws_row - MINLIN);
		ft_putstr_fd(STDIN_FILENO, env->buf);//
	}
	else
		ft_putstr_fd(STDIN_FILENO, "Too small window\n");

}
