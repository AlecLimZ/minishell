/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:32:15 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 22:41:44 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sum_length;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	sum_length = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * sum_length + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	ft_strlcat(ptr, s2, sum_length + 1);
	return (ptr);
}
