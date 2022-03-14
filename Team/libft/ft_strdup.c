/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:16:12 by yang              #+#    #+#             */
/*   Updated: 2021/05/09 23:32:35 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		length;

	length = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * length + 1);
	if (dest == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memcpy(dest, s1, length + 1);
	return (dest);
}
