/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:09:03 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 11:02:32 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_variables(t_pdata *vars)
{
	if (vars)
	{
		vars->cmd_array = NULL;
		vars->cmd_path = NULL;
		vars->error_file = NULL;
		vars->error_msg = NULL;
		vars->input = -1;
		vars->output = -1;
		vars->pip[0] = -1;
		vars->pip[1] = -1;
		vars->child[0] = -1;
		vars->child[1] = -1;
	}
}

void	free_dbl_str(char **str)
{
	int	pos;

	pos = 0;
	while (str && str[pos])
	{
		free(str[pos]);
		str[pos] = NULL;
		pos++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	sclose(int *fd, t_pdata *vars)
{
	if (fd && *fd && *fd != -1)
	{
		if (close(*fd) == -1)
			clean_exit(1, "Close failed", vars, EXIT_FAILURE);
		*fd = -1;
	}
}

void	wait_for_child(pid_t child, t_pdata *vars, int last)
{
	int	status;

	if (child != -1)
	{
		if (waitpid(child, &status, 0) == -1)
			clean_exit(1, "waitpid failed", vars, EXIT_FAILURE);
		if (last && WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				clean_exit(0, NULL, vars, WEXITSTATUS(status));
		}
	}
	else if (last)
		clean_exit(0, NULL, vars, EXIT_FAILURE);
}
