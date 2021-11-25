/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:57:58 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 09:54:05 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error(char *c)
{
	write(1, c, ft_strlen(c));
	return (0);
}

void	set_main(t_main *main, char **env)
{
	int	a;

	a = ft_strdlen(env);
	main->line = NULL;
	main->files = NULL;
	main->count = 0;
	main->cmd = NULL;
	main->env = NULL;
	main->env = strdup21(env);
	main->env = delete_from_env(a, "OLDPWD", main->env);
}

void	ft_frees(t_garbage *g)
{
	t_garbage	*p;

	while (g)
	{	
		p = g;
		free(g->garb);
		g->garb = NULL;
		g = g->next;
		free(p);
		p = NULL;
	}
	free(g);
	g = NULL;
}

int	main(int ac, char **argv, char **envm)
{
	t_main	*main;

	(void)ac;
	(void)argv;
	__get_var(SETPID, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	main = malloc(sizeof(t_main));
	set_main(main, envm);
	while (1)
	{
		main->line = readline("mokhamaes > ");
		if (main->line)
		{
			if (parse(main))
				execute(main);
			add_history(main->line);
			free(main->line);
			clear_all(main);
		}
	}
	return (0);
}
