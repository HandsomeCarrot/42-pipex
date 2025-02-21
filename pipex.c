/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 12:22:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Initializes all members of the t_pipex structure to default values.
** 
** @param data: Pointer to t_pipex structure to initialize
** 
** Sets all file descriptors to -1 (invalid) and pointers to NULL.
*/
static t_pipex	*initialize_data(t_pipex *data, char **argv, char **envp)
{
	t_pipex *new_data;

	new_data = ft_calloc(1, sizeof(t_pipex));
	if (!data)
	{
		ft_putendl_fd("Space allocation failed", STDERR_FILENO);
		exit(1);
	}
	data->argv = argv;
	data->envp = envp;
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

/*
** Opens input and output files for the pipex program.
** 
** @param data: Pointer to t_pipex structure to store file descriptors
** @param input: Path to input file
** @param output: Path to output file
** 
** Opens input file in read-only mode and output file in write-only mode,
** creating it if necessary. Sets error messages and exits on failure.
*/
static void	open_files(t_pipex *data, char *input, char *output)
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

static void	validate_commands(t_pipex *data)
{

}

/*
** Main entry point for the pipex program.
** 
** @param argc: Number of command line arguments
** @param argv: Array of command line argument strings
** @param envp: Array of environment variables
** 
** @return EXIT_SUCCESS on success, EXIT_FAILURE on error
** 
** Flow:
** 1. Validates argument count (requires exactly 4 arguments)
** 2. Creates pipe
** 3. Opens input/output files
** 4. Processes and executes commands
** 5. Cleans up resources
** 6. Waits for child processes
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	data = initialize_data(data, argv, envp);
	if (argc != 5)
	{
		data->error_msg = ft_strdup("Exactly 4 arguments needed");
		exit_program(data, EXIT_FAILURE, 0);
	}
	if (pipe(data->pipe_fd) == -1)
	{
		data->error_msg = ft_strdup("Pipe failed");
		exit_program(data, EXIT_FAILURE, 1);
	}
	open_files(data, argv[1], argv[4]);
	validate_commands(data);
	data->child[0] = execute_command(data, 0);
	data->child[1] = execute_command(data, 1);
	close_all_fds(data);
	wait_for_child_processes(data);
	if (data->child[1] != -1)
		exit_program(data, EXIT_SUCCESS, 0);
	exit_program(data, EXIT_FAILURE, 0);
}
