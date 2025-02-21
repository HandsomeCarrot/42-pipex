/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:09:03 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 18:25:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Free a NULL-terminated array of strings
 *
 * @param str Double pointer to NULL-terminated array of strings
 *
 * Iterates through array freeing each string and setting pointers to NULL.
 * Finally frees the array pointer. Handles NULL input gracefully.
 */
void	free_string_array(char **str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		free(str[pos]);
		str[pos] = NULL;
		pos++;
	}
	if (str)
		free(str);
}

/**
 * @brief Safely close a file descriptor with error handling
 *
 * @param data Main pipex data structure for error handling
 * @param fd Pointer to file descriptor to close
 *
 * Checks if descriptor is valid (>2), closes it, and sets to -1.
 * Handles close errors by setting error message and exiting.
 */
static void	protected_close(t_pipex *data, int *fd)
{
	if (*fd > 2 && close(*fd) == -1)
	{
		data->msg1 = ft_strdup("Failed to close file descriptor");
		data->msg2 = ft_itoa(*fd);
		exit_program(data, EXIT_FAILURE, 1);
	}
	else if (*fd > 2)
		*fd = -1;
}

/**
 * @brief Close all open file descriptors
 *
 * @param data Main pipex data structure containing file descriptors
 *
 * Safely closes all file descriptors (input, output, pipe ends) and handles
 * errors. Sets descriptors to -1 after closing.
 */
void	close_all_fds(t_pipex *data)
{
	protected_close(data, &data->pipe_fd[0]);
	protected_close(data, &data->pipe_fd[1]);
	protected_close(data, &data->input);
	protected_close(data, &data->output);
}

/**
 * @brief Wait for child processes to complete
 *
 * @param data Main pipex data structure with child PIDs
 *
 * Waits for both command processes using waitpid(). Handles wait failures and
 * propagates second child's exit status.
 */
void	wait_for_child_processes(t_pipex *data)
{
	int	status;

	if (data->child[0] >= 0 && waitpid(data->child[0], NULL, 0) == -1)
	{
		data->msg1 = ft_strdup("waitpid failed for 1st command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (data->child[1] >= 0 && waitpid(data->child[1], &status, 0) == -1)
	{
		data->msg1 = ft_strdup("waitpid failed for 2nd command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (data->child[1] != -1 && WIFEXITED(status))
		exit_program(data, WEXITSTATUS(status), 0);
}
