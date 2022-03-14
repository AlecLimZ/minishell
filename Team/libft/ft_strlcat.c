/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:10:15 by yang              #+#    #+#             */
/*   Updated: 2021/05/27 21:08:09 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	length;

	i = 0;
	j = 0;
	length = 0;
	while (dst[j] != '\0')
		j++;
	while (src[length] != '\0')
		length++;
	if (dstsize > j)
	{
		while (src[i] != '\0' && i < dstsize - j - 1)
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
		return (j + length);
	}
	else
		return (length + dstsize);
}
