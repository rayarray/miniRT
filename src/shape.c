/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 18:07:42 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shape.h"
#include "parser.h"
#include "libft.h"

void	_shape_ctor(struct s_shape *me, char **args)
{
	// Not sure what to do here.
	ft_printf("PANIC @ _shape_ctor\n");
	exit(123);
}

void	shape_ctor(struct s_shape *me, char **args)
{
	static const struct s_shape_vtable	vtable =
		{
			&_shape_ctor,
			&shape_dtor
		};

	me->vtptr = &vtable;
	me->vtptr->shape_ctor(me, args);
}

void		shape_dtor(struct s_shape *me)
{
	me->vtptr->shape_dtor(me);
//	free(me);	// Should it be deleted here? or by the caller on their own?
}