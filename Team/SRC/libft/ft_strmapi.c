/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:37:06 by yang              #+#    #+#             */
/*   Updated: 2021/05/15 18:01:10 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	length;
	size_t	i;
	char	*ptr;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * length + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
