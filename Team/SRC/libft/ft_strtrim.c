/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:55:15 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 22:40:51 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_set(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

static int	mem_size(const char *s1, const char *set)
{
	int	s1_len;
	int	mem_len;
	int	i;

	s1_len = ft_strlen(s1);
	i = 0;
	mem_len = s1_len;
	while (is_set(s1[i], set))
	{
		mem_len--;
		i++;
	}
	i = 0;
	while (is_set(*(s1 + s1_len - 1), set))
	{
		mem_len--;
		s1_len--;
	}
	if (mem_len < 0)
		mem_len = 0;
	return (mem_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	i;
	size_t	i_last;
	char	*ptr;

	if (!s1)
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	i = 0;
	i_last = 0;
	ptr = (char *)malloc(sizeof(char) * (mem_size(s1, set)) + 1);
	if (ptr == NULL)
		return (NULL);
	if (*set == '\0')
	{
		ft_strlcpy(ptr, s1, s1_len + 1);
		return (ptr);
	}
	while (is_set(*(s1 + i), set))
		i++;
	while (is_set(*(s1 + s1_len - 1 - i_last), set))
		i_last++;
	ft_strlcpy(ptr, s1 + i, s1_len - i - i_last + 1);
	return (ptr);
}
