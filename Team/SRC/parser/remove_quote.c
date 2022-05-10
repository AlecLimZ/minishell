/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:27:45 by yang              #+#    #+#             */
/*   Updated: 2022/05/10 10:46:09 by yang             ###   ########.fr       */
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
		if (i <= 0)
			break ;
	}
}
