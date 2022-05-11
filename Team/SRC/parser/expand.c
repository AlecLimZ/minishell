/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:31:16 by yang              #+#    #+#             */
/*   Updated: 2022/05/11 15:00:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	add_var_to_list(t_cmd *cmd, t_list *head, char *str)
{
	char	**token;
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
		replace_expand_str(head, str);
}

int	var_expand(char *str, char **expand, t_prompt *prompt)
{
	char	temp[500];
	char	*num;
	int		i;
	char	ptr[500];

	i = 0;
	*expand = NULL;
	if (str[i + 1] && str[i + 1] == '?')
	{
		num = ft_itoa(g_ret);
		ft_strlcpy(ptr, num, ft_strlen(num) + 1);
		*expand = ptr;
		free(num);
		i += 1;
	}
	else if (str[i + 1] && str[i + 1] != '_' && !ft_isalpha(str[i + 1]))
		i += 1;
	else
	{
		while (str[i] && is_env(str[i + 1]))
			i++;
		ft_strlcpy(temp, str + 1, i + 1);
		*expand = ft_genvp(temp, prompt);
	}
	return (i);
}

int	expand_token_2(char *dst, char *src, int i)
{
	int	pos;

	pos = get_env_pos(src, i);
	if (pos == -1)
	{
		if (i < (int)ft_strlen(src))
			ft_strlcat(dst, src + i, \
					ft_strlen(dst) + ft_strlen(src) - i + 1);
	}
	return (pos);
}

void	expand_token(char *src, t_list *head, t_cmd *cmd, t_prompt *prompt)
{
	char	dst[500];
	char	*expand;
	int		i;
	int		pos;

	i = -1;
	ft_memset(dst, 0, 500);
	while (src[++i])
	{
		pos = expand_token_2(dst, src, i);
		if (pos == -1)
			break ;
		if (pos > i)
		{
			ft_strlcat(dst, src + i, ft_strlen(dst) + pos - i + 1);
			i = pos;
		}
		i += var_expand(src + pos, &expand, prompt);
		if (expand)
			ft_strlcat(dst, expand, ft_strlen(dst) + ft_strlen(expand) + 1);
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
			if (need_expansion(head->content) != -1)
			{
				ft_strlcpy(src, head->content, ft_strlen(head->content) + 1);
				expand_token(src, head, &prompt->cmds[i], prompt);
				if (head->type == 1)
					head = prompt->cmds[i].token;
			}
			if (!head)
				break ;
			remove_quotes(head);
			head = head->next;
		}
	}
	return (0);
}
