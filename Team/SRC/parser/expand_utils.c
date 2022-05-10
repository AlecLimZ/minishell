/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:22:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/10 10:45:46 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

/* check if env name is valid
** i. start with alpha or '_'
** ii. only consist of alpha, digit or '_'
*/

int	get_env_pos(char *str, int pos)
{
	int	i;
	int	quote;

	i = pos - 1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) \
			|| str[i + 1] == '_' || str[i + 1] == '?'))
			return (i);
		else if (str[i] == '\'')
			quote = in_quote(str, i);
		if (quote > i)
			i = quote;
	}
	return (-1);
}
