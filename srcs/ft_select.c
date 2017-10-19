/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:26:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 13:46:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Tests whether all the system attributes are present to work properly and init
** self-values
*/

static int init(t_select *env, int ac, char **av)
{
	char *tmp;

	if (ac < 2)
		return (NOINPUT);
	if ((tmp = getenv("TERM")) == NULL)
		return (NOTERM);
	if (tgetent(NULL, tmp) == ERR)
		return (NOTERMDB);
	if (tcgetattr(STDIN_FILENO, &env->tios) == -1)
		return (NOATTR);
	if (tcgetattr(STDIN_FILENO, &env->oldtios) == -1)
		return (NOATTR);
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws) == -1)
		return (NOWINDOW);
	env->tios.c_lflag &= ~(ICANON);
	env->tios.c_lflag &= ~(ECHO);
	env->tios.c_cc[VMIN] &= 1;
	env->tios.c_cc[VTIME] &= 0;
	fill_lst(&env->files, ++av);
	if (!env->files)
		return (SHITTYINPUT);
	((t_file *)env->files->content)->cursor = 1;
	ft_bzero(env->buf, 255);
	env->color = true;
	return (SUCCESS);
}

/*
** Main function for ft_select
*/

void	ft_select(int ac, char **av)
{
	t_select	env;
	int 		ret;
	char		buf[4];

	if ((ret = init(&env, ac, av)) != SUCCESS)
		fatal_err(ret);
	sig_switch(0, &env);
	wrap_signal();
	select_term(&env);
	refresh_window(&env);
	while (1)
	{
		print_files(&env);
		ft_bzero(buf, 4);
		read(STDIN_FILENO, buf, 4);
		user_input(buf, &env);
	}
}
