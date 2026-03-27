/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:20:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/05/07 15:09:40 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_item;

	if (content == NULL)
		return (NULL);
	lst_item = (t_list *)malloc(sizeof(t_list));
	if (lst_item == NULL)
		return (NULL);
	lst_item->content = content;
	lst_item->next = NULL;
	return (lst_item);
}
