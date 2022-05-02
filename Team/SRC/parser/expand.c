/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:21:45 by yang              #+#    #+#             */
/*   Updated: 2022/05/02 16:14:15 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_path(char *prefix, char *postfix, char *path)
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
		expand = ft_strdup(temp);
	else
		expand = ft_strjoin(temp, postfix);
	return (expand);
}

static char	*expand_str(char *str, int pos, char *path)
{
	char	*expand;
	char	*prefix;
	char	*postfix;

	prefix = get_prefix(str, pos);
	postfix = get_postfix(str, pos);
	expand = expand_path(prefix, postfix, path);
	free(prefix);
	prefix = NULL;
	free(postfix);
	postfix = NULL;
	return (expand);
}

static char	*var_expand(char *str, int pos, t_prompt *prompt)
{
	char	*path;
	char	*expand;
	char	*temp;
	int		i;

	i = pos;
	while (str[i] && is_env(str[i + 1]))
		i++;
	temp = ft_strndup(str + pos + 1, i - pos);
	//if (temp[0] == '?')
	if (!is_name(temp))
		return (NULL);
	path = ft_getenv(temp, prompt); //have to create own ft_getnenv
	free(temp);
	temp = NULL;
	expand = expand_str(str, pos, path);
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
		free_double_ptr(token, false);
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
				str = var_expand(head->content, pos, prompt);
				del = add_var_to_list(&prompt->cmds[i], head, str);
			}
			remove_quotes(head);
			head = head->next;
		}
		ft_lstdel_pos(&prompt->cmds[i].token, del);
	}
}
