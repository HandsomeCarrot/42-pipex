/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:53 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/17 20:34:54 by vpoka            ###   ########.fr       */
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
	int		input;
	int		output;
	int		pip[2];
	pid_t	child[2];
}			t_pdata;

//----------pipex.c----------//

void		sclose(int *fd, t_pdata *vars);
void		clean_exit(int error, char *msg, t_pdata *vars, int exit_status);

//----------check_cmd.c----------//

void		set_cmd_vars(t_pdata *vars, char *cmd, char **envp);

//----------exec_cmds.c----------//

pid_t		execute_command(t_pdata *vars, char **envp, int last);

//----------utils.c----------//

void		prep_variables(t_pdata *vars);
void		free_dbl_str(char **str);
void		wait_for_child(pid_t child, t_pdata *vars, int last);

#endif