/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:09:03 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 18:22:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_dbl_str(char **str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		free(str[pos]);
		str[pos] = NULL;
		pos++;
	}
	if (str)
		free(str);
}

void	sclose(int *fd, t_pdata *vars)
{
	if (fd && *fd != -1)
	{
		if (close(*fd) == -1)
		{
			vars->error_msg = ft_strdup("Close failed for fd");
			vars->error_file = ft_itoa(*fd);
			clean_exit(vars, EXIT_FAILURE, 1);
		}
		*fd = -1;
	}
	else if (!fd)
	{
		sclose(&(vars->pip[0]), vars);
		sclose(&(vars->pip[1]), vars);
		sclose(&(vars->input), vars);
		sclose(&(vars->output), vars);
	}
}

void	wait_for_children(t_pdata *vars)
{
	int	status;

	if (vars->child[0] != -1 && waitpid(vars->child[0], NULL, 0) == -1)
	{
		vars->error_msg = ft_strdup("Waitpid failed for 1st command");
		clean_exit(vars, EXIT_FAILURE, 1);
	}
	if (waitpid(vars->child[1], &status, 0) == -1)
	{
		vars->error_msg = ft_strdup("Waitpid failed for 2nd command");
		clean_exit(vars, EXIT_FAILURE, 1);
	}
	if (WIFEXITED(status))
		clean_exit(vars, WEXITSTATUS(status), 0);
}
