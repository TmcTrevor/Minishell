#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"


int	ft_error(char *c)
{
	write(1, c, ft_strlen(c));
	return (0);
}

void    clear_all(t_main *main)
{
	int i = 0;
	//t_env   *t;
	t_redirect *r;
	t_command *c;
	t_env *v;

	//free(main->line);
    if (main->cmd)
    {
	    while (main->cmd)
	    {
		    c = main->cmd;
            if (main->cmd->redirect)
		    {
			    while(main->cmd->redirect)
			    {
                    r = main->cmd->redirect;
					if (main->cmd->redirect->line)
					{
						free(main->cmd->redirect->line);
				    	main->cmd->redirect->line = NULL;
					}
					if (main->cmd->redirect->file)
				    {
						free (main->cmd ->redirect->file);
						main->cmd->redirect->file = NULL;
					}
				    main->cmd->redirect = main->cmd->redirect->nextred; 
				    free(r);
					r = NULL;
                   
			    }
		    }
		    if (main->cmd->argument)
		    {
			    while (main->cmd->argument[++i])
			    {
				free(main->cmd->argument[i]);
					 main->cmd->argument[i] = NULL;
			    }
				free(main->cmd->argument);
				main->cmd->argument = NULL;
		    }
			i = 0;
			if (main->cmd->cmd)
			{
		    	free(main->cmd->cmd);
            	main->cmd->cmd = NULL;
			}
		    if (main->cmd->fcmd)
		    {
			    free(main->cmd->fcmd);
			    main->cmd->fcmd = NULL;
		    }
		    main->cmd = main->cmd->nextcmd;
		    free(c);
            c = NULL;
        }
	}
	while (main->env)
	{
		v = main->env;
		free(main->env->value);
		main->env->value = NULL;
		main->env = main->env->next;
		free(v);
		v = NULL;
	}
}
void    set_main(t_main *main)
{
    main->line = NULL;
    main->env = NULL;
    main->count = 0;
    main->cmd = NULL;
}

int main(int ac, char **argv, char **envm)
{
	(void)ac;
	(void)argv;
	int i = 1;
	t_main  *main;
	main   = malloc(sizeof(t_main));
    set_main(main);
	
	while (i)
	{
		env_init(main, envm);
		main->line = readline("mokhamaes > ");

		if (!ft_strncmp(main->line,"exit",4))
            i = 0;
       	parse(main);
		add_history(main->line);
        free(main->line);
		
        clear_all(main);
	}
	free(main);
	//clear_all(main);
	//system("leaks minishell");
	return 0;

}
