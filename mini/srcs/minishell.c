/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:57:58 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/23 20:21:35 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void        garbage(t_garbage **garbage, void *address)
{
    t_garbage *new;

    new = (t_garbage *)malloc(sizeof(t_garbage));
    new->next = *(garbage);
    new->garb = address;
    *garbage = new;
}

char		**strdup21(char **b)
{
	int i;
	int j;
	char **c;

	j = 0;
	if (!b)
		return NULL;
	i = ft_strdlen(b);
	c = malloc((i + 1)* sizeof(char *));
	garbage(&g, c);
	while (j < i)
	{
		c[j] = ft_strdup(b[j]);
		j++;
	}
	c[i] = NULL;
	return (c);
}

int	ft_error(char *c)
{
	write(1, c, ft_strlen(c));
	return (0);
}

void    set_main(t_main *main, char **env)
{
    main->line = NULL;
	main->files = NULL;
    main->count = 0;
    main->cmd = NULL;
	main->env = NULL;
	main->env = strdup21(env);
	main->env = delete_line(main->env, "OLDPWD");
}

void	ft_frees(t_garbage *g)
{
	t_garbage *p;
	while(g)
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

int main(int ac, char **argv, char **envm)
{
	(void)ac;
	(void)argv;
	int i = 1;
	t_main  *main;
	__get_var(SETPID, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	
	main   = malloc(sizeof(t_main));
	//g->status = 0;
    set_main(main, envm);
	while (i)
	{
		
		main->line = readline("mokhamaes > ");
		if (main->line)
		{
			if (parse(main))
				execute(main);
			//write(2, ft_itoa(g->status), 2);
			add_history(main->line);
			free(main->line);
    		clear_all(main);	
		}
		else
			i = 0;
	}
	free_argument(main->env);
	free(main);
	ft_frees(g);
	system("leaks minishell");
	return 0;
}