/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 19:51:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 19:56:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Get the width of the longest argument and round (add padding) to the superior multiple of 
** MCW (Minimum Column Width)
*/

static int	longest_arg(t_list *lst)
{
	int len;
	int col_w;

	col_w = MCW;
	while (lst)
	{
		len = ft_strlen(((t_file *)(lst->content))->filename);
		lst = lst->next;
		if (len > col_w)
			col_w = (len % MCW) ? ((len / MCW) * MCW)  + MCW : len;
	}
	return (col_w);
}

/*
** Return the number of files a line can hold
** if return 0 --> Error
*/

static int	max_files_on_a_line(int min_col, int ws_col)
{
	return (ws_col / min_col);
}

/*
** Return the minimum number of lines to print
** Dump an error if min_files < ws_row
*/

static int	min_lines(int n_files, int fbl)
{
	return ((n_files % fbl) == 0 ? (n_files / fbl) : (n_files / fbl) + 1);
}

void	refresh_window(t_select *env)
{
	MINCOL = longest_arg(env->files);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws);
	if ((FBL = max_files_on_a_line(env->min_col, env->ws.ws_col)) == 0)
	{
		MINLIN = min_lines(ft_lstcount(env->files), 1);
		return ;
	}
	MINLIN = min_lines(ft_lstcount(env->files), FBL);
}
