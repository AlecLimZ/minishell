/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:01:30 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 22:40:06 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static int	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	count_sep(char const *s, char c)
{
	int	j;

	j = 0;
	while (s[j] == c)
		j++;
	return (j);
}

static char	**check_empty(char **word, int j)
{
	char	**w_split;
	int		index;

	w_split = word;
	index = j;
	if (w_split[index] == NULL)
	{
		while (--index >= 0)
			free(w_split[index]);
		free(w_split);
		return (NULL);
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**w_split;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	word_count = count(s, c);
	w_split = (char **)malloc(sizeof(char *) * word_count + 1);
	if (w_split == NULL)
		return (NULL);
	while (word_count--)
	{
		i = i + count_sep(s + i, c);
		w_split[++j] = (char *)malloc(sizeof(char) * word_length(s + i, c) + 1);
		if (check_empty(w_split, j) == NULL)
			return (NULL);
		ft_strlcpy(w_split[j], s + i, word_length(s + i, c) + 1);
		i = i + word_length(s + i, c);
	}
	w_split[++j] = NULL;
	return (w_split);
}
