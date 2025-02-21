/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 18:20:28 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Opens input and output files for the pipex program
 *
 * @param data Pointer to t_pipex structure to store file descriptors
 *
 * Opens input file in read-only mode and output file in write-only mode,
 * creating it if necessary. Sets error messages and prints them.
 */
static void	open_files(t_pipex *data)
{
	data->input = open(data->argv[1], O_RDONLY);
	if (data->input == -1)
	{
		data->msg1 = ft_strdup("input file");
		data->msg2 = ft_strdup(data->argv[1]);
		print_error(data, 1);
	}
	data->output = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output == -1)
	{
		data->msg1 = ft_strdup("output file");
		data->msg2 = ft_strdup(data->argv[4]);
		print_error(data, 1);
	}
}

/**
 * @brief Initialize the pipex data structure with program arguments
 *
 * @param data Pointer to pipex data structure to initialize
 * @param argv Array of command line arguments
 * @param envp Array of environment variables
 *
 * Sets up initial program state including command arrays, file descriptors,
 * and pipe creation. Processes both commands in the pipeline.
 */
static void	initialize_data(t_pipex *data, char **argv, char **envp)
{
	data->argv = argv;
	data->envp = envp;
	open_files(data);
	if (pipe(data->pipe_fd) == -1)
	{
		data->msg1 = ft_strdup("creating pipe failed");
		exit_program(data, EXIT_FAILURE, 1);
	}
	if (data->input >= 0)
		process_command(data, 0);
	if (data->output >= 0)
		process_command(data, 1);
	data->child[0] = -1;
	data->child[1] = -1;
}

/**
 * @brief Main entry point for the pipex program
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @param envp Array of environment variables
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error
 *
 * Implements Unix pipe behavior to execute commands in a pipeline:
 * 1. Validates argument count (requires exactly 4 arguments)
 * 2. Creates pipe for inter-process communication
 * 3. Opens input/output files
 * 4. Processes and executes commands
 * 5. Cleans up resources
 * 6. Waits for child processes to complete
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	data = ft_calloc(1, sizeof(t_pipex));
	if (!data)
	{
		ft_putendl_fd("space allocation failed", STDERR_FILENO);
		exit(1);
	}
	if (argc != 5)
	{
		data->msg1 = ft_strdup("exactly 4 arguments needed");
		exit_program(data, EXIT_FAILURE, 0);
	}
	initialize_data(data, argv, envp);
	data->child[0] = execute_command(data, 0);
	data->child[1] = execute_command(data, 1);
	close_all_fds(data);
	wait_for_child_processes(data);
	if (data->child[1] != -1)
		exit_program(data, EXIT_SUCCESS, 0);
	exit_program(data, EXIT_FAILURE, 0);
}
