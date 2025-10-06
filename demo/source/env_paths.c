/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:27:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/06 14:34:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	char **arr;
	t_shell	shell;

	arr = arr_split_by_c(getenv("PATH"), ':', 1);
	arr_print(arr);
}
