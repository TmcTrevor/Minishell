/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:47:40 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/13 18:49:57 by mokhames         ###   ########.fr       */
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

int		get_fo_index(char *c)
{
	int i;
	
	i = 0;
	while (c[i] && c[i] != '=')
		i++;
	if (i == ft_strlen(c))
		i = -1;
	return (i);
}

/*char	*check_dollar(char *c, char **env)
{
	
}*/

void	add_to_export(char *c, char ***env)
{

	char *s;
	char *fp;
	int	i;

	//checK_dollar(c, *env);
	//printf("%s\n", c);
	i = get_fo_index(c);
	if (i == -1)
	{
		if (!find_path2(c, *env))
			*env= strdup23(*env, c);
		return ;
	}
	fp = ft_substr(c, 0, i);
	s = ft_strchr(c, '=');
	printf("%s\n", fp);
	printf(" s= %s\n",s );
	if (find_path2(fp, *env))
		replace(env,fp,s);
	else
		*env= strdup23(*env, c);
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
           {
				printf("**************%s\n", args[j]);
				add_to_export(args[j], env);
			}
            j++;
        }
    }
    return (1);
}