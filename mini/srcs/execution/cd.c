/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:11:34 by mokhames          #+#    #+#             */
/*   Updated: 2021/11/12 22:41:55 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int    print_senv(char **env, char *c)
{
    int i;
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

int	cd(char **cmd, char ***env)
{
    char *noldpwd;
    char *myp;

    myp = getcwd(NULL, 0);
    if (!find_path2("OLDPWD", *env))
    {
        noldpwd = ft_strjoin("OLDPWD=", myp);
        *env = strdup23(*env, noldpwd);
        free(noldpwd);
        noldpwd = NULL;
    }
    if (!cmd[1])
    {
        replace(env,"OLDPWD=",myp);
        chdir(find_path2("HOME", *env));
        noldpwd = ft_strjoin("PWD=", getcwd(NULL, 0));
        replace(env, "PWD=", noldpwd);
        free(noldpwd);
        noldpwd = NULL;
        
    }
	else if(!chdir(cmd[1]))
    {
        replace(env,"OLDPWD=",myp);
		noldpwd = ft_strjoin("PWD=", getcwd(NULL, 0));
        replace(env, "PWD=", noldpwd);
        free(noldpwd);
        noldpwd = NULL;
    }
    else
    {
		write(1, "mokhames: cd: ", 11);
		write(1, cmd[1], ft_strlen(cmd[1]));
		write(1, ": No such file or directory\n", 29);
		return (127);
	}
    
	return (1);
}