/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 18:17:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Print error messages from pipex data structure
 *
 * @param data Pointer to pipex data structure containing error info
 * @param include_errno Flag to include system error message
 *
 * Outputs error messages to stderr with appropriate formatting. Handles memory
 * cleanup of error message strings after printing.
 */
void	print_error(t_pipex *data, int include_errno)
{
	if (data->msg1)
	{
		ft_putstr_fd(data->msg1, STDERR_FILENO);
		if (data->msg2 || include_errno)
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
 * @brief Clean up resources and exit program
 *
 * @param data Pointer to pipex data structure to clean up
 * @param exit_code Process exit code to return
 * @param include_errno Flag to include system error message
 *
 * Performs complete cleanup including:
 * - Printing error messages
 * - Freeing allocated memory
 * - Closing file descriptors
 * Before exiting with specified code
 */
void	exit_program(t_pipex *data, int exit_code, int include_errno)
{
	print_error(data, include_errno);
	if (data->cmd_arrays[0])
		free_string_array(data->cmd_arrays[0]);
	if (data->cmd_arrays[1])
		free_string_array(data->cmd_arrays[1]);
	if (data->cmd_paths[0])
		free(data->cmd_paths[0]);
	if (data->cmd_paths[1])
		free(data->cmd_paths[1]);
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
