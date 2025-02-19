/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 19:23:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(t_pipex *data, int include_errno)
{
	if (data->error_msg)
	{
		ft_putstr_fd(data->error_msg, STDERR_FILENO);
		if (data->error_file || include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		free(data->error_msg);
		data->error_msg = NULL;
	}
	if (data->error_file)
	{
		ft_putstr_fd(data->error_file, STDERR_FILENO);
		if (include_errno)
			ft_putstr_fd(": ", STDERR_FILENO);
		free(data->error_file);
		data->error_file = NULL;
	}
	if (include_errno)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

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
	if (data->input != -1)
		close(data->input);
	if (data->output != -1)
		close(data->output);
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	exit(exit_code);
}
