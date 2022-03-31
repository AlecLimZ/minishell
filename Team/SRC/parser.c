/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:31:23 by yang              #+#    #+#             */
/*   Updated: 2022/03/29 18:23:58 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

int parser(t_prompt *prompt, char *str)
{
	int	i;
	//int	total;

	printf("DEBUG: total cmds: %d\n", total_cmds(str));
	prompt->total_cmds = total_cmds(str);
	if (prompt->total_cmds == -1)
	{
		printf("Error occurred\n");
		return (-1);
	}
	prompt->cmd = malloc(sizeof(t_cmd) * total_cmds(str));
	split_args_pipe(prompt, str);
	operator_add_space(prompt);

	i = -1;
	while (++i < prompt->total_cmds)
	{
		//prompt->cmd[i].full_cmd = str1;
		printf("DEBUG: %s\n", prompt->cmd[i].full_cmd);
	}
	
	/*i = -1;
	while (++i < prompt->total_cmds)
	{
		total = total_token(prompt->cmd[i].full_cmd);
		printf("total token: %d\n", total);
		prompt->cmd[i].token = malloc(sizeof(char *) * (total + 1));
		split_token(&prompt->cmd[i], prompt->cmd[i].full_cmd);
		prompt->cmd[i].token[total] = 0;
	}

	i = 0;
	int j = 0;
	while (i < prompt->total_cmds)
	{
		printf("i: %d\t total_cmds: %d\n", i, prompt->total_cmds);
		j = 0;
		while (j < total_token(prompt->cmd[i].full_cmd))
		{
			printf("DEBUG: after split: %s\n", prompt->cmd[i].token[j]);
			j++;
		}
		i++;
	}*/
	printf("end");
	return (0);
}
