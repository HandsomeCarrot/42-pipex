/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/18 19:31:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
