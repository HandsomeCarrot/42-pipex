/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/20 18:25:52 by vpoka            ###   ########.fr       */
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
	char	**argv;
	char	**envp;
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

int			main(int argc, char **argv, char **envp);

//----------command_validation.c----------//

void		process_command(t_pipex *data, char *cmd, int is_last_command);

//----------execute_commands.c----------//

pid_t		execute_command(t_pipex *data, int last);

//----------cleanup.c----------//

void		free_string_array(char **str);
void		protected_close(t_pipex *data);
void		wait_for_child_processes(t_pipex *data);

//----------exit.c----------//

void		print_error(t_pipex *data, int error);
void		exit_program(t_pipex *data, int exit_status, int error);

#endif