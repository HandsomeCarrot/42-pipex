/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/17 21:53:44 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sclose(int *fd, t_pdata *vars)
{
	if (fd && *fd && *fd != -1)
	{
		if (close(*fd) == -1)
			clean_exit(1, "Close failed", vars, EXIT_FAILURE);
		*fd = -1;
	}
}

void	clean_exit(int error, char *msg, t_pdata *vars, int exit_status)
{
	if (error)
		perror(msg);
	else if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (vars)
	{
		if (vars->cmd_array)
			free_dbl_str(vars->cmd_array);
		if (vars->cmd_path)
		{
			free(vars->cmd_path);
			vars->cmd_path = NULL;
		}
		if (vars->input && vars->input != -1)
			close(vars->input);
		if (vars->output && vars->output != -1)
			close(vars->output);
		if (vars->pip[0] && vars->pip[0] != -1)
			close(vars->pip[0]);
		if (vars->pip[1] && vars->pip[1] != -1)
			close(vars->pip[1]);
	}
	exit(exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pdata	vars;

	if (argc != 5)
		clean_exit(0, "Exactly 4 arguments needed\n", NULL, EXIT_FAILURE);
	prep_variables(&vars);
	set_cmd_vars(&vars, argv[2], envp);
	if (pipe(vars.pip) == -1)
		clean_exit(1, "Pipe failed", &vars, EXIT_FAILURE);
	vars.input = open(argv[1], O_RDONLY);
	if (vars.input == -1)
		perror(argv[1]);
	vars.child[0] = execute_command(&vars, envp, 0);
	vars.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars.output == -1)
		perror(argv[4]);
	set_cmd_vars(&vars, argv[3], envp);
	vars.child[1] = execute_command(&vars, envp, 1);
	sclose(&(vars.pip[0]), &vars);
	sclose(&(vars.pip[1]), &vars);
	sclose(&(vars.input), &vars);
	sclose(&(vars.output), &vars);
	wait_for_child(vars.child[0], &vars, 0);
	wait_for_child(vars.child[1], &vars, 1);
	clean_exit(0, NULL, &vars, EXIT_SUCCESS);
}
