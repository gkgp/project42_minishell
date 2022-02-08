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

int    execute_loop(t_node *node, char **envp)
{
	int		fd[2];
	int		res[2];
	pid_t	pid;
	int		fd_in;
	int		success;

	fd_in = 0;
	success = 0;
	while (node)
	{
		pipe(fd);
		pipe(res);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (node->right)
				dup2(fd[1], 1);
			close(fd[0]);
			success = cmd_execute(node->left, fd_in, envp);
			if (success == -1)
				write(fd[1], "", 1);
			write(res[1], &success, sizeof(success));
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			success = read(res[0], &success, sizeof(success));
			fd_in = fd[0];
	        node = node->right;
		}
	}
	return (success);
}

int	here_doc(char *limiter)
{
	char	*r;
	char	*txt;
	int		fd_tmp;

	while (1)
	{
		r = readline("");
		if (ft_strlen(limiter) == ft_strlen(r) - 1
			&& !ft_strncmp(limiter, r, ft_strlen(limiter)))
			break ;
		txt = ft_strjoin(txt, r, 1);
		free(r);
	}
	fd_tmp = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd_tmp, txt, ft_strlen(txt));
	free(txt);
	return (fd_tmp);
}

char	*pathname_creator(char *s, char **paths)
{
	char	*cmd;
	int		i;

	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], "/", 0);
		cmd = ft_strjoin(cmd, s, 1);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			free(cmd);
	}
	ft_putstr_fd("Error : wrong command name\n", 2);
	return (NULL);
}

char	**possible_path(char **envp)
{
	int		i;
	char	**result;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i++], "PATH=", 5))
		i++;
	result = ft_split(envp[i] + 5, ':');
	return (result);
}

char	*path_define(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**paths;

	printf("yoyo\n");
	/*if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset") 
	|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
	|| !ft_strcmp(cmd, "export"))
		return (ft_strjoin("../srcs/builtin/ft_", cmd, 0));*/
	paths = possible_path(envp);
	cmd_path = pathname_creator(cmd, paths);
	return (cmd_path);
}

int	cmd_execute(t_node *node, int fd_in, char **envp)
{
	int		i;
	int		input;
	int		output;
	char	*cmd_path;
	
	i = -1;
	dup2(fd_in, 0);
	input = 0;
	output = 0;
	printf("bubu\n");
	if (node->right)
	{
		while (node->right->redir_type[++i])
		{
			if (node->right->redir_type[i] == CHEVRON_I)
				input = open(node->right->redir_name[i], O_RDONLY);
			else if (node->right->redir_type[i] == CHEVRON_O)
				output = open(node->right->redir_name[i], O_CREAT | O_WRONLY | O_TRUNC);
			else if (node->right->redir_type[i] == DOUBLE_CHEVRON_I)
				input = here_doc(node->right->redir_name[i]);
			else
				output = open(node->right->redir_name[i], O_CREAT | O_WRONLY | O_APPEND);
			if (input == -1 || output == -1)
			{
				ft_putstr_fd("Error.", 2);
				return (0);
			}
		}
	}
	if (input)
		dup2(input, 0);
	if (output)
		dup2(output, 1);
	cmd_path = path_define(node->root->left->args[0], envp);
	printf("lolo\n");
	if (!cmd_path)
		return (-1);
	execve(cmd_path, node->left->args, envp);
	return (-1);
}

int	execute(t_node *node, char **envp)
{
	int	success;

	printf("bobo %d\n", node->root->node_type);
	if (node->root->node_type == 3)
		success = execute_loop(node, envp);
	else
		success = cmd_execute(node, 0, envp);
	return (success);
}