/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:35:26 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/17 14:21:53 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char(void)
{
	char	buf[4];
	int		nbr;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buf, 4);
	nbr = *(int *)buf;
	if (nbr < 0)
		nbr *= (-1);
	return ('a' + nbr % 26);
}

char	*ft_create_file(void)
{
	char	*filename;
	int		i;

	i = -1;
	filename = malloc(sizeof(char) * 11);
	filename[10] = '\0';
	while (++i < 10)
		filename[i] = (char)ft_char();
	return (filename);
}

void	ft_oldpwd(t_prompt *prompt)
{
	char	*oldpwd;
	char	*tmp2;
	t_list	*envp;

	oldpwd = ft_getpwd();
	envp = prompt->envp;
	if (ft_findenv("OLDPWD", prompt) == -1)
		ft_newexport(prompt, "OLDPWD");
	while (envp != NULL)
	{
		if (!ft_strncmp(envp->content, "OLDPWD", 6))
		{
			tmp2 = ft_strjoin("OLDPWD=", oldpwd);
			free(envp->content);
			envp->content = tmp2;
		}
		envp = envp->next;
	}
}

char	*ft_geteof(t_cmd *cmd)
{
	t_list	*token;
	char	*eof;

	token = cmd->token;
	while (token != NULL)
	{
		if (token->type == 4)
			eof = token->content;
		token = token->next;
	}
	return (eof);
}
