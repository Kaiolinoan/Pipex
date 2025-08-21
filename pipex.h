#ifndef pipex_h
#define pipex_h

#include "Libft/libft.h"

#include <sys/wait.h>


typedef struct s_data
{
    pid_t pid;
    int stdin;
    int stdout;
    int fd;
}   t_data;

char	*join_path(char *raw_path, char **argv, int argc, int av_index);
char	*get_path(int argc, char **argv, char **envp);
char	**get_cmds(char **argv, int argc);
char	*search_path(char **envp);



#endif