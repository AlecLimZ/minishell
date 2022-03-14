/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:37:56 by yang              #+#    #+#             */
/*   Updated: 2021/10/26 10:13:09 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;
	
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = *lst;
		new->next = *lst;
	}
	else
	{
		temp = *lst;
		new->prev = *lst;
		new->next = temp->next;
		temp->next->prev = new;
		temp->next = new;
	}
}
