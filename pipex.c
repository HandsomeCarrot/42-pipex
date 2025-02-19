/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 13:57:50 by vpoka            ###   ########.fr       */
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
	vars.input = open(argv[1], O_RDONLY);
	if (vars.input == -1)
	{
		vars.error_msg = ft_strdup("Input file");
		vars.error_file = ft_strdup(argv[1]);
		print_error(&vars, 1);
	}
	vars.child[0] = execute_command(&vars, envp, 0);
	vars.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars.output == -1)
	{
		vars.error_msg = ft_strdup("Output file");
		vars.error_file = ft_strdup(argv[4]);
		print_error(&vars, 1);
	}
	set_cmd_vars(&vars, argv[3], envp);
	vars.child[1] = execute_command(&vars, envp, 1);
	sclose(&(vars.pip[0]), &vars);
	sclose(&(vars.pip[1]), &vars);
	sclose(&(vars.input), &vars);
	sclose(&(vars.output), &vars);
	wait_for_child(vars.child[0], &vars, 0);
	wait_for_child(vars.child[1], &vars, 1);
	clean_exit(&vars, EXIT_SUCCESS, 0);
}
