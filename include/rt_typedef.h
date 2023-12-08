/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_typedef.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:45:14 by tsankola          #+#    #+#             */
/*   Updated: 2023/12/08 15:19:49 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPEDEF_H
# define RT_TYPEDEF_H
# include <stdint.h>

// Shapes should be between e_LIGHT and e_NAE
typedef enum e_elem_type
{
	e_AMBIENT_LIGHTING = 0,
	e_CAMERA = 1,
	e_LIGHT = 2,
	e_SPHERE = 3,
	e_PLANE = 4,
	e_CYLINDER = 5,
	e_NAE = 6
}	t_elem_type;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point3;

typedef struct s_point2
{
	double	x;
	double	y;
}	t_point2;

typedef struct s_ray
{
	t_point3	point;
	t_vec		dir;
}	t_ray;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
}	t_pixel;

#endif