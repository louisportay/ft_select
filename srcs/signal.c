/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 18:25:18 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 17:16:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	hardexit(int signum, t_select *env)
{
	static t_select *envaddr = NULL;
	
	if (envaddr == NULL)
	{
		envaddr = env;
		return ; 
	}
	
// restore the terminal and free your stuff... Bleah bleah

	restore(envaddr);
	signal(SIGINT, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	raise(signum);
}

/*
** Restore the previous Terminal Configuration
*/

void	restore(t_select *env)
{
	ft_lstdel(&env->files, destroy_file);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &env->oldtios);
}

void	sighandler(int signum, siginfo_t *siginfo, void *context)
{
(void)signum;
(void)siginfo;
(void)context;

	if (signum == SIGSEGV || signum == SIGINT)
		hardexit(signum, NULL);		
}

void	wrap_sigaction(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &sighandler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

//	sigaction(SIGKILL, &sa, NULL);
//	sigaction(SIGSTOP, &sa, NULL);

	sigaction(SIGWINCH, &sa, NULL);
	sigaction(SIGCONT, &sa, NULL);

	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGTRAP, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
}

