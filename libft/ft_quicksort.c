/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:34:31 by fpaglia           #+#    #+#             */
/*   Updated: 2025/06/19 07:34:34 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_two_elements(int *start, int *end)
{
	if (start >= end)
		return (1);
	if (end - start == 1)
	{
		if (*end < *start)
			ft_swap(end, start);
		return (1);
	}
	return (0);
}

static void	do_sort(int **left, int **right, int pivot)
{
	while (**left < pivot)
		(*left)++;
	while (**right > pivot)
		(*right)--;
	if (*left <= *right)
	{
		ft_swap(*left, *right);
		(*left)++;
		(*right)--;
	}
}

void	ft_quicksort(int *start, int *end)
{
	int	pivot;
	int	*left;
	int	*right;

	if (is_two_elements(start, end))
		return ;
	pivot = *(start + (end - start) / 2);
	left = start;
	right = end;
	while (left <= right)
		do_sort(&left, &right, pivot);
	if (start < right)
		ft_quicksort(start, right);
	if (left < end)
		ft_quicksort(left, end);
}
