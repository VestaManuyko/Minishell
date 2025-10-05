/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:54:10 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/01 12:54:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    int i =0;
    int status = 0;

    while (av[1][i])
    {
        status = str_isquoted(av[1][i]);
        printf("%c : %2d : %c\n", av[1][i], status, (char)status);
        i++;
    }
    return (0);
}
