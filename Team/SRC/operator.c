/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:49:45 by yang              #+#    #+#             */
/*   Updated: 2022/03/31 15:36:59 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

/*char	*ft_strjoin_space(char *str, int pos)
{
	char	*ptr;
	char	*prefix;
	char	*postfix;
	int		i;
	int		j;

	prefix = NULL;
	postfix = NULL;
	printf("strjoin: %s\n", str);
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 2));
	prefix = ft_strndup(str, pos + 1);
	//printf("postfix: %s\t len: %lu\n", str + pos + 1, ft_strlen(str) - pos - 1);
	postfix = ft_strndup(str + pos + 1, (int)ft_strlen(str) - pos - 1);
	printf("postfix: %s\t len: %lu\n", str + pos + 1, ft_strlen(str) - pos - 1);
	ft_memset(ptr, 0, ft_strlen(str) + 1);
	i = -1;
	j = -1;
	printf("pos: %d\n", pos);
	while (prefix[++i])
	{
		ptr[i] = prefix[i];
	}
	ptr[++i] = ' ';
	while (postfix[++j])
	{
		printf("i: %d\t len: %lu\t pos: %d\n", i, ft_strlen(str) + 1, j);
		ptr[i + j] = postfix[j];
	}
	free(prefix);
	free(postfix);
	//ptr[++i] = '\0';
	return (ptr);
}*/

/*int	before_after_operator(t_cmd *cmd, int i)
{
	char *str;
	//char *tmp;

	str = cmd->full_cmd;
	if (!is_space(str[i - 1]))
		str = ft_strjoin_space(str, i - 1);
	if (!is_space(str[i + 1]) && !is_operator(str[i + 1]))
		str = ft_strjoin_space(str, i + 1);
	if (is_operator(str[i + 1]) && !is_space(str[i + 2]))
		str = ft_strjoin_space(str, i + 2);
	cmd->full_cmd = str;
	printf("DEBUG: after add space: %s\n", cmd->full_cmd);
	return (i);
}*/

/* add space if before or after operator got no space */
// void	operator_add_space(t_prompt *prompt)
// {
// 	int	i;
// 	int	j;
// 	//t_cmd cmd;

// 	i = -1;
// 	while (++i < prompt->total_cmds)
// 	{
// 		//cmd = prompt->cmd[i];
// 		j = 0;
// 		while (prompt->cmd[i].full_cmd[j])
// 		{
// 			if (is_operator(prompt->cmd[i].full_cmd[j]))
// 				j = before_after_operator(&prompt->cmd[i], j);
// 			j++;
// 		}
// 	}
// }