/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 16:45:46 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 18:12:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** This could be done with escape sequences as well, but it's a termcap project.
*/

static void	activate_print_options(t_file *file)
{
	if (file->select & 1)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	if (file->cursor & 1)
		tputs(tgetstr("us", NULL), 1, ft_putchar);
}

static void	deactivate_print_options(t_file *file)
{
	if (file->select & 1)
		tputs(tgetstr("me", NULL), 1, ft_putchar);
	if (file->cursor & 1)
		tputs(tgetstr("ue", NULL), 1, ft_putchar);
}

static void	display(t_select *env)
{
	t_list	*tmp;
	int	i;

	tmp = env->files;
	i = 0;
	while (tmp != NULL)
	{
		activate_print_options((t_file *)tmp->content);
		ft_putstr(((t_file *)tmp->content)->filename); // filename
		deactivate_print_options((t_file *)tmp->content);
		ft_putnchar(' ', MINCOL - ft_strlen(((t_file *)tmp->content)->filename)); // padding
		if ((++i % env->filesbyline) == 0)
			ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	print_files(t_select *env)
{
//	if (ft_lstcount(env->files) == 0)
//		wrap_exit(env, EXIT_SUCCESS); 		// When all files has been extermined
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	if (FBL == 0 || MINLIN > env->ws.ws_row)
		ft_putstr("Too small window\n");
	else
		display(env);
}
