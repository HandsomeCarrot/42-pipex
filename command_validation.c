/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:36:38 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/21 16:05:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Extracts PATH directories from environment variables
 * Searches envp array for PATH variable and splits its value by ':'
 * @param envp - array of environment variables
 * @return array of PATH directories, or NULL if PATH not found
 */
static char	**extract_path_directories(char **envp)
{
	int	pos;

	pos = 0;
	while (envp[pos])
	{
		if (ft_strncmp(envp[pos], "PATH=", 5) == 0)
			return (ft_split((envp[pos]) + 5, ':'));
		pos++;
	}
	return (NULL);
}

/**
 * Builds full command path by joining directory and command
 * @param dir - directory path
 * @param cmd - command name
 * @return full path to command, or NULL on allocation failure
 */
static char	*build_command_path(char *dir, char *cmd)
{
	char	*dir_slash;
	char	*new_cmd;

	dir_slash = ft_strjoin(dir, "/");
	if (!dir_slash)
		return (NULL);
	new_cmd = ft_strjoin(dir_slash, cmd);
	free(dir_slash);
	return (new_cmd);
}

/**
 * Finds executable path by checking each PATH directory
 * @param paths - array of PATH directories to search
 * @param cmd_array - command array containing command name
 * @return full path to executable if found, NULL otherwise
 */
static char	*find_executable_path(char **paths, char **cmd_array)
{
	int		path;
	char	*new_cmd;

	path = 0;
	while (paths[path])
	{
		new_cmd = build_command_path(paths[path], cmd_array[0]);
		if (!new_cmd)
			return (NULL);
		if (access(new_cmd, F_OK) == 0)
			return (new_cmd);
		free(new_cmd);
		path++;
	}
	return (NULL);
}

static char	*resolve_command_path(t_pipex *data, int last)
{
	char	**path_dirs;
	char	*result;

	if (ft_strchr(data->cmd_arrays[last][0], '/'))
	{
		if (access(data->cmd_arrays[last][0], F_OK) == 0)
			return (ft_strdup(data->cmd_arrays[last][0]));
		return (NULL);
	}
	else
	{
		path_dirs = extract_path_directories(data->envp);
		if (!path_dirs)
			return (NULL);
		result = find_executable_path(path_dirs, data->cmd_arrays[last]);
		free_string_array(path_dirs);
		return (result);
	}
}

void	process_command(t_pipex *data, int last)
{
	if (!data->envp)
	{
		data->msg1 = ft_strdup("Missing enviroment variable");
		exit_program(data, EXIT_FAILURE, 0);
	}
	data->cmd_arrays[last] = ft_split(data->argv[2 + last], ' ');
	if (data->cmd_arrays[last])
		data->cmd_paths[last] = resolve_command_path(data, last);
	if (!data->cmd_arrays[last] || !data->cmd_paths[last])
	{
		if (!data->cmd_arrays[last])
			data->msg1 = ft_strdup(" ");
		else
			data->msg1 = ft_strdup(data->cmd_paths[last]);
		data->msg2 = ft_strdup("command not found");
		if (last)
			exit_program(data, 127, 0);
		print_error(data, 0);
	}
}
