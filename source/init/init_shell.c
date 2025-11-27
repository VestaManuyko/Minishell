/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 00:23:58 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/27 13:01:40 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	setpwd(t_arr *env)
{
	char *tmp;
	char *pwd;
	
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	if (pwd == NULL)
		return (0);
	free(tmp);
	if (!env_entry_update(env, pwd))
		return (free(pwd), 0);
	return (free(pwd), 1);
}

static int	ismax999(char *val, char **newval)
{
	int i;
	int nbr;

	*newval = NULL;
	if (val == NULL)
		return (0);
	i = 0;
	while (val[i] && i < 3)
	{
		if (!ft_isdigit(val[i]))
			return (0) ;
		i++;
	}
	if (val[i] != '\0')
		return (0);
	nbr = ft_atoi(val);
	nbr++;
	*newval = ft_itoa(nbr);
	return (1);
}

static int	setshlvl(t_arr *env, int id)
{
	char	*val;
	char	*newval;
	
	if (!env_getvalue((char **)env->arr, &val, id))
		return (0);
	if (val == NULL || !ismax999(val, &newval))
	{
		if (!env_entry_update(env, "SHLVL=1"))
			return (free(val), 0);
	}
	else
	{
		free(val);
		val = ft_strjoin("SHLVL=", newval);
		free(newval);
		if (val == NULL)
			return (0);
		if (!env_entry_update(env, val))
			return (free(val), 0);
		free(val);
	}
	return (1);
}

static int	minimalsetup(t_shell *sh)
{
	int shlvl;
	
	if (!setpwd(sh->env))
		return (0);
	shlvl = env_getid((char **)sh->env->arr, "SHLVL");
	if (shlvl == -1)
	{
		if (!env_entry_update(sh->env, "SHLVL=1"))
			return (0);
	}
	else if (!setshlvl(sh->env, shlvl))
		return (0);	
	return (1);
}

/*
 * Initialisation of the t_shell struct;
 * RETURN:
 * 0 on failure, 1 on success;
 */
int	init_shell(t_shell *shell, char **env)
{
	shell->env = tar_init(env, free);
	if (!shell->env)
		return (0);
	if (!minimalsetup(shell))
		return (tar_free(shell->env), 0);
	init_bltn_list(shell->bltn);
	shell->cmd_line = NULL;
	shell->count = 0;
	shell->items = NULL;
	shell->pipes = NULL;
	shell->status = 0;
	return (1);
}
