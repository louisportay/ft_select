/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 20:34:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_files(t_select *env)
{
	refresh_window(env);
	//printf("wincol = %d\nwinlin = %d\nmin_col = %d\nFBL = %d\nmin_lin = %d\n", env->ws.ws_col, env->ws.ws_row, MINCOL, FBL, MINLIN);
	if (FBL <= 0 || MINLIN > env->ws.ws_row)
		printf("error: TOO SMALL WINDOW\n");
}
