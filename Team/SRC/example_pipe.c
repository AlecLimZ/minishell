// # include <stdio.h>
// # include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <sys/wait.h>
// # include <sys/types.h>
// # include <signal.h>
// # include <fcntl.h>


// //cmd 0 (write to pipe1[1]) close pipe1[1] close pipe1[0]
// //cmd 1 (receive from pipe1[0]) close (pipe1[0])
// //      (write to pipe2[1]) close pipe2[1] close pipe2[0]
// //cmd 2 (receive from pipe2[0]) close (pipe2[0])

// void	exec(int i, char **argv, char **envp)
// {
// 	int fd[2];
// 	static int keep_fd;

// 	if (i != 2)
// 		pipe(fd);
	
// 	int process = fork();
// 	//child process
// 	if (process == 0)
// 	{
// 		if (i == 0)
// 		{
// 			dup2(fd[1], 1);
// 			close(fd[1]);
// 			close(fd[0]);
// 		}
// 		else if (i == 1)
// 		{
// 			dup2(keep_fd, 0);
// 			close(keep_fd);
// 			dup2(fd[1], 1);
// 			close(fd[1]);
// 			close(fd[0]);
// 		}
// 		else if (i == 2)
// 		{
// 			dup2(keep_fd, 0);
// 			close(keep_fd);
// 		}

// 		char *cmd[] = {argv[i + 1], NULL};
// 		execve(argv[i + 1], cmd, envp);
// 	}
// 	else //parent process
// 	{
// 		if (i == 0)
// 		{
// 			close(fd[1]);
// 			keep_fd = fd[0];
// 		}
// 		else if (i == 1)
// 		{
// 			close (keep_fd);
// 			close (fd[1]);
// 			keep_fd = fd[0];
// 		}
// 		else if (i == 2)
// 		{
// 			close (keep_fd);
// 		}
// 	}
// }

// // 0 = first, 1 = second, 2 = third
// int main(int argc, char **argv, char **envp)
// {
// 	int i = 0;
// 	while (i < 3)
// 	{
// 		exec(i, argv, envp);
// 		i += 1;
// 	}
// }
