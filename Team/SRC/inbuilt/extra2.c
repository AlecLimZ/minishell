/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:21:30 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 16:25:26 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_freestr(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

char	*ft_stringenv(char *s, char *tmp, int *cur)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = ft_get_envp(cur, s + *cur);
	if (!tmp2)
		return (ft_freestr(tmp));
	return (tmp2);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst || !src)
		return (dst);
	while (++i < len)
		dst[i] = '\0';
	i = -1;
	while (++i < len && src[i] != '\0')
		dst[i] = src[i];
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
