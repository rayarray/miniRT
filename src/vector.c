/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:32:10 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/14 15:31:17 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // debug thingy
#include "vector.h"

t_vec	vecInit(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	vecScalar(double i)
{
	return (vecInit(i, i, i));
}

t_vec	vecAdd(t_vec v1, t_vec v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	vecSub(t_vec v1, t_vec v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec	vecMul(t_vec v1, double t)
{
	v1.x *= t;
	v1.y *= t;
	v1.z *= t;
	return (v1);
}

t_vec	vecDiv(t_vec v1, double t)
{
	v1.x /= t;
	v1.y /= t;
	v1.z /= t;
	return (v1);
}

double	vecDot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vecCross(t_vec v1, t_vec v2)
{
	return (vecInit(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x));
}

double	vecLengthSquared(t_vec v1)
{
	return ((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

double	vecLength(t_vec v1)
{
	return (sqrt(vecLengthSquared(v1)));
}

t_vec	unitVector(t_vec v1)
{
	double	len;

	len = vecLength(v1);
	v1.x /= len;
	v1.y /= len;
	v1.z /= len;
	return (v1);
}

// debug thingy
void	vecPrint(char *name, t_vec v, int newline)
{
	if (newline)
		printf(" %s x%f y%f z%f\n", name, v.x, v.y, v.z);
	else
		printf(" %s x%f y%f z%f ", name, v.x, v.y, v.z);
}
