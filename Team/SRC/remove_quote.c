/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:27:45 by yang              #+#    #+#             */
/*   Updated: 2022/04/13 17:59:01 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_char_at(char *str, int index)
{
	char	*p1;
	char	*p2;

	p1 = str + index;
	while (*p1++ = *p2++)
	{
		;
	}
}
void	remove_quotes(t_list *lst)
{
	int	i;
	int	pos;
	int	last;
	char	*temp;
	char	*prefix;
	char	*postfix;
	char	str[MAX];

	i = -1;
	//str = NULL;
	ft_strlcpy(str, lst->content, ft_strlen(lst->content) + 1);
	last = (int)ft_strlen(str);
	printf("removing quote\n");
	// ft_memset(prefix, 0, ft_strlen(prefix));
	// ft_memset(postfix, 0, ft_strlen(postfix));
	while (++i < last && str[i])
	{
		//ft_memset(prefix, 0, sizeof(char *));
		//ft_memset(postfix, 0, sizeof(char *));
		printf("str: %s\n", str);
		if (is_quote(str[i]))
		{
			pos = in_quote(str, i);
			printf("i: %d\t pos: %d\n", i, pos);
			temp = lst->content;
			prefix = ft_strndup(str + i + 1, pos - i - 1);
			printf("prefix: %s\n", prefix);
			postfix = ft_strndup(str + pos + 1, last - pos - 1);
			printf("postfix: %s\n", postfix);
			//ft_strlcpy(postfix, str + pos + 1, last - pos);
			lst->content = ft_strjoin(prefix, postfix);
			free(temp);
			//free(prefix);
			//free(postfix);
			prefix = NULL;
			postfix = NULL;
			i = pos;
			str = lst->content;
		}
	}
}