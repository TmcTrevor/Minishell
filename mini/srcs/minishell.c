/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:57:58 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/10 10:27:53 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


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

int main(int ac, char **argv, char **envm)
{
	(void)ac;
	(void)argv;
	int i = 1;
	t_main  *main;
	main   = malloc(sizeof(t_main));
    set_main(main, envm);
	while (i)
	{
		main->line = readline("mokhamaes > ");
		if (!ft_strncmp(main->line,"exit",4))
        	i = 0;
       	parse(main);
		execute(main);
		add_history(main->line);
		free(main->line);
    	clear_all(main);
	}
	free(main);
	return 0;
}

// 4 
// char **res;
// char *word;
// res = (char **)malloc((s +1) * sizeof(char **));
// while (i < s)
// {
// 	word = 
// 	res[i] = ft_strdup(word);
// 	i++;
// }
// res[i] = NULL;
// free(word);
// return res;
