/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbifenzi <mbifenzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:18:00 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/24 02:13:35 by mbifenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	error1(void)
{
	printf("file error\n");
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT, 0777);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 3)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error1();
	return (file);
}

int	redirect_to(t_command *cmd, t_tools *tools)
{
	t_redirect	*red;
	int			fdin;
	int			fdout;

	(void)tools;
	fdin = -1;
	fdout = -1;
	red = cmd->redirect;
	while (red)
	{
		if (red->type == 3)
			fdin = open_file(red->file, red->type);
		if (red->type == 1 || red->type == 2)
			fdout = open_file(red->file, red->type);
		red = red->nextred;
	}
	if (fdin > -1)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout > -1)
	{
		dup2(fdout, 1);
		close(fdout);
	}
	return (0);
}
//close FDs at the end ?? 