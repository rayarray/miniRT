/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:56:36 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 17:46:10 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "light.h"
#include "rt_validations.h"

int	light_ctor(struct s_light *l, t_vec pos, double brightness, t_color color)
{
	if (!is_ratio(brightness))
		return (1);
	l->brightness = brightness;
	l->pos = pos;
	l->color = color;
	return (0);
}

void	light_dtor(struct s_light *l)
{	// Placeholder code, not sure of usage yet
	struct s_light	*next;

	if (l == NULL)
		return ;
	free(l);
}
