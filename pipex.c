/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:50 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 18:22:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	prep_variables(t_pdata *vars)
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

void	open_files(t_pdata *vars, char *input, char *output)
{
	vars->input = open(input, O_RDONLY);
	if (vars->input == -1)
	{
		vars->error_msg = ft_strdup("Input file");
		vars->error_file = ft_strdup(input);
		print_error(vars, 1);
	}
	vars->output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars->output == -1)
	{
		vars->error_msg = ft_strdup("Output file");
		vars->error_file = ft_strdup(output);
		print_error(vars, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pdata	vars;

	prep_variables(&vars);
	if (argc != 5)
	{
		vars.error_msg = ft_strdup("Exactly 4 arguments needed");
		clean_exit(&vars, EXIT_FAILURE, 0);
	}
	if (pipe(vars.pip) == -1)
	{
		vars.error_msg = ft_strdup("Pipe failed");
		clean_exit(&vars, EXIT_FAILURE, 1);
	}
	open_files(&vars, argv[1], argv[4]);
	set_cmd_vars(&vars, argv[2], envp);
	vars.child[0] = execute_command(&vars, envp, 0);
	set_cmd_vars(&vars, argv[3], envp);
	vars.child[1] = execute_command(&vars, envp, 1);
	sclose(NULL, &vars);
	wait_for_children(&vars);
	clean_exit(&vars, EXIT_SUCCESS, 0);
}
