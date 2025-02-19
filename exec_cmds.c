/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:22:59 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 12:06:33 by vpoka            ###   ########.fr       */
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
		clean_exit(vars, EXIT_FAILURE, 0);
	if (dup2(vars->pip[1], STDOUT_FILENO) == -1)
		clean_exit(vars, EXIT_FAILURE, 0);
	sclose(&(vars->input), vars);
	sclose(vars->pip, vars);
	sclose(vars->pip + 1, vars);
	sclose(&(vars->output), vars);
}

static void	handle_last(t_pdata *vars)
{
	if (dup2(vars->pip[0], STDIN_FILENO) == -1)
		clean_exit(vars, EXIT_FAILURE, 0);
	if (dup2(vars->output, STDOUT_FILENO) == -1)
		clean_exit(vars, EXIT_FAILURE, 0);
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
	{
		vars->error_msg = ft_strdup("Fork failed in execute_command");
		clean_exit(vars, EXIT_FAILURE, 1);
	}
	if (pid == 0)
	{
		if (!last)
			handle_first(vars);
		else if (last)
			handle_last(vars);
		execve(vars->cmd_path, vars->cmd_array, envp);
		vars->error_msg = ft_strdup("Command failed");
		vars->error_file = ft_strdup(vars->cmd_path);
		clean_exit(vars, get_exit_code(), 1);
	}
	return (pid);
}
