/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:00:37 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 14:54:35 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Frees an allocated string array. Returns *array which should be NULL
char	**free_strarray(char ***array)
{
	char	**i;

	if (!array || !*array)
		return (NULL);
	i = *array;
	while (i && *i != NULL)
		free(*(i++));
	free(*array);
	*array = NULL;
	return (*array);
}
