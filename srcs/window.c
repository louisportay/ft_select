/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 19:51:54 by lportay           #+#    #+#             */
/*   Updated: 2017/10/18 20:37:52 by lportay          ###   ########.fr       */
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
		if (len >= col_w)
			col_w = ((len % MCW) ? ((len / MCW) * MCW): len) + MCW;
	}
	return (col_w);
}

/*
** Return the number of files a line can hold
** if return 0, it's an Error
*/

static int	max_files_on_a_line(int ws_col, int min_col)
{
	return (ws_col / min_col);
}

/*
** Return the minimum number of lines to print
*/

static int	min_lines(int n_files, int fbl)
{
	return ((n_files % fbl) == 0 ? (n_files / fbl) : (n_files / fbl) + 1);
}

/*
** Get the new parameters for winsize and the printing of files (new padding)
**
** This function is called for 2 reasons:
** -Screen resizing
** -File Deletion
*/

void	refresh_window(t_select *env)
{
	MINCOL = longest_arg(env->files);
	if ((FBL = max_files_on_a_line(env->ws.ws_col, env->min_col)) == 0)
		MINLIN = -1;
	else
		MINLIN = min_lines(ft_lstcount(env->files), FBL);
}
