/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:22:59 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/17 21:43:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_exit_code(void)
{
	if (errno == EACCES)
		return (126);
	else if (errno == ENOENT)
		return (127);
	return (EXIT_FAILURE);
}

static void	handle_first(t_pdata *vars)
{
	if (dup2(vars->input, STDIN_FILENO) == -1)
		clean_exit(0, NULL, vars, EXIT_FAILURE);
	if (dup2(vars->pip[1], STDOUT_FILENO) == -1)
		clean_exit(0, NULL, vars, EXIT_FAILURE);
	sclose(&(vars->input), vars);
	sclose(vars->pip, vars);
	sclose(vars->pip + 1, vars);
	sclose(&(vars->output), vars);
}

static void	handle_last(t_pdata *vars)
{
	if (dup2(vars->pip[0], STDIN_FILENO) == -1)
		clean_exit(0, NULL, vars, EXIT_FAILURE);
	if (dup2(vars->output, STDOUT_FILENO) == -1)
		clean_exit(0, NULL, vars, EXIT_FAILURE);
	sclose(&(vars->input), vars);
	sclose(vars->pip, vars);
	sclose(vars->pip + 1, vars);
	sclose(&(vars->output), vars);
}

pid_t	execute_command(t_pdata *vars, char **envp, int last)
{
	pid_t	pid;

	if ((!last && vars->input == -1) || (last && vars->output == -1)
		|| !vars->cmd_path)
		return (-1);
	pid = fork();
	if (pid == -1)
		clean_exit(1, "Fork failed", vars, EXIT_FAILURE);
	if (pid == 0)
	{
		if (!last)
			handle_first(vars);
		else if (last)
			handle_last(vars);
		execve(vars->cmd_path, vars->cmd_array, envp);
		clean_exit(1, vars->cmd_path, vars, get_exit_code());
	}
	return (pid);
}
