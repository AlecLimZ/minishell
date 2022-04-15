/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:21:45 by yang              #+#    #+#             */
/*   Updated: 2022/04/15 10:59:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[++i])
	{
		if (!is_env(str[i]))
			return (0);
	}
	return (1);
}

int get_env_pos(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			return (i);
		else if (str[i] == '\'')
			quote = in_quote(str, i);
		if (quote > i)
			i = quote;
	}
	return (-1);
}

char	*get_prefix(char *str, int i)
{
	if (i > 0)
	{
		return(ft_strndup(str, i));
	}
	return (NULL);
}

char	*get_postfix(char *str, int i)
{
	int		postfix_pos;

	postfix_pos = 0;
	while (str[++i])
	{
		if (!is_env(str[i]))
		{
			postfix_pos = i;
			break;
		}
	}
	if (postfix_pos != 0)
		return (ft_strndup(str + i, ft_strlen(str) - i));
	return (NULL);
}

char	*expand_str(char *prefix, char *postfix, char *path)
{
	char	*temp;
	char	*expand;

	temp = NULL;
	expand = NULL;
	if (!path)
	{
		if (!prefix && !postfix)
			return (NULL);
		else if (!prefix)
			return (ft_strjoin("", postfix));	
		else if (!postfix)
			return (ft_strjoin(prefix, ""));
		else
			return (ft_strjoin(prefix, postfix));	
	}
	if (!prefix)
		temp = path;
	else
		temp = ft_strjoin(prefix, path);
	if (!postfix)
		expand = temp;
	else
		expand = ft_strjoin(temp, postfix);
	return (expand);
}

char	*var_expand(char *str, int pos)
{
	char	*path;
	char	*prefix;
	char	*postfix;
	char	*expand;
	char	*temp;
	int		i;

	i = pos;
	prefix = get_prefix(str, pos);
	postfix = get_postfix(str, pos);
	while (str[i] && is_env(str[i + 1]))
		i++;
	temp = ft_strndup(str + pos + 1, i - pos);
	//if (temp[0] == '?')
	if (!is_name(temp))
		return (NULL);
	path = getenv(temp);
	free(temp);
	temp = NULL;
	expand = expand_str(prefix, postfix, path);
	if (prefix)
		free(prefix);
	if (postfix)
		free(postfix);
	return (expand);
}

int	add_var_to_list(t_cmd *cmd, t_list *head, char *str)
{
	char	**token;
	int		i;
	t_list	*new;

	token = NULL;
	i = -1;
	if (head->type == 1 && str != NULL)
	{
		token = ft_split_str(str, ' ');
		while (token[++i])
		{
			new = ft_lstnew(token[i]);
			set_token_type(new, i);
			ft_lstadd_pos(&cmd->token, new, i + 1);
		}
		free_malloc(token);
	}
	else
		head->content = str;
	return (i + 1);
}

void	expand_token(t_prompt *prompt)
{
	int		i;
	t_list	*head;
	int		pos;
	char	*str;
	int		del;

	i = -1;
	while (++i < prompt->total_cmds)
	{
		del = 0;
		head = prompt->cmds[i].token;
		while (head && head->type <= 2)
		{
			pos = get_env_pos(head->content);
			if (pos != -1)
			{
				str = var_expand(head->content, pos);
				del = add_var_to_list(&prompt->cmds[i], head, str);
				
			}
			remove_quotes(head);
			head = head->next;
		}
		ft_lstdel_pos(&prompt->cmds[i].token, del);
	}
}
