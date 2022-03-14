/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:15:32 by yang              #+#    #+#             */
/*   Updated: 2021/05/29 10:31:56 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (c == '\0')
		return ((char *)(s + i));
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}
