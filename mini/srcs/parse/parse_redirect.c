/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:59:26 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/09 18:07:18 by mokhames         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void    get_count_index(t_command *cmd)
{
    int i;
    char **c;
    int j;
    int open;
    
    i = 0;
    j = 0;
    open = 0;
    cmd->count = 0;
    while (cmd->cmd[i])
    {
        open = check_quotes(cmd->cmd[i], open);
        if ((cmd->cmd[i] == '<' || cmd->cmd[i] == '>') && !open)
        {
            cmd->t[j] = i;
            cmd->count++;
            j++;
        }
        i++;
    }
    cmd->t[j] = i + 1;
   // printf(" -----%s\n",cmd->cmd);
}

int check_next(t_command *cmd, int i)
{
    if (cmd->cmd[cmd->t[i]] == '>' && cmd->cmd[cmd->t[i + 1]] != '>')
        return (1);
    if (cmd->cmd[cmd->t[i]] == '>' && cmd->cmd[cmd->t[i + 1]] == '>')
        return (2);
   if (cmd->cmd[cmd->t[i]] == '<' && cmd->cmd[cmd->t[i + 1]] != '<')
        return (3);
    if (cmd->cmd[cmd->t[i]] == '<' && cmd->cmd[cmd->t[i + 1]] == '<')
        return (4);
   return (0);
}

void       redirect(t_command *cmd, int type, int i)
{
    char *c;

    c = ft_substr(cmd->cmd,cmd->t[i], cmd->t[i+1] - cmd->t[i]);
    printf("%s\n",c);
}

void    get_type(t_command *cmd)
{
    int i;
    int type;

    i = 0;
    while (i <= cmd->count)
    {
        type = check_next(cmd, i);
        redirect(cmd, type, i);
        i++;
    
    }   
}

void    file_arg(t_command *cmd)
{
    int i;

    i = 0;
    //while (i <= cmd->count)
    //{
        get_type(cmd);
        //get_arg(cmd->redirect);
       // get_file(cmd->redirect);
     //   i++;
   // }
}

void   parse_redirection(t_command *cmd)
{
    
    while (cmd)
    {
        get_count_index(cmd);
        printf("%d\n",cmd->count);
        file_arg(cmd);
        cmd = cmd->nextcmd;
    }
        
}