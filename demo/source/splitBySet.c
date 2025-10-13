/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitBySet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:10:22 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 11:46:01 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av)
{
	char test[] = "ls '-al s'\t | grep\t you\n  \a\b\v\f | \"wc -l | wc -w\" "; 
	if (ac != 2)
	{
		printf("Error:\n\tstr2arr.out {eval_quote: 0 | 1} \n");
		return (1);
	}
	char **arr = str_split_by_set(test, " \a\b\t\n\v\f\r", atoi(av[1]));
	if (arr == NULL)
		return (1);
	arr_print(arr);
	arr_free(arr);
	return (0);
}
