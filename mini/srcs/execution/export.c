/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:47:40 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/13 01:06:06 by mokhames         ###   ########.fr       */
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

void	add_to_export(char *c, char ***env)
{
	char **s;
	s = ft_split(c, '=');
	if (find_path2(s[0], *env))
		replace(env,s[0],s[1]);
	else
		printf("")
}

int		export(char **args, char ***env)
{
    int i;
    int j;

    j = 1;
    i = ft_strdlen(args) - 1;
    if (i == 0)
        add_quotes(*env);
    else if (i > 0)
    {
        while (args[j])
        {
            if (!check_syntax(args[j]))
                add_to_export(args[j], env);
            j++;
        }
    }
    return (1);
}