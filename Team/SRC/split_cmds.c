/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:25:35 by yang              #+#    #+#             */
/*   Updated: 2022/04/18 09:23:36 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

int	count(char *str, char c);

int	check_pipe(char *str)
{
	char	**check;
	int		i;
	int		j;
	int		len;

	len = count(ft_strtrim(str, " "), ' ');
	check = ft_split_str(str, ' ');
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (j < (int)ft_strlen(check[i]) && check[i][++j] != '\0')
		{
			if (check[i][j] == '|')
			{
				if ((j < (int)ft_strlen(check[i]) - 1 && check[i][j + 1] == '|')
					|| (i < len - 1 && check[i + 1][0] == '|'))
					return (-1);
			}
			else if (is_quote(check[i][j]))
				j = in_quote(check[i], j);
		}
	}
	if (check[--i][--j] == '|')
		return (-1);
	return (0);
}

int	count(char *str, char c)
{
	int	total;
	int	i;

	i = -1;
	total = 1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			total++;
			while (i < (int)ft_strlen(str) - 2 && str[i + 1] == c)
				i++;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
		if (i == -1)
			return (-1);
	}
	return (total);
}

/* separate user input into each cmd by c */
char	**ft_split_str(char *str, char c)
{
	char	**w_split;
	int		start_pos;
	int		i;
	int		j;

	w_split = malloc(sizeof(char *) * (count(str, c) + 1));
	if (!w_split)
		return (NULL);
	start_pos = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			w_split[++j] = ft_strndup(str + start_pos, i - start_pos);
			while (i < (int)ft_strlen(str) - 2 && str[i + 1] == c)
				i++;
			start_pos = i + 1;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
	}
	w_split[++j] = ft_strndup(str + start_pos, i - start_pos);
	w_split[++j] = NULL;
	return (w_split);
}

void	free_malloc(char **array)
{
	int	i;

	i = -1;
	while (!array[++i])
		free(array[i]);
	free(array);
}
