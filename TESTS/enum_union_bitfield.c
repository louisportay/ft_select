/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_union_bitfield.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 16:39:25 by lportay           #+#    #+#             */
/*   Updated: 2017/10/04 14:58:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>

enum	e_interrupt
{
//	SIGINT,
//	SIGQUIT,
//	SIGILL,
//	SIGABRT,
//	SIGFPE,
	sigkill,
//	SIGSEGV,
	sigstop,
};

union	u_pouet /* Apply padding by 8 */
{
	char	a[17];
	int	b;
	double	c;
};

typedef struct	s_2bool
{
	bool a : 1;
	bool b : 1;
	bool c : 1;
	bool d : 1;
	bool e : 1;
	bool f : 1;
	bool g : 1;
	int h : 12;
}		t_2bool;

int main(void)
{
//	t_2bool a;
//	a.h = 2;
//	printf("%d\n", a.h);
//	a.h = 4096;
//	printf("%d\n", a.h);
//	char a = SIGSEGV;
//	printf("%d\n", a);
	
//	printf("%lu\n", sizeof(struct winsize));
	if (tgetent(NULL, NULL) == ERR)
		printf("KO\n");
	perror(NULL);
//	printf("%lu\n", sizeof(t_2bool));
}
