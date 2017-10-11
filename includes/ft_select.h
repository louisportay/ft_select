/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 15:03:40 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 18:05:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <stdbool.h>

/*
** Minimum Column Width (for Padding)
** NEVER SET THIS VALUE TO 0 (unless you want to get a FPE...)
*/

# define MCW 8

/*
** Characters and escape sequences
*/

#define MINCOL env->min_col
#define FBL env->filesbyline
#define MINLIN env->min_lines

/*
** Error strings
*/

#define	NOINPUT_STR	"Usage: ft_select [FILE]...\n"
#define	NOTERM_STR	"TERM environment variable not set.\n"
#define	NOTERMDB_STR	"No database found for this terminal.\n"
#define	NOATTR_STR	"Couldn't retrieve terminal attributes.\n"
#define	NOWINDOW_STR	"Couldn't retrieve window attributes.\n"
#define	SHITTYINPUT_STR	"The input sent is invalid, Use a filename instead\n"

enum	e_errcode
{
	SUCCESS,
	NOINPUT,
	NOTERM,
	NOTERMDB,
	NOATTR,
	NOWINDOW,
	SHITTYINPUT,
};

typedef struct		s_file
{
	char		*filename;
	unsigned char	select : 1;
	unsigned char	cursor : 1;
}			t_file;

/*
** min_col == la largeur minimum d'une colonne pour imprimer le nom de tous les 
**	      fichiers, le padding ajouté au plus long nom de fichier peut-etre
**	      changé avec la macro MCW
** filesbyline == le nombre de fichiers qu'une ligne peut contenir, depend de
**		  la largeur ws_col et de min_col
** min_lines == le nombre minimum dont doit disposer le terminal pour imprimer
**		le nom de tous les fichiers, depend de filesbyline et du nombre
**		de fichiers passe au programme
*/

typedef struct		s_select
{
	struct termios	tios;
	struct termios	oldtios;
	struct winsize	ws;

	t_list		*files;

	unsigned char	min_col;
	unsigned char	filesbyline;
	unsigned char	min_lines;
}			t_select;

void	ft_select(int ac, char **av);

void	fatal_err(int errcode);
void	wrap_exit(t_select *env, int status);

void	sig_switch(int signum, t_select *env);
void	wrap_signal(void);
void	sighandler(int signum);

void	restore_term(t_select *env, bool del);
void	select_term(t_select *env);

t_file	*new_file(char *filename);
void	destroy_file(void *content, size_t content_size);
void	fill_lst(t_list **files, char **av);

void	print_files(t_select *env);
void	refresh_window(t_select *env);

void	user_input(char *buf, t_select *env);

void	uparrowkey(void);
void	downarrowkey(void);
void	leftarrowkey(void);
void	rightarrowkey(void);

#endif
