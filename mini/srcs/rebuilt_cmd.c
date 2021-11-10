/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuilt_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:04:49 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/10 16:09:01 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void    echoo(char **cmd)
{
	if (!ft_strncmp("-n",cmd[1],2))
		printf("%s",cmd[2]);
	else
		printf("%s\n",cmd[1]);  
}*/


/*void    check_cmd(char *inpt, char **cmd, char **envm)
{
	pid_t pid;
	if (*cmd == NULL)
		return ;
    /*else if (!ft_strncmp("echo",cmd[0],4))
        echoo(cmd);
	else if (!ft_strncmp("exit",cmd[0],4))
        exit(0);
	else if (!ft_strncmp("cd",cmd[0],4))
        cd(cmd);
	/*if (!ft_strncmp("pwd",cmd[0],4))
        exit(0);
	else if (!ft_strncmp("export",cmd[0],4))
        exit(0);
	else if (!ft_strncmp("unset",cmd[0],4))
        exit(0);
	/*if (!ft_strncmp("env",cmd[0],4))
        exit(0);
	else 
    {
		pid = fork();
		if (pid == 0)
			cmd_call(inpt,envm);
		waitpid(pid, NULL, 0);
    }
}*/