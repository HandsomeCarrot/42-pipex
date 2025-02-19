/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 15:53:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(t_pdata *vars, int error)
{
	if (vars->error_msg)
	{
		ft_putstr_fd(vars->error_msg, STDERR_FILENO);
		if (vars->error_file || error)
			ft_putstr_fd(": ", STDERR_FILENO);
		free(vars->error_msg);
		vars->error_msg = NULL;
	}
	if (vars->error_file)
	{
		ft_putstr_fd(vars->error_file, STDERR_FILENO);
		if (error)
			ft_putstr_fd(": ", STDERR_FILENO);
		free(vars->error_file);
		vars->error_file = NULL;
	}
	if (error)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	clean_exit(t_pdata *vars, int exit_status, int error)
{
	print_error(vars, error);
	if (vars)
	{
		if (vars->cmd_array)
			free_dbl_str(vars->cmd_array);
		if (vars->cmd_path)
		{
			free(vars->cmd_path);
			vars->cmd_path = NULL;
		}
		if (vars->input != -1)
			close(vars->input);
		if (vars->output != -1)
			close(vars->output);
		if (vars->pip[0] != -1)
			close(vars->pip[0]);
		if (vars->pip[1] != -1)
			close(vars->pip[1]);
	}
	exit(exit_status);
}
