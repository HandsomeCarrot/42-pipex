/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:36:38 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/19 11:24:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path_dirs(char **envp)
{
	int	pos;

	pos = 0;
	while (envp && envp[pos])
	{
		if (ft_strncmp(envp[pos], "PATH=", 5) == 0)
			return (ft_split((envp[pos]) + 5, ':'));
		pos++;
	}
	return (NULL);
}

static char	*assign_new_path(char *dir, char *cmd)
{
	int		cmd_path_len;
	char	*new_cmd;

	if (!dir || !cmd)
		return (NULL);
	cmd_path_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	new_cmd = ft_calloc(cmd_path_len, sizeof(char));
	if (!new_cmd)
		return (NULL);
	ft_strlcat(new_cmd, dir, cmd_path_len);
	ft_strlcat(new_cmd, "/", cmd_path_len);
	if (ft_strlcat(new_cmd, cmd, cmd_path_len) >= (size_t)cmd_path_len)
	{
		free(new_cmd);
		return (NULL);
	}
	return (new_cmd);
}

static char	*find_valid_cmd_path(char **paths, char **cmd_array)
{
	int		path;
	char	*new_cmd;

	if (!paths || !cmd_array || !cmd_array[0])
		return (NULL);
	path = 0;
	while (paths[path])
	{
		new_cmd = assign_new_path(paths[path], cmd_array[0]);
		if (!new_cmd)
			return (NULL);
		if (access(new_cmd, F_OK) == 0)
			return (new_cmd);
		free(new_cmd);
		path++;
	}
	return (NULL);
}

static char	*get_cmd_path(char **cmd_array, char **envp)
{
	char	**path_dirs;
	char	*result;

	if (!cmd_array || !cmd_array[0] || !envp)
		return (NULL);
	if (ft_strchr(cmd_array[0], '/'), access(cmd_array[0], F_OK) == 0)
		return (ft_strdup(cmd_array[0]));
	path_dirs = get_path_dirs(envp);
	if (!path_dirs)
		return (NULL);
	result = find_valid_cmd_path(path_dirs, cmd_array);
	free_dbl_str(path_dirs);
	return (result);
}

void	set_cmd_vars(t_pdata *vars, char *cmd, char **envp)
{
	if (!cmd || !envp)
	{
		vars->error_msg = ft_strdup("Did not get needed variables");
		clean_exit(vars, EXIT_FAILURE, 0);
	}
	if (vars->cmd_array)
		free_dbl_str(vars->cmd_array);
	vars->cmd_array = ft_split(cmd, ' ');
	if (!vars->cmd_array || !vars->cmd_array[0])
	{
		vars->error_msg = ft_strdup("ft_split failed");
		clean_exit(vars, EXIT_FAILURE, 0);
	}
	if (vars->cmd_path)
		free(vars->cmd_path);
	vars->cmd_path = get_cmd_path(vars->cmd_array, envp);
	if (!vars->cmd_path)
		vars->cmd_path = ft_strdup(vars->cmd_array[0]);
}
