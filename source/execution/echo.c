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

static void	print_cmd_args(int flag, char *cmd_args)
{
	if (!flag)
		printf("%s\n", cmd_args);
	else
		printf("%s", cmd_args);
}

int	bltn_echo(t_arr *args, t_arr *env)
{
	char	*print_str;
	char	*cmd_args;
	int		flag;

	flag = 0;
	cmd_args = get_args((char **)args->arr, &flag);
	if (!cmd_args)
		return (0);
	if (ft_strchr(cmd_args, '$'))
	{
		print_str = str_expand(dollar, env, cmd_args, 0);
		if (!print_str)
			return (free(cmd_args), 0);
		if (!flag)
			printf("%s\n", print_str);
		else
			printf("%s", print_str);
		return (free(print_str), free(cmd_args), 1);
	}
	else
		print_cmd_args(flag, cmd_args);
	return (free(cmd_args), 1);
}
