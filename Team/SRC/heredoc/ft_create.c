/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:35:26 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/04 17:00:38 by leng-chu         ###   ########.fr       */
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
	int		pos;
	char	*tmp;

	oldpwd = ft_getpwd();
	pos = ft_findenv("OLDPWD", prompt);
	tmp = ft_strjoin("OLDPWD", "=");
	prompt->our_env[pos] = ft_strjoin(tmp, oldpwd);
	free(tmp);
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
