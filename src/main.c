/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:38:42 by klino-an          #+#    #+#             */
/*   Updated: 2025/08/20 20:26:11 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char **get_cmds(char **argv, int argc)
{
    char **command;
    static int i = 2;

	if(i > argc - 2)
		return (NULL);
	command = ft_split(argv[i], ' ');
	if (!command)
		return (NULL);
	i++;
	for (int j = 0; command[j]; j++)
		printf("[%d]:%s\n", i, command[j]);
    return (command);
}

char	*search_path(char **envp)
{
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}
char	*join_path(int argc , char **argv, char **envp)
{
	char	*path;
	char	**arr_path;
	char	*full_path;
	static int		av_index = 2;
	int		i;
	int limit;
	path = search_path(envp);
	arr_path = ft_split(path, ':');
	if (!arr_path)
		return (NULL);
	limit = argc - 2;
	if (av_index > limit)
		return (NULL);
	i = 0;
	while (arr_path[i])
	{
		full_path = ft_strjoin(arr_path[i], "/");
		if (!full_path)		
			return (NULL);
		full_path = ft_strjoin(full_path, argv[av_index]);
		if (!full_path)
			return (NULL);
		printf("%s\n", full_path);
		if (access(full_path, F_OK) == 0)
		{
		    printf("entrou\n");
			av_index++;
			return (full_path);
		}
		else
			i++;
	}
	av_index++;
	//av_index nao incremente, entao sempre ira pegar o mesmo comando!
	//agora ja pega, mas tenho que tomar cuidado pois estou usando uma static variable e nao sei qual processo vai chegar primeiro!
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	int i = 1;
	int pipe_fd[2];
	int commands_count;
	if (argc != 5)
	    return (-1);
	commands_count = argc - 3;
	data.stdin = dup(0);
	data.stdout = dup(1);
	while (i <= commands_count)
	{
	    pipe(pipe_fd);
	    data.pid = fork();
	    if (data.pid < 0)
	        write (2, "Erro\n", 5);
	    else if (data.pid == 0)
	    {
	        if (i == 1)
	            data.fd = open(argv[1], O_RDONLY);
	        else if (i == commands_count)
	            data.fd = open(argv[argc - 1], 
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
	        if (data.fd < 0)
	            write(2, "Nao deu para abrir o arquivo\n", 29);
	        if (i == 1)
	            (dup2(data.fd, 0), dup2(pipe_fd[1], 1));
	        else if (i == commands_count)
	            (dup2(pipe_fd[0], 0), dup2(data.fd, 1));
	        close(data.fd);
	        char *path = join_path(argc, argv, envp);
	        char **cmd = get_cmds(argv, argc);
	        execve(path, cmd, envp);
	        //clear execve
	        write(2, "execve falhou\n", 14);
	        exit(-1);
	    }
	    i++;
	}
	if (data.pid > 0)
	{
	    int status;
	    waitpid(data.pid, &status, 0);
	    //loop para quantidade de filhos
	    wait(NULL);
	}
	return (0);
}
