/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:36:06 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/08 21:59:51 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "element.h"
#include "parser.h"
#include "libft.h"

void	_elem_ctor(struct s_elem *me, char **args)
{
	// Not sure what to do here.
	ft_printf("PANIC @ _elem_ctor\n");
	exit(123);
}

void	elem_ctor(struct s_elem *me, char **args)
{
	static const struct s_elem_vtable	vtable =
		{
			&_elem_ctor,
			&elem_dtor
		};

	me->vtptr = &vtable;
	me->vtptr->elem_ctor(me, args);
}

void		elem_dtor(struct s_elem *me)
{
	me->vtptr->elem_dtor(me);
//	free(me);	// Should it be deleted here? or by the caller on their own?
}