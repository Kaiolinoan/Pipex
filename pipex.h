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


#endif