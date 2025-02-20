/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:36:38 by vpoka             #+#    #+#             */
/*   Updated: 2025/02/20 18:27:17 by vpoka            ###   ########.fr       */
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

/**
 * Resolves full path to command executable
 * Checks if command contains path, otherwise searches PATH directories
 * @param cmd_array - command array containing command name
 * @param envp - array of environment variables
 * @return full path to executable if found, NULL otherwise
 */
static char	*resolve_command_path(char **cmd_array, char **envp)
{
	char	**path_dirs;
	char	*result;

	if (ft_strchr(cmd_array[0], '/') && access(cmd_array[0], F_OK) == 0)
		return (ft_strdup(cmd_array[0]));
	path_dirs = extract_path_directories(envp);
	if (!path_dirs)
		return (NULL);
	result = find_executable_path(path_dirs, cmd_array);
	free_string_array(path_dirs);
	return (result);
}

/**
 * Processes command by splitting it and resolving executable path
 * @param data - pipex structure containing command data
 * @param cmd - command string to process
 * @param envp - array of environment variables
 */
void	process_command(t_pipex *data, char *cmd, int is_last_command)
{
	if (!data->envp)
	{
		data->error_msg = ft_strdup("Missing enviroment variable");
		exit_program(data, EXIT_FAILURE, 0);
	}
	if (data->cmd_array)
		free_string_array(data->cmd_array);
	data->cmd_array = ft_split(cmd, ' ');
	if (!data->cmd_array[0])
	{
		if (!is_last_command)
			data->error_msg = ft_strdup("The first command is empty");
		else
			data->error_msg = ft_strdup("The second command is empty");
		exit_program(data, EXIT_FAILURE, 0);
	}
	if (data->cmd_path)
		free(data->cmd_path);
	data->cmd_path = resolve_command_path(data->cmd_array, data->envp);
	if (!data->cmd_path)
		data->cmd_path = ft_strdup(data->cmd_array[0]);
}
