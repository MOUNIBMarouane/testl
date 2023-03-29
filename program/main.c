/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamounib <mamounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:05:02 by mamounib          #+#    #+#             */
/*   Updated: 2023/03/29 11:25:58 by mamounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_execmd(char *arg, int infile, int outfile, char **env)
{
	struct s_cmd	cmd;

	cmd.fulcmd = ft_split(arg, ' ');
	cmd.path = ft_getpath(cmd.fulcmd[0], env);
	if (!cmd.path)
	{
		write(2, "command not found", 17);
		exit(1);
	}
	if (dup2(infile, 0) == -1)
		perror("dup2");
	dup2(outfile, 1);
	if (dup2(outfile, 1) == -1)
		perror("dup2");
	ft_closefd(outfile, infile, -1, -1);
	if (execve(cmd.path, cmd.fulcmd, NULL) == -1)
		perror("execve");
	exit(1);
}

void	ft_checkarg(int arg)
{
	if (arg != 5)
	{
		write(2, "you must take 4 arguments\n", 26);
		exit(1);
	}
}

void checker()
{
	system("leaks pipex");
}
int	main(int argc, char **argv, char **environ)
{
	int				fd[2];
	int				pipfd[2];
	pid_t			pid[2];

	atexit(checker);
	ft_checkarg(argc);
	fd[0] = ft_openfd(argv[1], 1);
	fd[1] = ft_openfd(argv[4], 2);
	if (pipe(pipfd) == -1)
		exit(1);
	pid[0] = fork();
	if (pid[0] == -1)
		exit (1);
	if (pid[0] == 0)
		ft_execmd(argv[2], fd[0], pipfd[1], environ);
	close(pipfd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		exit(1);
	if (pid[1] == 0)
		ft_execmd(argv[3], pipfd[0], fd[1], environ);
	ft_closefd(pipfd[0], fd[0], fd[1], -1);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
