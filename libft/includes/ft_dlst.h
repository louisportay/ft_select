/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:53:15 by lportay           #+#    #+#             */
/*   Updated: 2017/09/26 16:26:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLST_H
# define FT_DLST_H

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*previous;
	struct s_dlist	*next;
}					t_dlist;

t_dlist				*ft_dlstnew(void const *content, size_t content_size);
void				ft_dlstadd(t_dlist **alst, t_dlist *new);
void				ft_dlstaddend(t_dlist **alst, t_dlist *new);
void				ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstremove(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlsthead(t_dlist **dlst);
void				ft_dlstend(t_dlist **dlst);
size_t				ft_dlstcount(t_dlist *dlst);
size_t				ft_dlstindex(t_dlist *dlst);
t_dlist				*ft_dlstaddr(size_t rank, t_dlist *dlst);
void				ft_dlstprint(t_dlist *list);

#endif
