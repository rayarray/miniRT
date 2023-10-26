/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/10/26 17:45:54 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	hitSphere(const t_vec center, double radius, const t_ray ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	// vec3 oc = r.origin() - center;
    // auto a = dot(r.direction(), r.direction());
    // auto b = 2.0 * dot(oc, r.direction());
    // auto c = dot(oc, oc) - radius*radius;
    // auto discriminant = b*b - 4*a*c;
    // return (discriminant >= 0);
	oc = vecSub(ray.origin, center);
	a = vecDot(ray.destination, ray.destination);
	b = 2.0 * vecDot(oc, ray.destination);
	c = vecDot(oc, oc) - radius * radius;
	discriminant = b * b - (4 * a * c);
	return (discriminant >= 0);
}
