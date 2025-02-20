/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/20 19:18:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Prints error messages from pipex data structure
 *
 * Outputs error messages stored in the t_pipex structure to stderr.
 * Handles formatting of error message components and system error messages.
 * Frees error message strings after printing.
 *
 * @param data Pointer to pipex data structure containing error info
 * @param include_errno Flag to include system error message (errno)
 */
void	print_error(t_pipex *data, int include_errno)
{
	if (data->error_msg)
	{
		ft_putstr_fd(data->error_msg, STDERR_FILENO);
		if (data->error_file || include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		free(data->error_msg);
		data->error_msg = NULL;
	}
	if (data->error_file)
	{
		ft_putstr_fd(data->error_file, STDERR_FILENO);
		if (include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		free(data->error_file);
		data->error_file = NULL;
	}
	if (include_errno)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

/**
 * @brief Cleanly exits the program with specified exit code
 *
 * Performs cleanup operations including error message printing, memory
 * deallocation, and file descriptor closing before exiting.
 *
 * @param data Pointer to pipex data structure to clean up
 * @param exit_code Process exit code to return to OS
 * @param include_errno Flag to include system error message (errno)
 */
void	exit_program(t_pipex *data, int exit_code, int include_errno)
{
	print_error(data, include_errno);
	if (data->cmd_array)
		free_string_array(data->cmd_array);
	if (data->cmd_path)
	{
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	if (data->input > 2)
		close(data->input);
	if (data->output > 2)
		close(data->output);
	if (data->pipe_fd[0] > 2)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] > 2)
		close(data->pipe_fd[1]);
	free(data);
	exit(exit_code);
}
