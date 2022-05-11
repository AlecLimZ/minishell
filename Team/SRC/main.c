/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/11 18:39:34 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

/* refresh the prompt if user hit Ctrl + C */
void	new_prompt(int sig)
{
	(void)sig;
	g_ret = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* init environment, add environment list into linked list */
int	init_env(t_prompt *prompt, char *envp[])
{
	int		i;
	t_list	*new;
	int		pos;

	i = -1;
	prompt->envp = NULL;
	while (envp[++i] != NULL)
	{
		new = ft_lstnew(envp[i]);
		ft_lstadd_back(&prompt->envp, new);
	}
	pos = ft_findenv("OLDPWD", prompt);
	if (ft_posenv(pos, prompt))
		return (0);
	return (0);
}

/* get input from user and add it into history list */
int	get_input(char *str)
{
	char	*buf;
	int		i;

	buf = readline(">>> ");
	i = 0;
	if (buf == NULL)
	{
		printf("exit\n");
		return (-1);
	}
	while (buf[i] && is_space(buf[i]))
		i++;
	if (buf[i])
	{
		add_history(buf);
		ft_strlcpy(str, buf, ft_strlen(buf) + 1);
	}
	if (!buf[i])
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

static int	minishell(t_prompt *prompt, char *input_str)
{
	int	input;

	while (true)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
		ft_memset(input_str, 0, MAXCOM);
	//	printf("g_ret: %d\n", g_ret);
		input = get_input(input_str);
		if (input == -1)
			break ;
		if (input)
		{
			if (parser(prompt, input_str) == -1)
			{
				g_ret = 2;
				ft_putendl_fd("minishell: syntax error", 2);
				continue ;
			}
			exec_args(prompt);
			clean_up(prompt, prompt->total_cmds - 1, 2);
		}
	}
	return (g_ret);
}

int	ft_runscript(char *argv, char **envp, t_prompt *prompt)
{
	// char	err[MAXCOM];

	if (!prompt)
		return (0);
	ft_memset(prompt, 0,sizeof(t_prompt));
	init_env(prompt, envp);
	if (argv)
	{
		//printf("argv: %s\n", argv);
		if (parser(prompt, argv) == -1)
		{
			// ft_strlcpy(err, "minishell: syntax error near unexpected token", )
			// ft_strlcat(err, )
			g_ret = 2;
			ft_putendl_fd("minishell: syntax error", 2);
			return (g_ret) ;
		}
		exec_args(prompt);
		clean_up(prompt, prompt->total_cmds - 1, 2);
	}
	return (g_ret);
}

// int	run_script(char *input, char **envp)
// {
// 	t_prompt	prompt;
// 	char		*part;

// 	ft_bzero(&prompt, sizeof(prompt));
// 	prompt.env = init_env(envp);
// 	change_dir(&prompt, ".");
// 	while (next_string(&part, &input, ';'))
// 	{
// 		prompt.full_cmds = part;
// 		if (get_cmds(&prompt.cmds, &prompt))
// 			prompt.e_status = execute_line(prompt.cmds, &prompt);
// 		cleanup_cmd(&prompt);
// 	}
// 	cleanup(&prompt);
// 	return (prompt.e_status);
// }

int	main(int argc, char *argv[], char *envp[])
{
	char			input_str[MAXCOM];
	t_prompt		*prompt = NULL;
	struct termios	termios_new;
	struct termios	termios_save;

	// if (argc == 3 && !ft_strcmp(argv[1], "-c"))
	// {
	// 	return (ft_runscript(argv[2], envp, prompt));
	// }
	prompt = malloc(sizeof(t_prompt));
	if (argc == 3 && !ft_strcmp(argv[1], "-c"))
	{
		return (ft_runscript(argv[2], envp, prompt));
	}
	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
	if (!prompt)
		return (EXIT_FAILURE);
	ft_memset(prompt, 0, sizeof(t_prompt));
	init_env(prompt, envp);
	if (minishell(prompt, input_str))
	{
		tcsetattr(0, 0, &termios_save);
		return (g_ret);
	}
	tcsetattr(0, 0, &termios_save);
	return (g_ret);
}
