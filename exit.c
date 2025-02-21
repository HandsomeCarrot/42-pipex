/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 15:50:57 by vpoka            ###   ########.fr       */
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
	if (data->msg1)
	{
		ft_putstr_fd(data->msg1, STDERR_FILENO);
		if (data->msg1 || include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		free(data->msg1);
		data->msg1 = NULL;
	}
	if (data->msg2)
	{
		ft_putstr_fd(data->msg2, STDERR_FILENO);
		if (include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		else
			ft_putchar_fd('\n', STDERR_FILENO);
		free(data->msg2);
		data->msg2 = NULL;
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
	if (data->cmd_arrays)
	{
		free_string_array(data->cmd_arrays[0]);
		free_string_array(data->cmd_arrays[1]);
	}
	if (data->cmd_paths)
		free_string_array(data->cmd_paths);
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
