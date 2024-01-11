/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:56:36 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/11 17:49:08 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_bonus.h"
#include "rt_validations_bonus.h"

int	light_ctor(struct s_light *l, t_vec pos, double brightness, t_color c)
{
	if (!is_ratio(brightness))
		return (1);
	l->brightness = brightness;
	l->loc = pos;
	l->color = c;
	l->next = NULL;
	return (0);
}

void	light_dtor(struct s_light **l)
{
	struct s_light	*this;

	while (*l != NULL)
	{
		this = *l;
		*l = this->next;
		free(this);
	}
}
