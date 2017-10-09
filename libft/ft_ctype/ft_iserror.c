/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iserror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 21:36:39 by lportay           #+#    #+#             */
/*   Updated: 2017/10/09 21:38:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iserror(int signum)
{
	if (signum == SIGILL ||signum == SIGTRAP ||signum == SIGABRT || signum
		== SIGFPE || signum == SIGBUS || signum == SIGSEGV)
		return (1);
	return (0);
}
