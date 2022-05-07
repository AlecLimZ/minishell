/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:31:23 by yang              #+#    #+#             */
/*   Updated: 2022/05/07 22:32:12 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_prompt *prompt)
{
	int		i;
	t_list	*token;

	i = -1;
	while (++i < prompt->total_cmds)
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
		{
			return (1);
		}
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

static int	set_token_after_redirect(t_cmd *cmd, char **token, int redirect)
{
	int		i;
	t_list	*new;
	t_list	*head;

	i = 0;
	if (redirect == -1)
		return (free_double_ptr(token, true));
	head = cmd->token;
	while (head && head->type <= 2)
	{
		head = head->next;
		i++;
	}
	while (token[redirect])
	{
		new = ft_lstnew(token[redirect]);
		set_token_type(new, i);
		ft_lstadd_pos(&cmd->token, new, i + 1);
		redirect++;
		i++;
	}
	return (free_double_ptr(token, false));
}

static int	tokenize(t_cmd *cmd, char *str)
{
	char	**token;
	t_list	*new;
	int		i;
	int		redirect;

	token = ft_split_str(str, ' ');
	free(str);
	str = NULL;
	i = -1;
	while (token[++i])
	{
		if (is_operator_in_str(token[i]))
			break ;
		new = ft_lstnew(token[i]);
		set_token_type(new, i);
		ft_lstadd_back(&cmd->token, new);
	}
	redirect = set_token_redirection(cmd, token, i);
	if (redirect == -1 || set_token_after_redirect(cmd, token, redirect) == -1)
	{
		free_double_ptr(token, false);
		return (-1);
	}
	return (0);
}

int	parser(t_prompt *prompt, char *str)
{
	char	**split_cmd;
	int		i;

	prompt->total_cmds = count(str, '|');
	if (prompt->total_cmds == -1
		|| (ft_strchr(str, '|') && check_pipe(str) == -1))
		return (-1);
	prompt->cmds = malloc(sizeof(t_cmd) * prompt->total_cmds);
	split_cmd = ft_split_str(str, '|');
	i = -1;
	while (split_cmd[++i])
	{
		ft_memset(&prompt->cmds[i], 0, sizeof(t_cmd));
		str = ft_strtrim(split_cmd[i], " ");
		if (tokenize(&prompt->cmds[i], str) == -1)
		{
			free_double_ptr(split_cmd, false);
			return (clean_up(prompt, i, 2));
		}
	}
	free_double_ptr(split_cmd, false);
	expand_n_remove_quote(prompt);
	// if (expand_token(prompt))
	// 	return (-1);
	print_cmds(prompt);
	return (0);
}
