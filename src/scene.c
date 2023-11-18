/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:22 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/18 22:23:38 by tsankola         ###   ########.fr       */
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

struct s_scene	*new_scene(void)
{
	struct s_scene	*scene;

	scene = malloc(sizeof(struct s_scene));
	if (scene != NULL)
	{
		scene->ambient = NULL;
		scene->camera = NULL;
		scene->lights = NULL;
		scene->shapes = NULL;
	}
	return (scene);
}

void	scene_dtor(struct s_scene **scene)
{
	if (scene && *scene)
	{
		free((*scene)->ambient);
		free((*scene)->camera);
		light_dtor(&(*scene)->lights);
		shape_list_clear(&(*scene)->shapes);
		free(*scene);
		*scene = NULL;
	}
}
