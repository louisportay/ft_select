/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:26:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 19:16:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** init self-values
*/

static void	setenv_select(t_select *env)
{
	env->tios.c_lflag &= ~(ICANON);
	env->tios.c_lflag &= ~(ECHO);
	env->tios.c_cc[VMIN] &= 1;
	env->tios.c_cc[VTIME] &= 0;
	T_FILE(env->files->content)->cursor = 1;
	ft_bzero(env->buf, 256);
	env->buf_index = 0;
	env->color = true;
	env->print_buf = false;
	//SET LE CF, le CM et le NB_FILE
}

/*
** Tests whether all the system attributes are present to work properly
*/

static char init(t_select *env, int ac, char **av)
{
	char *tmp;

	if (ac < 2 || ft_strcmp(av[1], "--help") == 0)
		return (NOINPUT);
	else if (ft_strcmp(av[1], "--key") == 0)
		return (KEY);
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
	fill_lst(env, ++av);
	if (!env->files)
		return (SHITTYINPUT);
	setenv_select(env);
	return (SUCCESS);
}

/*
** Main function for ft_select
*/

void	ft_select(int ac, char **av)
{
	t_select	env;
	char		buf[4];
	char		ret;

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
