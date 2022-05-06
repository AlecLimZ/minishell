/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:21:45 by yang              #+#    #+#             */
/*   Updated: 2022/05/06 19:54:07 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_var_to_list(t_cmd *cmd, t_list *head, char *str)
{
	char	**token;
	char	*temp;
	int		i;
	t_list	*new;

	i = -1;
	if (head->type == 1 && str != NULL)
	{
		token = ft_split_str(str, ' ');
		free(str);
		while (token[++i])
		{
			new = ft_lstnew(token[i]);
			set_token_type(new, i);
			ft_lstadd_pos(&cmd->token, new, i + 1);
		}
		free_double_ptr(token, false);
	}
	else
	{
		temp = head->content;
		head->content = str;
		free(temp);
	}
	return (i + 1);
}

static int	expand_loop(t_prompt *prompt, int i, t_list *head, int *del)
{
	int		pos;
	char	*str;

	pos = get_env_pos(head->content, 0);
	while (pos != -1 && head->content[pos + 1])
	{
		str = var_expand(head->content, &pos, prompt);
		*del = add_var_to_list(&prompt->cmds[i], head, str);
		pos = get_env_pos(head->content, pos + 1);
	}
	return (0);
}

int	expand_token(t_prompt *prompt)
{
	int		i;
	t_list	*head;
	int		err;
	int		del;

	i = -1;
	while (++i < prompt->total_cmds)
	{
		del = 0;
		head = prompt->cmds[i].token;
		while (head && head->type <= 2)
		{
			err = expand_loop(prompt, i, head, &del);
			if (err)
				return (err);
			remove_quotes(head);
			head = head->next;
		}
		ft_lstdel_pos(&prompt->cmds[i].token, del);
	}
	return (0);
}
