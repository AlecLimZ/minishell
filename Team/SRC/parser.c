/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:31:23 by yang              #+#    #+#             */
/*   Updated: 2022/04/01 18:56:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void print_cmds(t_prompt *prompt)
{
	int i = -1;
	t_list *token;

	while(++i < prompt->total_cmds)
	{
		token = prompt->cmds[i].token;
		printf("Command %d\n", i);
		while (token != NULL)
		{
			printf("content: %s\t type: %d\n", token->content, token->type);
			token = token->next;
		}
	}
}

int	get_operator_pos(char *str)
{
	int	i;

	i = 0; 
	while (str[i] && !is_operator(str[i]))
		i++;
	return (i);
}

int	get_file_pos(char *str)
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

int	get_redirection_type(char *str)
{
	char	redirect;
	int		i;

	i = 0;
	redirect = str[i];
	printf("redirection: %s\n", str);
	if (ft_strlen(str) > 1 && is_operator(str[i + 1]))
	{
		if (str[i + 1] != redirect)
			return (-1);
		if (redirect == '>')
			return (GREATGREAT);
		return (LESSLESS);
	}
	else
	{
		if (redirect == '>')
			return (GREAT);
		return (LESS);
	}
}

int	set_token_redirection(t_cmd *cmd, char **token, int i)
{
	char	dest[MAXCOM];
	int		pos;
	t_list	*new;

	while (token[i])
	{
		pos = get_operator_pos(token[i]);
		if (pos != 0)
		{
			ft_memset(dest, 0, MAXCOM);
			ft_strlcpy(dest, token[i], pos + 1);
			new = ft_lstnew(dest);
			if (i == 0)
				new->type = COMMAND;
			else
				new->type = ARGUMENT;
			ft_lstadd_back(&cmd->token, new);
		}
		ft_memset(dest, 0, MAXCOM);
		if (ft_strlen(token[i] + pos) > 2)
		{
			ft_strlcpy(dest, token[i] + get_file_pos(token[i]), ft_strlen(token[i]) - get_file_pos(token[i]) + 1);
			//ft_strlcpy(dest, token[i] + pos + 1, ft_strlen(token[i]) - get_file_pos(token[i]) + 1);
		}
		else
			ft_strlcpy(dest, token[i + 1], ft_strlen(token[i + 1]) + 1);
		new = ft_lstnew(dest);
		new->type = get_redirection_type(token[i] + pos);
		if (new->type == -1)
			return (-1);
		ft_lstadd_back(&cmd->token, new);
		if ((ft_strlen(token[i] + pos) == 1 && is_operator(token[i][pos]))
			|| (ft_strlen(token[i] + pos) == 2 && is_operator(token[i][pos]) && is_operator(token[i][pos + 1])))
			i++;
		i++;
	}
	return (0);
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
		while (token[i][++j])
		{
			if (!is_quote(token[i][0]) && is_operator(token[i][j]))
				stop = 1;
		}
		if (stop == 1)
			break;
		new = ft_lstnew(token[i]);
		if (i == 0)
			new->type = COMMAND;
		else
			new->type = ARGUMENT;
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
	if (prompt->total_cmds == -1)
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
	print_cmds(prompt);
	return (0);
}


// int get_token(t_cmd *cmd, char *str)
// {
// 	char	**split_token;
// 	int		i;

// 	split_token = ft_split_str(str, ' ');
// 	i = -1;
// 	while (split_token[++i])
// 	{

// 	}
// }
// int parser(t_prompt *prompt, char *str)
// {
// 	int	i;
// 	//int	total;

// 	printf("DEBUG: total cmds: %d\n", total_cmds(str));
// 	prompt->total_cmds = total_cmds(str);
// 	if (prompt->total_cmds == -1)
// 	{
// 		printf("Error occurred\n");
// 		return (-1);
// 	}
// 	prompt->cmd = malloc(sizeof(t_cmd) * total_cmds(str));
// 	split_args_pipe(prompt, str);
// 	operator_add_space(prompt);

// 	i = -1;
// 	while (++i < prompt->total_cmds)
// 	{
// 		//prompt->cmd[i].full_cmd = str1;
// 		printf("DEBUG: %s\n", prompt->cmd[i].full_cmd);
// 	}
	
// 	/*i = -1;
// 	while (++i < prompt->total_cmds)
// 	{
// 		total = total_token(prompt->cmd[i].full_cmd);
// 		printf("total token: %d\n", total);
// 		prompt->cmd[i].token = malloc(sizeof(char *) * (total + 1));
// 		split_token(&prompt->cmd[i], prompt->cmd[i].full_cmd);
// 		prompt->cmd[i].token[total] = 0;
// 	}

// 	i = 0;
// 	int j = 0;
// 	while (i < prompt->total_cmds)
// 	{
// 		printf("i: %d\t total_cmds: %d\n", i, prompt->total_cmds);
// 		j = 0;
// 		while (j < total_token(prompt->cmd[i].full_cmd))
// 		{
// 			printf("DEBUG: after split: %s\n", prompt->cmd[i].token[j]);
// 			j++;
// 		}
// 		i++;
// 	}*/
// 	printf("end");
// 	return (0);
// }
