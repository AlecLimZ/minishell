/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:27:45 by yang              #+#    #+#             */
/*   Updated: 2022/05/11 14:59:37 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	remove_quotes(t_list *lst)
{
	char	*str;
	int		i;
	int		close;

	str = lst->content;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			close = in_quote(str, i) - 1;
			ft_memmove(&str[i], &str[i + 1], ft_strlen(str) - i);
			ft_memmove(&str[close], &str[close + 1], ft_strlen(str) - close);
			i = close;
		}
		else
			i++;
		if (i < 0)
			break ;
	}
}

void	replace_expand_str(t_list *head, char *str)
{
	char	*temp;

	temp = head->content;
	if (!str[0])
		head->content = NULL;
	else
		head->content = ft_strdup(str);
	free(temp);
}
