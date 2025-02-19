/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:09:03 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 19:22:57 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	wait_for_child_processes(t_pipex *data)
{
	int	status;

	if (data->child[0] != -1 && waitpid(data->child[0], NULL, 0) == -1)
	{
		data->error_msg = ft_strdup("Waitpid failed for 1st command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (waitpid(data->child[1], &status, 0) == -1)
	{
		data->error_msg = ft_strdup("Waitpid failed for 2nd command");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (WIFEXITED(status))
		exit_program(data, WEXITSTATUS(status), 0);
}
