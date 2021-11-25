/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:33:53 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/25 09:50:00 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**delete_line(char **env, char *c)
{
	char	**new_env;
	int		i;
	int		j;
	int		sa;

	sa = ft_strdlen(env);
	i = 0;
	j = 0;
	if (!find_path2(c, env))
		return (env);
	new_env = (char **)malloc((sa) * sizeof(char *));
	garbage(&g, c);
	while (i < sa - 1)
	{
		if (!ft_strcmp(env[i], c))
			i++;
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	ft_fres(env, 1);
	return (new_env);
}

int	replace(char ***env, char *c, char *to_replace)
{
	int		i;
	int		a;
	char	**e;

	i = 0;
	e = *env;
	a = ft_strdlen(e);
	while (!ft_strnstr(e[i], c, ft_strlen(c)) && i < a)
		i++;
	if (e[i])
	{
		free(e[i]);
		e[i] = ft_strdup(ft_strjoin(c, to_replace));
		return (1);
	}
	return (0);
}
