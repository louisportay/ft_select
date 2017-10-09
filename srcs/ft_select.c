/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:26:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 22:53:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int init(t_select *env, int ac, char **av)
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
	env->tios.c_cc[VTIME] &= 100; // test 0 ?

	fill_lst(&env->files, ++av);	// increment av to remove "./ft_select from the arguments 

	return (SUCCESS);
}

void	ft_select(int ac, char **av)
{
	t_select	env;
	int 		ret;
	char		buf[4];

	if ((ret = init(&env, ac, av)) != SUCCESS)
		fatal_err(ret);
	hardexit(0, &env);
	wrap_sigaction();
	while (1)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar);
		ft_bzero(buf, 4);
		read(STDIN_FILENO, buf, 4);
		user_input(buf);
//		print_files(&env);
	}
}
