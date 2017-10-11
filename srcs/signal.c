/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 18:25:18 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:51:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Va falloir normer tout ca
*/

void	sig_switch(int signum, t_select *env)
{
	static t_select *envaddr = NULL;
	
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGTERM ||
	signum == SIGILL ||signum == SIGTRAP ||signum == SIGABRT || signum
		== SIGFPE || signum == SIGBUS || signum == SIGSEGV)
		restore_term(envaddr, true);
	else if (signum == SIGWINCH)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &envaddr->ws);
		refresh_window(envaddr);
		print_files(envaddr);
		return ;		// Default behaviour is not interesting here
	}
	else if (signum == SIGTSTP)	// faking SIGTSTP with a ioctl is shit, here's a real SIGTSTP handler
	{
		signal(SIGCONT, &sighandler); //restore SIGCONT handler for next call
		restore_term(envaddr, false);
	}
	else if	(signum == SIGCONT)
	{
		signal(SIGTSTP, &sighandler); //restore SIGTSTP handler for next call
		select_term(envaddr);
	}

	signal(signum, SIG_DFL);
	raise(signum);//
//	kill(0, signum);// la lutte continue !

	if (envaddr == NULL)
		envaddr = env;
}

void	sighandler(int signum)
{
	sig_switch(signum, NULL);
}

void	wrap_signal(void)
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
