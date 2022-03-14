/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:01:31 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 22:44:00 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	length;

	length = 0;
	if (*src == '\0')
	{
		*dst = '\0';
		return (0);
	}
	while (src[length] != '\0')
		length++;
	if (dstsize == 0)
		return (length);
	if (dstsize > 0 && *src != '\0')
	{
		i = 0;
		while (dstsize > 0 && src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (length);
}
