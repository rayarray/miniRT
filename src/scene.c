/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/17 20:17:24 by tsankola         ###   ########.fr       */
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
	if (discriminant >= 0)
		return (1);
	else
		return (0);
}

int	scene_ator(struct s_scene **scene, int lightcount, int shapecount)
{
	*scene = malloc(sizeof(struct s_scene) * 1);
	if (*scene == NULL)
		return (1);
	(*scene)->lights = ft_calloc(sizeof(struct s_light *), (lightcount + 1));
	if ((*scene)->lights == NULL)
		return (1);
	(*scene)->shapes = ft_calloc(sizeof(struct s_shape *), (shapecount + 1));
	if ((*scene)->shapes == NULL)
		return (1);
	return (0);
}

void	scene_dtor(struct s_scene **scene)
{
	struct s_light	*lptr;
	struct s_shape	*sptr;

	lptr = *(*scene)->lights;
	while (lptr != NULL)
	{
		light_dtor(lptr);
		free(lptr++);
	}
	free((*scene)->lights);
	(*scene)->lights = NULL;
	sptr = *(*scene)->shapes;
	while (sptr != NULL)
	{
		shape_dtor(sptr);
		free(sptr++);
	}
	free((*scene)->shapes);
	(*scene)->shapes = NULL;
	free(*scene);
	*scene = NULL;
}
