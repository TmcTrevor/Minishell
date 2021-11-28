/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:01:39 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/27 21:41:27 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sizedoublp(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	ft_herdocs_rl(char	*limiter, int fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_sigint_herdoc);
		line = readline("heredoc>");
		if (!line)
		{
			__get_var(SETEXIT, 0);
			exit(0);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			__get_var(SETEXIT, 0);
			exit(0);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

char	*ft_herdocs(char *str)
{
	int		pid;
	char	*name;
	int		fd;
	int		status;

	name = ft_strjoin("/tmp/", str);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	__get_var(SETPID, -1);
	pid = fork();
	if (pid == 0)
		ft_herdocs_rl(str, fd);
	waitpid(pid, &status, 0);
	if (status == 256)
		__get_var(SETEXIT, 1);
	__get_var(SETPID, 0);
	free(str);
	close(fd);
	return (name);
}

char	**arg_fill(t_redirect **red, char ***arg, int j)
{
	char	**a;
	char	*c;
	char	*q;

	a = ft_split1((*red)->line + j, ' ');
	if ((*red)->type == 4)
	{	
		c = ignore_quotes(a[0], 1);
		(*red)->file = ft_herdocs(c);
		if (__get_var(GETEXIT, 0) == 1)
				return (0);
	}
	else
	{
		c = dollar_check(a[0], (*red)->env);
		q = ignore_quotes(c, 1);
		(*red)->file = ft_strdup(q);
		free(c);
		c = NULL;
	}
	a[0] = NULL;
	*arg = a;
	a++;
	if (sizedoublp(a) > 0)
		return (a);
	return (NULL);
}

char	**getter(t_redirect **red, int i, char c, char ***arg)
{
	int		j;

	j = 1;
	if ((*red)->line[1] == '>' || (*red)->line[1] == '<')
		j = 2;
	if (i == 0 && (c == '>' || c == '<'))
	{
		(*red)->flag = 1;
		return (arg_fill(red, arg, j));
	}
	else
		return (helfer(red, arg, j));
	return (0);
}

void	ft_fres1(char **b)
{
	int	i;

	i = 0;
	while (b[i])
	{
		free(b[i]);
		b[i] = NULL;
		i++;
	}
	free(b);
	b = NULL;
}

int	get_argv(t_command *cmd, char **env)
{
	int			i;
	char		**b;
	t_redirect	*l;

	i = 0;
	cmd->fcmd = NULL;
	cmd->argument = NULL;
	l = cmd->redirect;
	b = NULL;
	while (i <= cmd->count)
	{
		if (cmd->cmd)
		{
			b = getter(&cmd->redirect, i, cmd->cmd[0], &cmd->fakearg);
			if (b)
				cmd->argument = ignore_quotes1(strdjoin(cmd->redirect->flag, \
					cmd->argument, b), env);
			cmd->redirect = cmd->redirect->nextred;
			i++;
		}
	}
	if (cmd->argument)
		cmd->fcmd = cmd->argument[0];
	cmd->redirect = l;
	return (1);
}
