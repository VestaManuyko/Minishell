/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/06 15:57:19 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRINGS_H
# define MS_STRINGS_H

void	arr_free(char **arr);
void	arr_print(char **arr);
t_arr	*env_deepcpy(char **src_env);
int		*env_putone(t_arr *env, char *str);
int		*env_popone(t_arr *env, char *str);
char	*env_getvalue(t_arr *env, char *key);

#endif
