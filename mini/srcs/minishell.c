#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"



int main(int ac, char **argv, char **envm)
{
        char *inpt;
        char **cmd;
        pid_t pid;

        int i = 0;

        while (1)
        {
                inpt = readline("mokhamaes > ");
                cmd = ft_split(inpt,' ');
                check_cmd(inpt, cmd, envm);
                add_history(inpt);
        }
        return 0;

}