#include "../includes/minishell.h"

void    execute(t_cmd cmd)
{
    char    *cmd_path;
    if (!cmd.cmd_path)
    {
        ft_putstr_fd("Command name error\n", 2);
        return ;
    }
	execve(cmd.cmd_path, cmd.args, cmd.envp);
}