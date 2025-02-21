/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:22:59 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 17:07:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Sets up file descriptors for the first command in the pipeline.
 * Duplicates input to STDIN and pipe write end to STDOUT.
 * Closes unused file descriptors.
 * @param data - Pointer to pipex structure containing file descriptors
 */
static void	setup_first_command(t_pipex *data)
{
	if (dup2(data->input, STDIN_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
}

/**
 * Sets up file descriptors for the last command in the pipeline.
 * Duplicates pipe read end to STDIN and output to STDOUT.
 * Closes unused file descriptors.
 * @param data - Pointer to pipex structure containing file descriptors
 */
static void	setup_last_command(t_pipex *data)
{
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	if (dup2(data->output, STDOUT_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
}

/**
 * Executes a command by forking a child process and setting up appropriate
 * file descriptors based on command position in pipeline.
 * 
 * @param data - Pointer to pipex structure containing command info
 * @param last - Flag indicating if this is the last command
 * @return pid_t - Process ID of child process, or -1 on error
 */
pid_t	execute_command(t_pipex *data, int last)
{
	pid_t	pid;

	if ((!last && (data->input == -1 || !data->cmd_paths[last]))
		|| (last && data->output == -1))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		data->msg1 = ft_strdup("failed to create child procces");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (pid == 0)
	{
		if (!last)
			setup_first_command(data);
		else
			setup_last_command(data);
		close_all_fds(data);
		execve(data->cmd_paths[last], data->cmd_arrays[last], data->envp);
		data->msg1 = ft_strdup("command failed");
		data->msg2 = ft_strdup(data->cmd_paths[last]);
		exit_program(data, 126, 1);
	}
	return (pid);
}
