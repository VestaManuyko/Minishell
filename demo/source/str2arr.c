/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:10:22 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/14 10:41:31 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
sig_atomic_t volatile g_return;

int main(int ac, char **av)
{
//	char test[] = "ls '-al s'\t | grep\t you\n | \"wc -l | wc -w\" "; 
//	char test[] = "something|with|noDIff";
	if (ac != 4)
	{
		printf("Error:\n\tstr2arr.out {separator} {eval_quote: 0 | 1} {str}\n");
		return (1);
	}
	char **arr = str_split_by_set(av[3], " \a\b\t\n\v\f\r", atoi(av[2]));
	if (arr == NULL)
		return (1);
	arr_print(arr, '\n', 1);
	arr_free(arr);
	return (0);
}
