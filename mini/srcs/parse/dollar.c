/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:21:15 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/22 16:04:00 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index(char *c, char w)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (c[i] == w || c[i] == ' ')
			return (i);
		i++;
	}
	return (-1);	
}

/*char	*dollar_check(char *c, char *s,t_env *env)
{
	int i;
	char *sub;


	i = 0;
	while (c[i])
		i++;
	sub = ft_substr(c,1,i - 2);
	if (c[0] == '\'' && c[i - 1] == '\'' && !(strcmp(sub, s)))
		return (s);
	if ((i = get_index(s, '$')) != -1)
	{
		while (env)
		{
			if (!(ft_strncmp(env->value, s + i + 1, ft_strlen(s + i) - 1)))
			{
				//free(s);
				sub = ft_substr(s, 0, i);
				char *q = env->value + ft_strlen(s + i);
				s = ft_strcat(sub, q);
				//printf("sub == %s  -------- q = %s --- s = %s\n", sub, q,s);
				//s = ft_strdup(ft_strcat(sub,q));
				return (s);
			}
			env = env->next;
		}
		s = ft_strdup("");
	}
    return (s);   
}*/
/*char	*dollar_check(char *c, char *s,t_env *env)
{
	int i;
	int j;
	char *sub;
	char *res;
	t_env *env1;

	i = 0;
	env1 = env;
	res = (char *)malloc(1 * sizeof(char ));
	while (c[i])
		i++;
	sub = ft_substr(c,1,i - 2);
	if (c[0] == '\'' && c[i - 1] == '\'' && !(strcmp(sub, s)))
		return (s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = get_index(s + i + 1, '$');
			printf("j = %d\n", j);
			if (j == -1)
				j = ft_strlen(s + i) - 1;
			sub = ft_substr(s + i ,1, j);
			env1 = env;
			while (env1)
			{
				if (!(ft_strncmp(env1->value, sub, j)) && env1->value[j] == '=')
				{
					res = ft_strjoin(res, env1->value + j + 1);
					i += j;
				}
				env1= env1->next;
			}	
		}
		else if (s[i])
			res = ft_joinchar(res, s[i]);
		printf("res = %s---  s[%d] = %c\n", res, i, s[i]);
		i++;
	}
    return (res);   
}*/
char	*check_env(char *c, char *res, t_env *env, int *k)
{
	while (env)
	{
		if (!(ft_strncmp(env->value, c, ft_strlen(c))) && env->value[ft_strlen(c)] == '=')
		{
			printf("sub = %s ------ env = %s\n",c, env->value +ft_strlen(c) + 1);
			res = ft_strjoin(res, env->value + ft_strlen(c) + 1);
			*k = 1;
			return (res);
		}
		env = env->next;
	}
	printf("dsd\n");
	return (res);
}

char	*dollar_check(char *c, char *s,t_env *env)
{
	int i;
	int j;
	int k;
	char *sub;
	k = 0;
	char *res;
	t_env *env1;

	i = 0;
	env1 = env;
	res = (char *)malloc(1 * sizeof(char ));
	res[0] = '\0'; 
	while (c[i])
		i++;
	if (!ft_strchr(s, '$'))
	{
		free(res);
		return (s);
	}
	sub = ft_substr(c,1,i - 2);
	if (c[0] == '\'' && c[i - 1] == '\'' && !(strcmp(sub, s)))
	{
			free(sub);
		return (s);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env1 = env;
			j = 1;
			k = 0;
			while (!k && s[i + j - 1])
			{
				sub = ft_substr(s + i + 1, 0 , j);
				res = check_env(sub, res, env1,&k);
				j++;
			}
			i += j;
		}
		else if (s[i])
		{
			res = ft_joinchar(res, s[i]);
			i++;
		}
	}
	free(sub);
	free(s);
    return (res);   
}