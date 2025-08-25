#ifndef pipex_h
#define pipex_h

#include "Libft/libft.h"

#include <sys/wait.h>
#include <errno.h>


typedef struct s_data
{
    pid_t pid;
    int fd;
    int child1;
    int child2;
}   t_data;

void    child1(t_data data, char **argv, char **envp, int pipe_fd[2]);
void    child2(t_data data, char **argv, char **envp, int pipe_fd[2]);
char	*get_path(char **argv, char **envp, int av_index);
void    print_error(char *file, int pipe_fd[2]);
char	*ft_free_and_join(char *s1, char *s2);
char	**get_cmds(char **argv, int av_index);
void     clean_mem(char *path, char **cmd);






#endif