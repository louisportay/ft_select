/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 18:25:18 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 10:31:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static bool	isthistheend(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGTERM
		|| signum == SIGILL || signum == SIGTRAP || signum == SIGABRT
		|| signum == SIGFPE || signum == SIGBUS || signum == SIGSEGV)
		return (true);
	return (false);
}

static void	redraw_window(t_select *env)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws);
	refresh_window(env);
	print_files(env);
}

/*
** Perform different actions for the signal sent
** faking SIGTSTP with ioctl call is bad practice, here's a real SIGTSTP handler
*/

void		sig_switch(int signum, t_select *env)
{
	static t_select *envaddr = NULL;
	
	if (isthistheend(signum) == true)
		restore_term(envaddr, true);
	else if (signum == SIGWINCH)
		return (redraw_window(envaddr));
	else if (signum == SIGTSTP)
	{
		signal(SIGCONT, &sighandler);
		restore_term(envaddr, false);
	}
	else if	(signum == SIGCONT)
	{
		signal(SIGTSTP, &sighandler);
		select_term(envaddr);
		print_files(envaddr);
	}
	signal(signum, SIG_DFL);
	kill(0, signum);//
	if (envaddr == NULL)
		envaddr = env;
}

void	sighandler(int signum)
{
	sig_switch(signum, NULL);
}

void		wrap_signal(void)
{
	signal(SIGTSTP, &sighandler);
	signal(SIGCONT, &sighandler);
	signal(SIGWINCH, &sighandler);
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGILL, &sighandler);
	signal(SIGTRAP, &sighandler);
	signal(SIGABRT, &sighandler);
	signal(SIGFPE, &sighandler);
	signal(SIGBUS, &sighandler);
	signal(SIGSEGV, &sighandler);
}
