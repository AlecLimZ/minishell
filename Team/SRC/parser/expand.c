/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:21:45 by yang              #+#    #+#             */
/*   Updated: 2022/05/07 22:23:23 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int	add_var_to_list(t_cmd *cmd, t_list *head, char *str)
// {
// 	char	**token;
// 	char	*temp;
// 	int		i;
// 	t_list	*new;

// 	i = -1;
// 	if (head->type == 1 && str != NULL)
// 	{
// 		token = ft_split_str(str, ' ');
// 		free(str);
// 		while (token[++i])
// 		{
// 			new = ft_lstnew(token[i]);
// 			set_token_type(new, i);
// 			ft_lstadd_pos(&cmd->token, new, i + 1);
// 		}
// 		free_double_ptr(token, false);
// 	}
// 	else
// 	{
// 		temp = head->content;
// 		head->content = str;
// 		free(temp);
// 	}
// 	return (i + 1);
// }

// static int	expand_loop(t_prompt *prompt, int i, t_list *head)
// {
// 	int		pos;
// 	char	*str;
// 	bool	expanded;

// 	expanded = false;
// 	pos = get_env_pos(head->content, 0);
// 	printf("content: %s\t pos: %d\n", head->content, pos);
// 	while (pos != -1 && head->content[pos + 1])
// 	{
// 		expanded = true;
// 		str = var_expand(head->content, &pos, prompt);
// 		if (str)
// 			add_var_to_list(&prompt->cmds[i], head, str);
// 		pos = get_env_pos(head->content, pos + 1);
// 	}
// 	return (expanded);
// }

// int	expand_token(t_prompt *prompt)
// {
// 	int		i;
// 	t_list	*head;
// 	bool	expanded;
// 	int		pos;

// 	i = -1;
// 	while (++i < prompt->total_cmds)
// 	{
// 		pos = 0;
// 		head = prompt->cmds[i].token;
// 		while (head && head->type <= 2 && ++pos)
// 		{
// 			expanded = expand_loop(prompt, i, head);
// 			// if (expanded)
// 			// 	ft_lstdel_pos(&prompt->cmds[i].token, pos);
// 			print_cmds(prompt);
// 			remove_quotes(head);
// 			head = head->next;
// 			//printf("head: %s\n", head->content);
// 		}
// 	}
// 	return (0);
// }
