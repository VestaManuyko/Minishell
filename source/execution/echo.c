/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:00:41 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/04 18:25:21 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_args(char *arr, char *temp, int i, int flag)
{
	char	*args;
	char	*temp2;

	if (i == 1 || (flag == 1 && i == 2))
		args = ft_strjoin(temp, arr);
	else
	{
		temp2 = ft_strjoin(temp, " ");
		args = ft_strjoin(temp2, arr);
		free(temp2);
	}
	return (args);
}

static char	*get_args(char	**arr, int *flag)
{
	size_t	i;
	char	*temp;
	char	*args;

	i = 1;
	temp = NULL;
	if (!arr[i])
		return (NULL);
	if (!ft_strncmp(arr[i], "-n", 2))
	{
		i++;
		*flag = 1;
	}
	while (arr[i])
	{
		if (!temp)
			temp = ft_strdup("");
		args = join_args(arr[i], temp, i, *flag);
		free (temp);
		if (!args)
			return (NULL);
		temp = args;
		i++;
	}
	return (args);
}

int	bltn_echo(t_arr *args, t_shell *sh)
{
	char	*cmd_args;
	int		flag;

	flag = 0;
	cmd_args = get_args((char **)args->arr, &flag);
	if (!cmd_args)
		return (write(1, "\n", 1), 0);
	if (!flag)
		ft_putendl_fd(cmd_args, 1);
	else
		write(1, cmd_args, ft_strlen(cmd_args));
	return (free(cmd_args), 1);
}
