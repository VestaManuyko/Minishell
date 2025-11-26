/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bltn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:17:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/26 15:53:03 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_boundaries(char *nbr, int sign)
{
	const char	*intmax = "9223372036854775807";
	size_t		i;

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

int	get_number(char *s)
{
	size_t	i;

	i = 0;
	while (*s && s[i])
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

int	legit_signedlongint(char *s)
{
	size_t	i;
	int		sign;

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
	i = get_number(s);
	if (i == 19)
		return (check_boundaries(s, sign));
	return (i < 19);
}

int	bltn_exit(t_arr *args, t_shell *sh)
{
	char	*str;

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
