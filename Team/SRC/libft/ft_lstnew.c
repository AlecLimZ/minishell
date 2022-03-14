/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:34:28 by yang              #+#    #+#             */
/*   Updated: 2021/10/26 09:38:54 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr == NULL)
		return (NULL);
	ptr->prev = NULL;
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
