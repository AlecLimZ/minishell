/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:42:59 by yang              #+#    #+#             */
/*   Updated: 2022/05/12 18:14:36 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

/* check pipe: check if user input valid syntax for '|'
** Invalid syntax:
** i. '|' located at args[0] or args[last]
** ii. 2 consecutive '|' with no commands
**
** Notes: 
** i. it can be no space in between pipe, echo||echo is valid
** ii. becareful on quotation
*/

int	check_pipe(char *str)
{
	char	**ptr;
	int		i;
	int		j;
	int		len;

	len = count(str, ' ');
	ptr = ft_split_str(str, ' ');
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < (int)ft_strlen(ptr[i]))
		{
			if (ptr[i][j] == '|')
			{
				if ((j < (int)ft_strlen(ptr[i]) - 1 && ptr[i][j + 1] == '|')
					|| (i < len - 1 && ptr[i + 1][0] == '|') || (!i && !j)
					|| (i == len - 1 && j == (int)ft_strlen(ptr[len - 1]) - 1))
					return (free_double_ptr(ptr, true));
			}
			else if (is_quote(ptr[i][j]))
				j = in_quote(ptr[i], j);
		}
	}
	return (free_double_ptr(ptr, false));
}
