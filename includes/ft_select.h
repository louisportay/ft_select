/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 15:03:40 by lportay           #+#    #+#             */
/*   Updated: 2017/10/04 17:31:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>

/*
** Minimum Column Width (for Padding)
*/

# define MCW 8

/*
** Characters and escape sequences
*/

# define SPACE ' '
# define ESC 27

/*
** Error strings
*/

#define NOINPUT_STR "Usage: ft_select [FILE]...\n"
#define NOTERM_STR "TERM environment variable not set.\n"
#define NOTERMDB_STR "No database found for this terminal.\n"
#define NOATTR_STR "Couldn't retrieve terminal attributes.\n"
#define NOWINDOW_STR "Couldn't retrieve window attributes.\n"

enum	e_errcode
{
	SUCCESS,
	NOINPUT,
	NOTERM,
	NOTERMDB,
	NOATTR,
	NOWINDOW,
};

typedef struct		s_files
{
	char		*filename;
//	int		select;
//	int		cursor;	
}			t_files;

typedef struct		s_select
{
	struct termios	tios;
	struct termios	oldtios;
	struct winsize	ws;
	t_list		*files;
	unsigned char	max_len;	
}			t_select;

void	ft_select(int ac, char **av);
void	fatal_err(int errcode);

#endif
