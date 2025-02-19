/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 14:27:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pdata	vars;

	prep_variables(&vars);
	if (argc != 5)
	{
		vars.error_msg = ft_strdup("Exactly 4 arguments needed");
		clean_exit(&vars, EXIT_FAILURE, 0);
	}
	set_cmd_vars(&vars, argv[2], envp);
	if (pipe(vars.pip) == -1)
	{
		vars.error_msg = ft_strdup("Pipe failed");
		clean_exit(&vars, EXIT_FAILURE, 1);
	}
	open_files(&vars, argv[1], argv[4]);
	vars.child[0] = execute_command(&vars, envp, 0);
	set_cmd_vars(&vars, argv[3], envp);
	vars.child[1] = execute_command(&vars, envp, 1);
	sclose(&(vars.pip[0]), &vars);
	sclose(&(vars.pip[1]), &vars);
	sclose(&(vars.input), &vars);
	sclose(&(vars.output), &vars);
	wait_for_children(&vars);
	clean_exit(&vars, EXIT_SUCCESS, 0);
}
