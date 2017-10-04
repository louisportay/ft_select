/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:26:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/04 17:43:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
int	longest_arg(char **av)
{
	int len;
	int col_w;

	col_w = MCW;
	while (*av != NULL)
	{
		len = ft_strlen(*av++);
		if (len > col_w)
		{
			if ((len % MCW) != 0)
				col_w = ((len / MCW) * MCW)  + MCW;
			else
				col_w = len;
		}
	}
	return (col_w);
}

void	epurlst(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content == NULL || tmp->content_size == 0)
		{
			tmp = tmp->next;
			ft_lstremove(lst, ft_lstindex(*lst, tmp) - 1, ft_delvoid);
		}	
		else
			tmp = tmp->next;
	}
}
*/


int init(t_select *env, int ac, char **av)
{
	char *tmp;

(void)av;

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
/* convert and insert the files in env->files*/
	return (0);
}

void	wrap_sigaction()
{
	struct sigaction sa;

	sa.sa_sigaction = &sighandler;
	sa.sa_flags = SA_SIGINFO;
}

int	ft_select(int ac, char **av)
{
	t_select	env;
	int ret;

	if ((ret = init(&env, ac, av)) != SUCCESS)
		fatal_err(ret);
	wrap_sigaction();
	return (0);
//	while (1)
//	{
//		
//	}

//	width = longest_arg(av + 1);
//	lst_av = ft_tabtolst(av + 1);
//	epurlst(&lst_av);

//	ft_lstdel(&lst_av, ft_delvoid);
}
