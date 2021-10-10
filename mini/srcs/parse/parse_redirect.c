/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:59:26 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/10 20:43:13 by mokhames         ###   ########.fr       */
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
    cmd->t[0] = 0;
    j = 1;
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
            while (cmd->cmd[i + 1] == '<' || cmd->cmd[i+1] == '>')
                i++;
        }
        
        i++;
    }
    cmd->t[j] = i + 1;
   
}

/*int check_next(t_command *cmd, int i)
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

}*/

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

int check_next(char *c)
{
    int type;
    if (c[0] == '>' && c[1] != '>')
       type = 1;
    if (c[0] == '>' && c[1] == '>')
        type = 2;
   if (c[0] == '<' && c[1]!= '<')
        type  = 3;
    if (c[0] == '<' && c[1] == '<')
        type = 4;
   type = check_eol(c, type);
   return (type);
}

void       redirect(t_command *cmd, int type, int i)
{
    char *c;
    int a;
    
    
    
    c = ft_substr(cmd->cmd,cmd->t[i], cmd->t[i+1] - cmd->t[i]);
    ft_lstadd_back2(&cmd->redirect, new_stack_red(c));
    //printf("|%s|\n",c);
    ///error check()
    if (i != 0)
    {
       // printf("|%s|\n",c);
        a = check_next(c);
        if (a == 0)
        {
            printf("syntax error\n");
        }
    }
}

void    get_type(t_command *cmd)
{
    int i;
    int type;

    i = 0;
    while (i <= cmd->count)
    {
        type = check_next(cmd->cmd + cmd->t[i]);
        redirect(cmd,type, i);
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
        printf("\n\n");
        file_arg(cmd);
        while (cmd->redirect)
        {
            printf("red = %s\n",cmd->redirect->line);
            cmd->redirect = cmd->redirect->nextred;
        }
        cmd = cmd->nextcmd;
    }
        
}