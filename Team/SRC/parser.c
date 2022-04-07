/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:31:23 by yang              #+#    #+#             */
/*   Updated: 2022/04/07 15:20:23 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	print_cmds(t_prompt *prompt)
{
	int i = -1;
	t_list *token;

	while(++i < prompt->total_cmds)
	{
		token = prompt->cmds[i].token;
		printf(BRED"Command %d\n"WHT, i);
		while (token != NULL)
		{
			printf("content: %s\t type: %d\n", token->content, token->type);
			token = token->next;
		}
	}
}

int	is_operator_in_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_operator(str[i]))
			return (1);
		else if (is_quote(str[i]))
			i = in_quote(str, i);
	}
	return (0);
}

void	set_token_type(t_list *new, int i)
{
	if (i == 0)
		new->type = COMMAND;
	else
		new->type = ARGUMENT;
}

int	tokenize(t_cmd *cmd, char *str)
{
	char	**token;
	t_list	*new;
	int		i;
	int		j;
	int		stop;

	token = ft_split_str(str, ' ');
	i = -1;
	stop = 0;
	while (stop == 0 && token[++i])
	{
		j = -1;
		if (is_operator_in_str(token[i]))
			break;
		//if (stop == 1)
			//break;
		new = ft_lstnew(token[i]);
		set_token_type(new, i);
		ft_lstadd_back(&cmd->token, new);
	}
	if (set_token_redirection(cmd, token, i) == -1)
		return (-1);
	return (0);
}

int	parser(t_prompt *prompt, char *str)
{
	char	**split_cmd;
	int		i;

	prompt->total_cmds = count(str, '|');
	if (prompt->total_cmds == -1 || check_pipe(str) == -1)
		return (-1);
	prompt->cmds = malloc(sizeof(t_cmd) * prompt->total_cmds);
	split_cmd = ft_split_str(str, '|');
	i = -1;
	while (split_cmd[++i])
	{
		ft_memset(&prompt->cmds[i], 0, sizeof(t_cmd));
		tokenize(&prompt->cmds[i], ft_strtrim(split_cmd[i], " "));
	}
	free_malloc(split_cmd);
	expand_token(prompt);
	print_cmds(prompt);
	return (0);
}
