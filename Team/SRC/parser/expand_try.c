/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_try.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:31:16 by yang              #+#    #+#             */
/*   Updated: 2022/05/08 00:35:05 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var_to_list(t_cmd *cmd, t_list *head, char *str)
{
	char	**token;
	char	*temp;
	int		i;
	t_list	*new;

	i = -1;
	if (head->type == 1 && str[0])
	{
		token = ft_split_str(str, ' ');
		while (token[++i])
		{
			new = ft_lstnew(token[i]);
			set_token_type(new, i);
			ft_lstadd_pos(&cmd->token, new, i + 1);
		}
		ft_lstdel_pos(&cmd->token, i + 1);
		free_double_ptr(token, false);
	}
	else
	{
		temp = head->content;
		head->content = ft_strdup(str);
		free(temp);
	}
}

int	var_expand(char *str, char **expand, t_prompt *prompt)
{
	char	temp[500];
	int		i;

	i = 0;
	if (str[i + 1] == '?')
		*expand = ft_itoa(g_ret);
	else
	{
		while (str[i] && is_env(str[i + 1]))
			i++;
		ft_strlcpy(temp, str + 1, i + 1);
		*expand = ft_getenv(temp, prompt);
	}
	return (i);
}

void	expand_token(char *src, t_list *head, t_cmd *cmd, t_prompt *prompt)
{
	char	dst[500];
	char	*expand;
	int		i;
	int		pos;

	ft_memset(dst, 0, sizeof(char));
	i = -1;
	while (src[++i])
	{
		pos = get_env_pos(src, i);
		if (pos == -1)
		{
			if (i < (int)ft_strlen(src) - 1)
				ft_strlcat(dst, src + i, \
					ft_strlen(dst) + ft_strlen(src) - i + 1);
			break ;
		}
		else
		{
			if (pos > i)
			{
				ft_strlcat(dst, src + i , ft_strlen(dst) + pos - i + 1);
				i = pos;
			}
			i += var_expand(src + pos, &expand, prompt);
			if (expand)
				ft_strlcat(dst, expand, ft_strlen(dst) + ft_strlen(expand) + 1);
		}
	}
	add_var_to_list(cmd, head, dst);
}

int	expand_n_remove_quote(t_prompt *prompt)
{
	int		i;
	char	src[500];
	t_list	*head;

	i = -1;
	while (++i < prompt->total_cmds)
	{
		head = prompt->cmds[i].token;
		while (head && head->type <= 2)
		{
			if (get_env_pos(head->content, 0) != -1)
			{
				ft_strlcpy(src, head->content, ft_strlen(head->content) + 1);
				expand_token(src, head, &prompt->cmds[i], prompt);
				if (head->type == 1)
					head = prompt->cmds[i].token;
			}
			remove_quotes(head);
			head = head->next;
		}
	}
	return (0);
}
