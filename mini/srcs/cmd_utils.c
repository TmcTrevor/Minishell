/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:29:35 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/10 11:37:14 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char *cmd, char *to_find, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], to_find , 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	error(void)
{
	write(1, "command not found\n", 19);
	exit(0);
}

void	cmd_call(t_command *cmd, char **envm)
{
	char	*file_path;

	//cmd = ft_split(argv, ' ');
	file_path = find_path(cmd->fcmd,"PATH", envm);
	if (execve(file_path, cmd->argument, envm) == -1)
		return (error());
}
