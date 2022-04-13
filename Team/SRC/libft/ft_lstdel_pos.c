/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:40:29 by yang              #+#    #+#             */
/*   Updated: 2022/04/13 13:12:33 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstdel_pos(t_list **head, int pos)
{
	t_list	*temp;
	t_list	*del;
	int		i;

	i = 0;
	temp = *head;
	if (pos == 0)
		return ;
	if (pos == 1)
	{
		*head = temp->next;
		temp->next = NULL;
		free(temp->content);
		free(temp);
	}
	else
	{
		while (++i < pos - 1)
			temp = temp->next;
		del = temp->next;
		temp->next = temp->next->next;
		del->next = NULL;
		free(del->content);
		free(del);
	}
}