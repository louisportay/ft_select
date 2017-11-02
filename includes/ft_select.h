/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 15:03:40 by lportay           #+#    #+#             */
/*   Updated: 2017/11/02 09:42:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <dirent.h>

/*
** Minimum Column Width (for Padding)
** NEVER SET THIS VALUE TO 0 (unless you want to get a FPE...)
*/

# define MCW 8

/*
** Macros for managing lists creation and deletion
*/

# define SELECTMODE	1
# define FALSEMODE	0

/*
** Escape sequences, except reverse-video and underline (implemented with termcaps)
*/

# define RESET		"\e[0m"
# define BOLD		"\e[1m"
# define ITALIC		"\e[3m"
# define STRIKETHROUGH	"\e[9m"
# define BLACK		"\e[30m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN		"\e[36m"
# define LIGHT_GRAY	"\e[37m"
# define DEFAULT	"\e[39m"
# define DARK_GRAY	"\e[90m"
# define LIGHT_RED	"\e[91m"
# define LIGHT_GREEN	"\e[92m"
# define LIGHT_YELLOW	"\e[93m"
# define LIGHT_BLUE	"\e[94m"
# define LIGHT_MAGENTA	"\e[95m"
# define LIGHT_CYAN	"\e[96m"
# define WHITE		"\e[97m"

/*
** Error strings
*/

# define NOINPUT_STR	"Usage: ft_select [--key] [--directory] [FILES]\n"
# define NOTERM_STR	"TERM environment variable not set.\n"
# define NOTERMDB_STR	"No database found for this terminal.\n"
# define NOATTR_STR	"Couldn't retrieve terminal attributes.\n"
# define NOWINDOW_STR	"Couldn't retrieve window attributes.\n"
# define SHITTYINPUT_STR "The input sent is invalid, Use a filename instead\n"
# define MISSINGCAPABILITY_STR "Termcap capability missing, exiting now\n"

enum	e_errcode
{
	SUCCESS,
	NOINPUT,
	NOTERM,
	NOTERMDB,
	NOATTR,
	NOWINDOW,
	SHITTYINPUT,
	KEY,
	MISSINGCAPABILITY,
};

typedef struct		s_file
{
	char	*filename;
	int	st_mode;
	bool	match : 1;
	bool	select : 1;
	bool	cursor : 1;
	bool	exist : 1;
}			t_file;

/*
** min_col  ==	la largeur minimum d'une colonne pour imprimer le nom de tous
**		les fichiers, le padding ajouté au plus long nom de fichier
**		peut-etre changé avec la macro MCW
**		MAXCOL = USHRT_MAX
**
** filesbyline == le nombre de fichiers qu'une ligne peut contenir, depend de
**		  la largeur ws_col et de min_col
**		  MAXFBL = 255
** min_lines == le nombre minimum dont doit disposer le terminal pour imprimer
**		le nom de tous les fichiers, depend de filesbyline et du nombre
**		de fichiers passe au programme
**			MAXLINES = 255
**
** first_matched_file == address of the first 't_file' in 'files' list with flag
**			 'match' on
** cursor_file == address of the 't_file' with flag 'cursor' on
**
** matched_files == total number of files with flag 'match' on
**		    MAXFILES = USHRT_MAX
**
** struct termios = 60 bytes
** struct winsize = 8 bytes
*/

typedef struct		s_select
{
	char		buf[256];
	struct termios	tios;
	struct termios	oldtios;
	struct winsize	ws;
	t_list		*files;
	t_list		*dir;
	t_list		*first_matched_file;
	t_list		*cursor_file;
	char		*mr;
	char		*us;
	char		*me;
	char		*ue;
	unsigned short	matched_files;
	unsigned short	min_col;
	unsigned char	filesbyline;
	unsigned char	min_lines;
	unsigned char	buf_index;
	bool		color : 1;
	bool		print_buf : 1;
}			t_select;

/*
** Fast access to env variables
** Easy cast into t_file *
*/

# define FMF		(env->first_matched_file)
# define CF		(env->cursor_file)
# define MATCHED_FILES	(env->matched_files)
# define MINCOL		(env->min_col)
# define FBL		(env->filesbyline)
# define MINLIN		(env->min_lines)
# define BUFI		(env->buf_index)
# define T_FILE(ptr)	((t_file *)ptr)

void	ft_select(int ac, char **av);
void	fatal_err(char errcode);
void	wrap_exit(t_select *env, int status);
void	sig_switch(int signum, t_select *env);
void	wrap_signal(void);
void	sighandler(int signum);
void	restore_term(t_select *env, bool del);
void	select_term(t_select *env);
void	fill_lst(t_select *env, char **av);
void	print_files(t_select *env);
void	refresh_window(t_select *env);
void	user_input(char *buf, t_select *env);
void	move_cursor(short movement, t_select *env);
void	spacekey(t_select *env);
void	enterkey(t_select *env);
void	deletekey(t_select *env);
void	selectallfiles(t_select *env, bool selectype);
void	deletefiles(t_select *env, bool mode);
void	autofill_buffer(t_select *env);
void	fill_buffer(char c, t_select *env);
int	ft_putchar_stdin(int c);
void	wrap_closedir(void *content, size_t len);
t_list	*next_match_on(t_list *lst);
void	reset_cf(t_select *env);
int	remove_filename(char *str);

#endif
