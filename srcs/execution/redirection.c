/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:18:00 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/27 21:38:09 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	error1(char *argv, int i)
{
	if (i == 1 || i == 2)
	{
		write(2, "mokhames : ", 12);
		write(2, argv, ft_strlen(argv));
		write(2, ": is a directory\n", 18);
			__get_var(SETEXIT, -1);
	}
	if (i == 3)
	{
		write(2, "mokhames : ", 12);
		write(2, argv, ft_strlen(argv));
		write(2, ": No such file or directory\n", 29);
			__get_var(SETEXIT, -1);
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 3 || i == 4)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error1(argv, i);
	return (file);
}

void	dup_n_close(int fdin, int fdout)
{
	if (fdin > 2)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout > 2)
	{
		dup2(fdout, 1);
		close(fdout);
	}
}

int	redirect_to(t_command *cmd, t_tools *tools)
{
	t_redirect	*red;
	int			fdin;
	int			fdout;

	(void)tools;
	fdin = 0;
	fdout = 1;
	red = cmd->redirect;
	while (red && __get_var(GETEXIT, 2) != -1)
	{
		if (red->type == 3 || red->type == 4)
			fdin = open_file(red->file, red->type);
		if (red->type == 1 || red->type == 2)
			fdout = open_file(red->file, red->type);
		red = red->nextred;
	}
	dup_n_close(fdin, fdout);
	return (0);
}
//close FDs at the end ?? 