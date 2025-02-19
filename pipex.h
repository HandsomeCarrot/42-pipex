/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 19:22:57 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

//----------struct----------//

typedef struct s_pipex
{
	char	**cmd_array;
	char	*cmd_path;
	char	*error_file;
	char	*error_msg;
	int		input;
	int		output;
	int		pipe_fd[2];
	pid_t	child[2];
}			t_pipex;

//----------pipex.c----------//

void		initialize_data(t_pipex *data);
void		open_files(t_pipex *data, char *input, char *output);

int			main(int argc, char **argv, char **envp);

//----------command_validation.c----------//

void		process_command(t_pipex *data, char *cmd, char **envp);

//----------execute_commands.c----------//

pid_t		execute_command(t_pipex *data, char **envp, int last);

//----------cleanup.c----------//

void		free_string_array(char **str);
void		protected_close(int *fd, t_pipex *data);
void		wait_for_child_processes(t_pipex *data);

//----------exit.c----------//

void		print_error(t_pipex *data, int error);
void		exit_program(t_pipex *data, int exit_status, int error);

#endif