#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"


int	ft_error(char *c)
{
	write(1, c, ft_strlen(c));
	return (0);
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
	return 0;
}
