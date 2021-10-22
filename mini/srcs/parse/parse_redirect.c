/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:59:26 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/22 15:14:32 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void    get_count_index(t_command *cmd)
{
    int i;
    int j;
    int open;
    
    i = 0;
	
	cmd->t[0] = 0;
    j = 1;
    open = 0;
    cmd->count = 0;
    while (cmd->cmd[i])
    {
        open = check_quotes(cmd->cmd[i], open);
        if ((cmd->cmd[i] == '<' || cmd->cmd[i] == '>') && !open)
        {
			if (i != 0)
			{
            	cmd->t[j] = i;
				cmd->count++;	
            	j++;
			}
            while (cmd->cmd[i + 1] == '<' || cmd->cmd[i+1] == '>')
                i++;
        }
        i++;
    }
    cmd->t[j] = i + 1; 
}


int     check_eol(char *c, int type)
{
    int i;
    
    i = 1;
    if (type == 2 || type == 4)
        i = 2;
    if (c[i] == '<' || c[i] == '>')
        return (0);
    while (c[i] == ' ')
        i++;
    if (c[i] == '\0')
        return (0);
    return (type);
}

char    *sub_split2(t_command *cmd, int i, int j)
{
    char *c;
	
    while (cmd->cmd[i + 1] == ' ')
        i++;
	c = ft_substr(cmd->cmd,i, j  - i);    
	return (c);
}

int		file_arg(t_command *cmd, t_env *env)
{
    int i;

    i = 0;
    (void)env;
    if (!get_type(cmd))
		return (0);
	if (!(get_argv(cmd, env)))
		return (0);
	return (1);
}

int   parse_redirection(t_command *cmd, t_env *env)
{
    int i;

    i = 0;
    cmd->redirect = NULL;
    while (cmd)
    {   
        //(void)env;
        get_count_index(cmd);
        if (!file_arg(cmd, env))
			return (0);
	    while (cmd->redirect)
		{
            printf("line = %s\n",cmd->redirect->line);
			printf("file = %s\n",cmd->redirect->file);
            printf("type = %d\n",cmd->redirect->type);
			cmd->redirect = cmd->redirect->nextred;
		}
        printf("main command = %s\n",cmd->fcmd);
        while (cmd->argument[i])
        {
            printf("argument[%d] = %s\n ",i, cmd->argument[i]);
            i++;
        }
        i = 0;
        printf("--------------------------------------------\n\3");
        
       cmd = cmd->nextcmd;
    }
	return (1);   
}