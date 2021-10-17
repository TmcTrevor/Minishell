/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhames <mokhames@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 10:59:26 by mokhames          #+#    #+#             */
/*   Updated: 2021/10/15 15:07:52 by mokhames         ###   ########.fr       */
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
	//printf("%d\n", i);
    cmd->t[j] = i + 1; 
	//printf("%d\n",cmd-)
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
	type = 0;
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

char    *sub_split2(t_command *cmd, int i, int j)
{
    char *c;
	
    while (cmd->cmd[i + 1] == ' ')
        i++;
	c = ft_substr(cmd->cmd,i, j  - i);    
	return (c);
}

int      redirect(t_command *cmd, int i)
{
    char *c;
 
    int a;
    
    c = ft_substr(cmd->cmd,cmd->t[i], cmd->t[i+1] - cmd->t[i]);
	a = 0;
    if (i == 0 && (cmd->cmd[0] == '>' || cmd->cmd[0] == '<'))
    {
        a = check_next(c);
        if (a == 0)
    	{
            printf("syntax error\n");
			return (0);
     	  }

    }
	if (i != 0)
    {
        a = check_next(c);
        if (a == 0)
    	{
            printf("syntax error\n");
			return (0);
     	  }
    }
	ft_lstadd_back2(&cmd->redirect, new_stack_red(c,a));
	return (1);
}

int    get_type(t_command *cmd)
{
    int i;

    i = 0;
    while (i <= cmd->count)
    {
        if (!redirect(cmd, i))
			return (0);
        i++;
    }  
	return (1); 
}

char	**getter(t_redirect **red, int i, char c, int *e)
{
    char **a;
    int j;
    j = 1;
    if ((*red)->line[1] == '>' || (*red)->line[1] == '<')
        j = 2;
	if (i == 0 && (c== '>' || c == '<'))
    {
        a = ft_split1((*red)->line + j, ' ');
        (*red)->file = ft_strdup(a[0]);
        a++;
        *e = 1; 
    }
    else
    {
		if (((*red)->line[0] == '>' || (*red)->line[0] == '<'))
		{
			a = ft_split1((*red)->line + j, ' ');
			(*red)->file = ft_strdup(a[0]);
			a++;
            *e = 2;
		}
		else
		{
            (*red)->file = ft_strdup("");
			a = ft_split1((*red)->line, ' ');
			*e = 3;
		}
    }
    return a;
}


int		get_argv(t_command *cmd)
{
	int i;
    int c;
    char **a;
    char **b;
	int j;
    int k;
    t_redirect *l;

	i = 0;
    k = 0;
    c = 0;
	j = 0;
    a = NULL;
    l = cmd->redirect;
	while (i <= cmd->count)
	{
		b = getter(&cmd->redirect, i, cmd->cmd[0], &c);
        j = 0;
        cmd->argument = strdjoin(cmd->argument, b);
        cmd->redirect = cmd->redirect->nextred;
		i++;
	}
    cmd->fcmd = cmd->argument[0];
    cmd->argument++;
    cmd->redirect = l;
    //printf("line = %s\n",cmd->redirect->line);
	return (1);
}

int		file_arg(t_command *cmd)
{
    int i;

    i = 0;
 
    if (!get_type(cmd))
		return (0);
	if (!(get_argv(cmd)))
		return (0);
//printf("line = %s\n",cmd->redirect->line);
	return (1);
}

int   parse_redirection(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd)
    {
        get_count_index(cmd);
        if (!file_arg(cmd))
			return (0);
		while (cmd->redirect)
		{
            printf("line = %s\n",cmd->redirect->line);
			printf("file = %s\n",cmd->redirect->file);
            printf("type = %d\n",cmd->redirect->type);
			cmd->redirect = cmd->redirect->nextred;
		}
        while (cmd->argument[i])
        {
            printf("argument[%d] = %s\n ",i, cmd->argument[i]);
            i++;
        }
        //printf("\n\n");
        cmd = cmd->nextcmd;
    }

	return (1);   
}