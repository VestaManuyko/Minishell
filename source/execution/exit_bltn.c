/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:17:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/28 09:50:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_boundaries(char *nbr, int sign)
{
	const char	*intmax = "9223372036854775807";
	int			i;

	i = 0;
	while (i < 19)
	{
		if (nbr[i] == intmax[i])
			i++;
		else
			break ;
	}
	if (sign == -1 && i == 18)
		return (nbr[i] <= intmax[i] + (sign == -1));
	return (nbr[i - (i == 19)] <= intmax[i - (i == 19)]);
}

static int	get_number(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			break ;
		i++;
	}
	s = s + i;
	while (*s && ft_strchr(MS_BLANKS, *s))
		s++;
	if (*s == '\0')
		return (i);
	return (100);
}

static int	legit_signedlongint(char *s)
{
	int	i;
	int	sign;

	sign = 1;
	if (!s || !s[0])
		return (0);
	while (ft_strchr(MS_BLANKS, *s))
		s++;
	if (*s && (*s == '+' || *s == '-'))
	{
		sign = 1 - (2 * (*s == '-'));
		s++;
	}
	while (*s == '0')
		s++;
	i = get_number(s);
	if (i == 19)
		return (check_boundaries(s, sign));
	return (i < 19);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	char	*str;

	if (g_return == 130)
		return (0);
	printf("exit\n");
	if (args->size > 2)
		return (cmd_perror(ER_MINI, "exit", "too many arguments"), 0);
	if (args->size == 1)
		clean_exit(0, sh, sh->status);
	str = (char *)args->arr[1];
	if (!legit_signedlongint(str))
	{
		cmd_perror(ER_EXIT, str, "numeric argument required");
		clean_exit(0, sh, 2);
	}
	return (clean_exit(0, sh, ft_atoi(str)), 1);
}
