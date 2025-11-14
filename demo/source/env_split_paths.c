/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:27:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/14 10:40:24 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* This little demostrator uses the split by set with only one item to demonstrate
 * that it has an identical behavior to the split by char.
 */
int main()
{
	char **arr;

	arr = str_split_by_set(getenv("PATH"), ":", 1);
	arr_print(arr, '\n', 1);
}
