#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

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
				int j = 0;
				//main->cmd->argument[2] =  NULL;
				//printf("%s\n",main->cmd->argument[2]);
			while (main->cmd->argument[j])
			{

				printf("p[%d] = %p\n", j, main->cmd->argument[j]);
				j++;
			}
				//free(main->cmd->argument[2]);
				//printf("s = %p -- %d\n", main->cmd->argument[0], i);
			    if (sizedoublp(main->cmd->argument) > 1)
				{
					while (main->cmd->argument[++i])
			    	{
				//	printf("s = %p -- %d\n", main->cmd->argument[i], i);
					    //if (main->cmd->argument[i])
							free(main->cmd->argument[i]);
					    main->cmd->argument[i] = NULL;
			    	}
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
  /* main->cmd->redirect = NULL;
    main->cmd->argument = NULL;
    main->cmd->cmd = NULL;
    main->cmd->fcmd = NULL;
    main->cmd->redirect->line = NULL;
    main->cmd->redirect->file = NULL;*/
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
		
       // clear_all(main);
	}
	free(main);
	//clear_all(main);
	//system("leaks minishell");
	return 0;

}
