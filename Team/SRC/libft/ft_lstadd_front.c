/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:37:56 by yang              #+#    #+#             */
/*   Updated: 2022/04/11 16:28:52 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;
	
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = *lst;
	}
	else
	{
		temp = *lst;
		new->next = temp;
		*lst = new;
		//temp->next = new;
	}
}
