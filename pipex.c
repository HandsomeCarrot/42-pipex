/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 19:35:41 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_data(t_pipex *data)
{
	data->cmd_array = NULL;
	data->cmd_path = NULL;
	data->error_file = NULL;
	data->error_msg = NULL;
	data->input = -1;
	data->output = -1;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->child[0] = -1;
	data->child[1] = -1;
}

void	open_files(t_pipex *data, char *input, char *output)
{
	data->input = open(input, O_RDONLY);
	if (data->input == -1)
	{
		data->error_msg = ft_strdup("Input file");
		data->error_file = ft_strdup(input);
		print_error(data, 1);
	}
	data->output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output == -1)
	{
		data->error_msg = ft_strdup("Output file");
		data->error_file = ft_strdup(output);
		print_error(data, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	initialize_data(&data);
	if (argc != 5)
	{
		data.error_msg = ft_strdup("Exactly 4 arguments needed");
		exit_program(&data, EXIT_FAILURE, 0);
	}
	if (pipe(data.pipe_fd) == -1)
	{
		data.error_msg = ft_strdup("Pipe failed");
		exit_program(&data, EXIT_FAILURE, 1);
	}
	open_files(&data, argv[1], argv[4]);
	process_command(&data, argv[2], envp);
	data.child[0] = execute_command(&data, envp, 0);
	process_command(&data, argv[3], envp);
	data.child[1] = execute_command(&data, envp, 1);
	protected_close(NULL, &data);
	wait_for_child_processes(&data);
	exit_program(&data, EXIT_SUCCESS, 0);
}
