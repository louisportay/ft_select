/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 19:51:25 by lportay           #+#    #+#             */
/*   Updated: 2017/09/26 18:39:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <curses.h> // def ERR macro
#include <termios.h>
#include <term.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

/*
 ** Read 'man termios' + 'man termcap' + 'man tcgetattr'
 */

void wrap_exit(/*char *err,*/ int status)
{
//	if (err)
//		ft_putstr(err);
//		ft_putstr("kek");
	exit(status);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
//	char *str;
//	(void)str;
//	struct termios	term;
//	char *tty;
//	(void)tty;
//	struct termios termios_p;

//	if (isatty(0) == 1)
//		printf("STDIN is a tty\n");
//	else
//		printf("STDIN is not a tty\n");
//	tty = ttyname(0);
//	perror(NULL);
//	printf("%s\n", tty);
//
//	avoid 'ioctl' it's non-standard
//
//	getenv return 'Value' of the 'key' in environment array
//
//	tcgetattr remplit le struct termios (passer l'adresse)
//	tcsetattr applique les changements de la struct termios
//	tgetflag, tgetnum et tgetstr retrievent les vlaues associes aux id definies dans le termninal
//	tputs output sur le screen les modif graphiques
//	tgoto bouge ton curseur et encode des trucs apparament
//
//	tcgetattr(0, &termios_p);
//	if (tgetent(NULL, getenv("TERM")) != 1)
//		exit(-1);
//	printf("%d\n", tgetflag("xn"));
//	printf("%d\n", tgetnum("co"));
//	printf("%d\n", tgetnum("li"));
//	str = tgetstr("cm", NULL);
//	tputs(tgoto(str, 15, 22), 0, putchar);


	int	term_fd = STDIN_FILENO;
	struct	termios s;
	struct	termios restore;
	char	buf[33];
//	char	*str_cl;
	char	*str_nd;
	char	*str_le;
	char	*str_up;

	if (tgetent(NULL, getenv("TERM")) != 1)
		wrap_exit(-1);
	if (isatty(term_fd) == 0)
		wrap_exit(-1);
	if (tcgetattr(term_fd, &s) == -1)
		wrap_exit(-1);
	if (tcgetattr(term_fd, &restore) == -1)
		wrap_exit(-1);

	s.c_lflag &= ~(ICANON);
	s.c_lflag &= ~(ECHO);
	s.c_cc[VMIN] = 1;
	s.c_cc[VTIME] = 0;
	if (tcsetattr(term_fd, TCSADRAIN, &s) == -1)
		wrap_exit(-1);

//	read(0, buf, 3);
//	if (buf[0] == 27 && buf[2] == 'A')
//		puts("\nFLECHE HAUTE\n");
//	else if (buf[0] == 27 && buf[2] == 'B')
//		puts("\nFLECHE BASSE\n");
//	else if (buf[0] == 27 && buf[2] == 'C')
//		puts("\nFLECHE DROITE\n");
//	else if (buf[0] == 27 && buf[2] == 'D')
//		puts("\nFLECHE GAUCHE\n");

//	str_cl = tgetstr("cl", NULL);
//	tputs(str_cl, 0, putchar);
//	str_nd = tgetstr("nd", NULL);
	(void)str_nd;
//	tputs(str_nd, 0, putchar);
//	str_le = tgetstr("le", NULL);
	(void)str_le;
//	(void)str_cl;
//	tputs(str_le, 0, putchar);
//	str_up = tgetstr("up", NULL);
	(void)str_up;
//	tputs(str_up, 0, putchar);
//	tgetstr("kr", NULL);
//	tputs(tgoto(tgetstr("cm", NULL), 20, 20), 0, putchar);
//	tputs(tgetstr("nd", NULL), 0, putchar);
//	read(0, buf, 3);
//	tputs(tgetstr("ue", NULL), 0, ft_putchar);
	tputs(tgetstr("us", NULL), 0, ft_putchar);
	buf[32] = '\0';
	while (1)
	{
		read(0, buf, 32);
		if (buf[0] == 4)
			break ;
		puts(buf);
	}
	tputs(tgetstr("ue", NULL), 0, ft_putchar);
	
//	struct winsize ws;
//	while (1)
//	{
//		printf("%d\n", tgetnum("co"));
//		ioctl(0, TIOCGWINSZ, &ws);
//		printf("col = %d -- lin = %d\n", ws.ws_col, ws.ws_row);
//		sleep(1);
//	}
	

//	restore.c_lflag |= (ECHO | ICANON);
	if (tcsetattr(term_fd, TCSADRAIN, &restore) == -1)
		wrap_exit(-1);
}
