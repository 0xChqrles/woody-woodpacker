/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 04:31:17 by clanier           #+#    #+#             */
/*   Updated: 2016/11/06 06:13:04 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*begin;

	if (!lst)
		return (NULL);
	begin = ft_lstnew(lst->content, lst->content_size);
	begin = f(lst);
	new = begin;
	while (lst->next)
	{
		new->next = f(lst->next);
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (begin);
}
