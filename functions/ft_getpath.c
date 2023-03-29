/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamounib <mamounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:57:12 by mamounib          #+#    #+#             */
/*   Updated: 2023/03/26 10:15:44 by mamounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../program/main.h"

char	*ft_getpath(char *cmd, char **env)
{
	char	**paths;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (cmd);
		return (NULL);
	}
	path = ft_getenv(env);
	paths = NULL;
	if (path != NULL)
		paths = ft_split(path + 5, ':');
	else
		exit(1);
	while (*paths)
	{
		path = NULL;
		path = ft_strjoin(*paths, "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK | X_OK))
			return (path);
		paths++;
	}
	return (NULL);
}
