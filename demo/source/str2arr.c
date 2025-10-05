/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:10:22 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/03 12:49:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av)
{
	char test[] = "ls '-al s' | grep you | \"wc -l | wc -w\" "; 
	if (ac != 3)
	{
		printf("Error:\n\tstr2arr.out {separator} {eval_quote: 0 | 1} \n");
		return (1);
	}
	char **arr = arr_split_by_c(test, av[1][0], atoi(av[2]));
	if (arr == NULL)
		return (1);
	arr_print(arr);
	arr_free(arr);
	return (0);
}
