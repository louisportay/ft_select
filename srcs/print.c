/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/10 21:22:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

//	GERER LE PADDING ET LE MESSAGE DE FENETRE TROP PETITE

void	display(t_select *env)
{
	t_list	*tmp;
	int	i;

	tmp = env->files;
	i = 0;
	while (tmp != NULL)
	{
		ft_printf("%-*s", MINCOL, ((t_file *)tmp->content)->filename);
		i++;
		if (i == env->filesbyline)
		{
			ft_putchar('\n');
			i = 0;
		}
		tmp = tmp->next;
	}
}

void	print_files(t_select *env)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	refresh_window(env);
	printf("%d\n", MINCOL);
//	ft_printf("\nMINCOL=%d\nFBL=%d\n", MINLIN, FBL);

//	ft_putnbr(MINLIN);
//	ft_putchar('\n');
//	ft_putnbr(env->ws.ws_row);
//	ft_putchar('\n');

//	if (FBL <= 0 || MINLIN > env->ws.ws_row)
//		ft_putstr("Too small window\n");
//	else
//		display(env);
}
