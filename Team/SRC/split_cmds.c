/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:25:35 by yang              #+#    #+#             */
/*   Updated: 2022/03/29 17:47:31 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int	total_cmds(char *str)
{
	int		total;
	int 	i;
	int		last;

	i = -1;
	total = 1;
	while (str[++i])
	{
		if (str[i] == '|')
			total++;
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
		if (i == -1)
			return (-1);
	}
	last = ft_strlen(str) - 1;
	while (is_space(str[last]))
		last--;
	if (str[last] == '|')
		return (-1);
	return (total);
}

/* separate user input into each cmd by '|' */
int	split_args_pipe(t_prompt *prompt, char *str)
{
	int		start_pos;
	int		i;
	int		j;

	start_pos = 0;
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			prompt->cmd[++j].full_cmd = ft_strndup(str + start_pos, i - start_pos);
			start_pos = i + 1;
		}
		else if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
	}
	prompt->cmd[++j].full_cmd = ft_strndup(str + start_pos, i - start_pos);
	return (0);
}

int	total_token(char *str)
{	
	int		total;
	int 	i;

	i = 0;
	total = 1;
	str = ft_strtrim(str, " ");
	while (i < (int)ft_strlen(str))
	{
		if (is_space(str[i]))
		{
			total++;
			while (is_space(str[i]))
				i++;
		}
		if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (total);
}

/* separate commands into each token by ' ' 
 * strndup copies the string before i */
int	split_token(t_cmd *cmd, char *str)
{
	int		start_pos;
	int		i;
	int		j;

	start_pos = 0;
	i = -1;
	j = -1;
	str = ft_strtrim(str, " ");
	while (++i < (int)ft_strlen(str))
	{
		if (is_space(str[i]))
		{
			cmd->token[++j] = ft_strndup(str + start_pos, i - start_pos);
			while (str[i] != '\0' && is_space(str[i]))
				i++;
			start_pos = i;
		}
		if (str[i] == '"' || str[i] == '\'')
			i = in_quote(str, i);
		if (i == -1)
			return (-1);
	}
	cmd->token[++j] = ft_strndup(str + start_pos, i - start_pos);
	return (0);
}
