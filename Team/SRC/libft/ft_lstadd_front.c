/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:37:56 by yang              #+#    #+#             */
/*   Updated: 2022/05/05 15:59:08 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

//void	ft_lstadd_front(t_list **lst, t_list *new)
//{
//	if (!new || !lst)
//		return ;
//	if (!*lst)
//	{
//		*lst = new;
//		new->next = *lst;
//	}
//	else
//	{
//		temp = *lst;
//		new->next = *lst;
//		*lst = new;
//		temp->next = new;
//	}
//}
