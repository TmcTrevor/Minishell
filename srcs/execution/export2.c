/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:47:02 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 00:00:34 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	half_write(char **my_env, int i, int j)
{
	while (my_env[i][j])
	{
		if (my_env[i][j] == '\\' || my_env[i][j] == '$' || my_env[i][j] == 34)
			write(1, "\\", 1);
		write(1, &(my_env[i][j]), 1);
		j++;
	}
}

void	ok_write(char **my_env, int i, int j)
{
	int	b;

	b = 0;
	write(1, "declare -x ", 11);
	while (my_env[i][j])
	{
		if (my_env[i][j] == '=')
		{
			write(1, "=", 1);
			b = 1;
			write(1, "\"", 1);
			j++;
			break ;
		}
		else
			write(1, &(my_env[i][j]), 1);
		j++;
	}
	half_write(my_env, i, j);
	if (b == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	add_quotes(char **my_env)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (my_env[i] != NULL)
	{
		j = 0;
		while (my_env[i][j])
		{
			if (my_env[i][j] != '=')
			{
				ok_write(my_env, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	get_fo_index(char *c)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != '=')
		i++;
	if (i == ft_strlen(c))
		i = -1;
	return (i);
}


char	**delete_from_env(int sa, char *c, char **env)
{
	int		i;
	int		j;
	int		k;
	char	*c1;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = (char **)malloc((sa) * sizeof(char *));
	garbage(&g, new_env);
	while (i < sa)
	{
		k = get_fo_index(env[i]);
		if (env[i])
		{
			c1 = ft_substr(env[i], 0, k);
			if (!ft_strcmp(c, c1))
				i++;
		}
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (return_free(env, new_env));
}
