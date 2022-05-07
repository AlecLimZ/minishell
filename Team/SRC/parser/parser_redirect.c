/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:59:12 by yang              #+#    #+#             */
/*   Updated: 2022/05/07 21:07:23 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
get_operator_file check if input command is correct
Invalid parsing for file will return (-1)
i. No file after operator
ii. operator len more than 2 
iii. 2 consecutive operator
iv. input operator like >< or <>
*/

static int	get_operator_pos(char **token, int pos)
{
	int		i;
	int		len_redirect;
	char	redirect;
	char	*str;

	i = -1;
	str = token[pos];
	while (str[++i] && !is_operator(str[i]))
	{
		if (is_quote(str[i]))
			i = in_quote(str, i);
	}
	redirect = str[i];
	len_redirect = 0;
	while (is_operator(str[i + len_redirect]))
		len_redirect++;
	if ((i == (int)ft_strlen(str) - len_redirect && token[pos + 1] == NULL)
		|| len_redirect > 2 || (len_redirect == 2 && str[i + 1] != redirect)
		|| (token[pos + 1] != NULL && is_operator(token[pos + 1][0])))
		return (-1);
	return (i);
}

static int	get_file_pos(char *str)
{
	int	i;

	i = 0;
	if (!is_operator(str[0]))
	{
		while (!is_operator(str[i]))
			i++;
	}
	while (is_operator(str[i]) && !is_space(str[i]))
		++i;
	return (i);
}

static int	get_redirection_type(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (GREATGREAT);
	else if (!ft_strncmp(str, "<<", 2))
		return (LESSLESS);
	else if (!ft_strncmp(str, ">", 1))
		return (GREAT);
	else if (!ft_strncmp(str, "<", 1))
		return (LESS);
	return (-1);
}

int	set_token_redirection(t_cmd *cmd, char **token, int i)
{
	char	dest[MAXCOM];
	int		j;
	t_list	*new;

	while (token[i] && is_operator_in_str(token[i]))
	{
		j = get_operator_pos(token, i);
		if (j == -1)
			return (-1);
		token_bef_operator(cmd, token, j, i);
		ft_memset(dest, 0, MAXCOM);
		if (ft_strlen(token[i] + j) > 2)
			ft_strlcpy(dest, token[i] + get_file_pos(token[i]), \
			ft_strlen(token[i]) - get_file_pos(token[i]) + 1);
		else
			ft_strlcpy(dest, token[i + 1], ft_strlen(token[i + 1]) + 1);
		new = ft_lstnew(dest);
		new->type = get_redirection_type(token[i] + j);
		ft_lstadd_back(&cmd->token, new);
		if ((ft_strlen(token[i] + j) <= 2 && is_operator(token[i][j]))
			|| (ft_strlen(token[i] + j) == 2 && is_operator(token[i][j + 1])))
			i++;
		i++;
	}
	return (i);
}
