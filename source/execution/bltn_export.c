/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:10:09 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 14:02:58 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_print(t_arr *env)
{
	int		i;
	char	*str;

	i = 0;
	while (i < env->size)
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr((char *)env->arr[i], '=') != NULL)
		{
			str = (char *)env->arr[i];
			while (*str != '=')
				ft_putchar_fd(*str++, 1);
			ft_putchar_fd(*str++, 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(str, 1);
			ft_putendl_fd("\"", 1);
		}
		else
		{
			str = (char *)env->arr[i];
			ft_putendl_fd(str, 1);
		}
		i++;
	}
}

int	bltn_export(t_arr *args, t_shell *sh)
{
	int	i;

	if (args->size == 1)
		export_print(sh->env);
	i = 1;
	while (i < args->size)
	{
		if (!env_entry_update(sh->env, (char *)args->arr[i]))
		{
			cmd_perror(ER_EXP, (char *)args->arr[i], ER_IDENT);
			sh->status = 1;
		}
		i++;
	}
	return (1);
}
