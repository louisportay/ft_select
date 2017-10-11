/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:21:49 by lportay           #+#    #+#             */
/*   Updated: 2017/10/11 17:13:59 by lportay          ###   ########.fr       */
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
void	ft_putnbr(long n);
int	ft_putchar(int c);
void	ft_putnchar(char c, size_t n);

#endif
