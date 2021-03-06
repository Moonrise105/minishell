/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olydden <olydden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:15:56 by olydden           #+#    #+#             */
/*   Updated: 2021/03/06 16:20:42 by olydden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

void	dict_set(t_list *dict, char *key, char *value);
t_list	*dict_del(t_list *dict, char *key);
t_list	*dict_create(char **array, char key);
char	**dict_to_arr(t_list *dict);
t_pair	*dict_get(t_list *dict, char *key);
void	dict_free(t_list **dict);
void	free_array_char(char **array);
void	dict_print(t_list *dict, char delim);
void	pair_free(void *pair);

#endif
