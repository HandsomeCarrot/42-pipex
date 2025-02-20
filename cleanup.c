/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:09:03 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/20 14:35:56 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees a NULL-terminated array of strings and the array itself
 * 
 * Iterates through each string, freeing memory and setting pointers to NULL.
 * Finally frees the array pointer. Handles NULL input gracefully.
 * 
 * @param str Double pointer to NULL-terminated array of strings
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
 * @brief Safely closes file descriptors and handles errors
 * 
 * If a valid file descriptor pointer is provided, closes it and updates status.
 * If NULL is passed, closes all pipe descriptors (input, output, pipe ends).
 * Sets descriptors to -1 after closing. Logs errors to pipex data structure.
 * 
 * @param file_descriptor Pointer to file descriptor integer
 * @param data Main pipex data structure for error tracking
 */
void	protected_close(int *file_descriptor, t_pipex *data)
{
	if (file_descriptor && *file_descriptor != -1)
	{
		if (close(*file_descriptor) == -1)
		{
			data->error_msg = ft_strdup("Close failed for file_descriptor");
			data->error_file = ft_itoa(*file_descriptor);
			exit_program(data, EXIT_FAILURE, 1);
		}
		*file_descriptor = -1;
	}
	else if (!file_descriptor)
	{
		protected_close(&(data->pipe_fd[0]), data);
		protected_close(&(data->pipe_fd[1]), data);
		protected_close(&(data->input), data);
		protected_close(&(data->output), data);
	}
}

/**
 * @brief Waits for child processes to complete and handles exit status
 * 
 * Uses waitpid() for both command processes. Checks for wait failures and
 * exits with appropriate errors. Propagates second child's exit status.
 * 
 * @param data Main pipex data structure with child PIDs and error fields
 */
void	wait_for_child_processes(t_pipex *data)
{
	int	status;

	if (data->child[0] != -1 && waitpid(data->child[0], NULL, 0) == -1)
	{
		data->error_msg = ft_strdup("Waitpid failed for 1st command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (data->child[1] != -1 && waitpid(data->child[1], &status, 0) == -1)
	{
		data->error_msg = ft_strdup("Waitpid failed for 2nd command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (data->child[1] != -1 && WIFEXITED(status))
		exit_program(data, WEXITSTATUS(status), 0);
}
