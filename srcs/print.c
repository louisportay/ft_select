/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 19:53:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_files(t_select *env)
{
	refresh_window(env);
	if (FBL <= 0 || MINLIN > env->ws.ws_row)
		printf("error: TOO SMALL WINDOW\n");
}
