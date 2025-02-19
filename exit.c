/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:18:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 11:08:14 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*print_error(t_pdata *vars, int error)
{
	
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
