/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:29:55 by yang              #+#    #+#             */
/*   Updated: 2021/05/29 10:10:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2 || n == 0)
		return (0);
	c1 = *s1;
	c2 = *s2;
	while ((c1 != '\0' || c2 != '\0') && n--)
	{
		if (c1 != c2)
			break ;
		c1 = *s1++;
		c2 = *s2++;
	}
	return (c1 - c2);
}
