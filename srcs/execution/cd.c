/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:53:04 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/24 23:45:09 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_senv(char **env, char *c)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], c, ft_strlen(c)))
		i++;
	if (env[i])
		printf("%s\n", env[i]);
	else
	{
		printf("not found\n");
		return (-1);
	}
	return (i);
}

void	add_oldpwd(char *myp, char ***env)
{
	char	*noldpwd;

	if (!find_path2("OLDPWD", *env))
	{
		noldpwd = ft_strjoin("OLDPWD=", myp);
		*env = strdup23(*env, noldpwd);
		free(noldpwd);
		noldpwd = NULL;
	}
}

void	cd_to_home(char *myp, char ***env)
{
	char	*noldpwd;
	char	*p;

	replace(env, "OLDPWD=", myp);
	p = find_path2("HOME", *env);
	if (p)
	{
		chdir(find_path2("HOME", *env));
		noldpwd = getcwd(NULL, 0);
		replace(env, "PWD=", noldpwd);
		free(noldpwd);
		noldpwd = NULL;
	}
	else
		perror("minishell: cd: HOME not set\n");
}

void	no_file(char *cmd)
{
	write(2, "mokhames: cd: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 29);
	__get_var(SETEXIT, 1);
}

int	cd(char **cmd, char ***env)
{
	char	*noldpwd;
	char	*myp;

	myp = getcwd(NULL, 0);
	garbage(&g, myp);
	add_oldpwd(myp, env);
	if (!cmd[1])
		cd_to_home(myp, env);
	else if (!chdir(cmd[1]))
	{
		replace(env, "OLDPWD=", myp);
		noldpwd = getcwd(NULL, 0);
		replace(env, "PWD=", noldpwd);
		free(noldpwd);
		noldpwd = NULL;
	}
	else
		no_file(cmd[1]);
	free(myp);
	myp = NULL;
	return (1);
}
