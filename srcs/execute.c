/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:54:12 by min-kang          #+#    #+#             */
/*   Updated: 2022/01/16 15:54:14 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    redir_input(t_cmd **cmd, char *limiter)
{
    char	*r_data;
	char	*input;
	int		tmp;

	input = NULL;
    limiter = ft_strjoin(limiter, "\n", 1);
	while (1)
	{
		input = readline("");
		if (!ft_strcmp(input, limiter))
			break ;
		r_data = ft_strjoin(r_data, input, 1);
		free(input);
	}
	tmp = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(tmp, r_data, ft_strlen(r_data));
    (*cmd)->in = tmp;
	free(r_data);
}

void	pipe_define(t_cmd *cmd, int fd_in, int *fd)
{
    if (cmd->in)
		dup2(cmd->in, 0);
	else
		dup2(fd_in, 0);
	if (cmd->next)
		dup2(fd[1], 1);
	else
		dup2(cmd->out, 1);
	close(fd[0]);
}

void    execute_loop(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;

	fd_in = 0;
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			pipe_define(cmd, fd_in, fd);
			execve(cmd->cmd_path, cmd->args, cmd->envp);
			exit(0);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			fd_in = fd[0];
            cmd = cmd->next;
		}
	}
}

void    execute(t_cmd *cmd)
{
    if (!cmd->cmd_path)
    {
        ft_putstr_fd("Command name error\n", 2);
        return ;
    }
    if (!cmd->limiter)
        redir_input(&cmd, cmd->limiter);
	execute_loop(cmd);
}
