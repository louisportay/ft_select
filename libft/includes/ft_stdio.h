/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:21:49 by lportay           #+#    #+#             */
/*   Updated: 2017/08/24 21:49:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDIO_H
# define FT_STDIO_H

# include "ft_printf.h"

int		get_next_line(const int fd, char **line);
int		ft_getchar(void);
int		ft_printf(const char *restrict format, ...);
void	ft_putendl(char const *s);
void	ft_putstr(char const *s);
void	ft_putchar(char c);

#endif
