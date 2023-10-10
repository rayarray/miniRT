/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:07:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/10/10 18:14:34 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"

t_ambient_lighting	*new_ambient_lighting(const char* identifier)
{
	t_ambient_lighting	*al;

	al = malloc(sizeof(t_ambient_lighting));
	if (al == NULL)
		return (NULL);
	al->identifier = ft_strdup(identifier);
	if (al->identifier == NULL){
		free(al);
		return (NULL);
	}
	al->color[RED] = 0;
	al->color[GREEN] = 0;
	al->color[BLUE] = 0;
	al->lighting_ratio = 0;
	return (al);
}

void	del_ambient_lighting(t_ambient_lighting **al)
{
	free((*al)->identifier);
	free(*al);
	*al = NULL;
}
