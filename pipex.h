/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 14:01:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

//----------struct----------//

typedef struct s_pdata
{
	char	**cmd_array;
	char	*cmd_path;
	char	*error_file;
	char	*error_msg;
	int		input;
	int		output;
	int		pip[2];
	pid_t	child[2];
}			t_pdata;

//----------pipex.c----------//

int			main(int argc, char **argv, char **envp);

//----------check_cmd.c----------//

void		set_cmd_vars(t_pdata *vars, char *cmd, char **envp);

//----------exec_cmds.c----------//

pid_t		execute_command(t_pdata *vars, char **envp, int last);

//----------utils.c----------//

void		prep_variables(t_pdata *vars);
void		free_dbl_str(char **str);
void		sclose(int *fd, t_pdata *vars);
void		wait_for_children(t_pdata *vars);

//----------exit.c----------//

void		print_error(t_pdata *vars, int error);
void		clean_exit(t_pdata *vars, int exit_status, int error);

#endif