/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:52:54 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 23:14:06 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*hold;
	t_list	*elem;

	if ((!f && !del) || !lst)
		return (NULL);
	hold = NULL;
	while (lst)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
			ft_lstclear(&hold, del);
		ft_lstadd_back(&hold, elem);
		lst = lst->next;
	}
	return (hold);
}
