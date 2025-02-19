/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:22:59 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 19:23:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	map_errno_to_exit_code(void)
{
	if (errno == EACCES)
		return (126);
	else if (errno == ENOENT)
		return (127);
	return (EXIT_FAILURE);
}

static void	setup_first_command(t_pipex *data)
{
	if (dup2(data->input, STDIN_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	protected_close(NULL, data);
}

static void	setup_last_command(t_pipex *data)
{
	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	if (dup2(data->output, STDOUT_FILENO) == -1)
		exit_program(data, EXIT_FAILURE, 0);
	protected_close(NULL, data);
}

pid_t	execute_command(t_pipex *data, char **envp, int is_last_command)
{
	pid_t	pid;

	if ((!is_last_command && data->input == -1)
		|| (is_last_command && data->output == -1))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		data->error_msg = ft_strdup("Fork failed in execute_command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (pid == 0)
	{
		if (!is_last_command)
			setup_first_command(data);
		else if (is_last_command)
			setup_last_command(data);
		execve(data->cmd_path, data->cmd_array, envp);
		data->error_msg = ft_strdup("Command failed");
		data->error_file = ft_strdup(data->cmd_path);
		exit_program(data, map_errno_to_exit_code(), 1);
	}
	return (pid);
}
