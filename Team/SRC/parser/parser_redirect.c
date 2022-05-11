/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:59:12 by yang              #+#    #+#             */
/*   Updated: 2022/05/11 15:03:58 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

static void	token_bef_operator(t_cmd *cmd, char **token, int pos, int i)
{
	char	dest[MAXCOM];
	t_list	*new;

	if (pos != 0)
	{
		ft_memset(dest, 0, MAXCOM);
		ft_strlcpy(dest, token[i], pos + 1);
		new = ft_lstnew(dest);
		set_token_type(new, i);
		ft_lstadd_back(&cmd->token, new);
	}
}

static int	token_operator(t_cmd *cmd, char *token, int *file_type, int j)
{
	char	dest[MAXCOM];
	t_list	*new;
	int		file_len;

	file_len = get_file_len(token, j);
	ft_memset(dest, 0, MAXCOM);
	ft_strlcpy(dest, token + j, file_len + 1);
	new = ft_lstnew(dest);
	new->type = *file_type;
	ft_lstadd_back(&cmd->token, new);
	*file_type = 0;
	return (file_len - 1);
}

/*
get_operator_file check if input command is correct
Invalid parsing for file will return (-1)
i. No file after operator
ii. operator len more than 2 
iii. 2 consecutive operator
iv. input operator like >< or <>
*/

static int	get_operator_pos(char **token, int pos, int j, int *operator_len)
{
	int		len_redirect;
	char	redirect;
	char	*str;

	str = token[pos];
	while (str[j] && !is_operator(str[j]))
	{
		if (is_quote(str[j]))
			j = in_quote(str, j);
		j++;
	}
	redirect = token[pos][j];
	len_redirect = 0;
	while (is_operator(str[j + len_redirect]))
		len_redirect++;
	if ((j == (int)ft_strlen(str) - len_redirect && token[pos + 1] == NULL)
		|| len_redirect > 2 || (len_redirect == 2 && str[j + 1] != redirect)
		|| (token[pos + 1] != NULL && is_operator(token[pos + 1][0])))
		return (-1);
	*operator_len = len_redirect;
	return (j);
}

static int	set_redirect(t_cmd *cmd, char **token, int i, int *file_type)
{
	int			j;
	int			pos;
	int			operator_len;
	char		dst[MAXCOM];

	j = -1;
	while (++j < (int)ft_strlen(token[i]))
	{
		if (*file_type == 0)
		{
			ft_memset(dst, 0, MAXCOM);
			pos = get_operator_pos(token, i, j, &operator_len);
			if (pos == -1)
				return (-1);
			if (pos > j)
				token_bef_operator(cmd, token, pos, i);
			j = pos;
			*file_type = get_redirection_type(&token[i][j]);
			j += operator_len - 1;
		}
		else
			j += token_operator(cmd, token[i], file_type, j);
	}
	return (0);
}

int	set_token_redirection(t_cmd *cmd, char **token, int i)
{
	static int	file_type;

	while (token[i])
	{
		if (set_redirect(cmd, token, i, &file_type) == -1)
			return (-1);
		if (file_type == 0 && ++i)
			break ;
		i++;
	}
	return (i);
}
