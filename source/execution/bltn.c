/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:44:45 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/05 16:44:48 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	bltn_export(t_arr *args, t_shell *sh)
{
	if (!env_entry_update(sh->env, (char *)args->arr[1]))
		return (0);
	return (1);
}

int	bltn_unset(t_arr *args, t_shell *sh)
{
	if (!env_entry_remove(sh->env, (char *)args->arr[1]))
		return (0);
	return (1);
}

int	bltn_env(t_arr *args, t_shell *sh)
{
	(void)args;
	arr_print((char **)sh->env->arr);
	return (1);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	(void)args;
	free_shell(sh);
	printf("exit\n");
	exit(0);
	return (1);
}
