/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:28:09 by tsankola          #+#    #+#             */
/*   Updated: 2024/01/04 15:25:38 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shape_cone.h"
#include "rt_validations.h"
#include "rt_typedef.h"
#include "shading.h"

int	cone_ctor(struct s_cone *this, t_vec orientation[2],
	double dimensions[2], t_color color)
{
	static const struct s_shape_vtable	vtable = {
		(void (*)(struct s_shape *))cone_dtor,
		(double (*)(struct s_shape *, t_ray))cone_intersect_distance,
		(t_color (*)(struct s_shape *, struct s_scene *, t_ray, int))
		cone_intersect_color
	};

	shape_ctor(&this->base, e_CONE, orientation[e_CONE_LOCATION], color);
	this->base.vtptr = &vtable;
	if (!is_direction_vector(orientation[e_CONE_AXIS])
		|| fleq(dimensions[e_CONE_HEIGHT], 0)	// Perhaps this could be negative? TODO: Test if feasible
		|| fleq(dimensions[e_CONE_DIAMETER], 0))
		return (1);
	this->diameter = dimensions[e_CONE_DIAMETER];
	this->height = dimensions[e_CONE_HEIGHT];
	this->axis = vec_normalize(orientation[e_CONE_AXIS]);
	this->angle = atan2(this->diameter / 2, this->height);
	this->vertex = vec_add(this->base.loc, vec_scal_mul(this->axis, this->height));
	printf("Cone base position %f %f %f Vertex position %f %f %f\n", this->base.loc.x, this->base.loc.y, this->base.loc.z, this->vertex.x, this->vertex.y, this->vertex.z);
	printf("diameter %f height %f\n", this->diameter, this->height);
	printf("actual height %f\n", vec_length(vec_sub(this->vertex, this->base.loc)));
	getchar();
	return (0);
}

void	cone_dtor(struct s_cone *this)
{
	_shape_base_dtor(&this->base);
}

t_cone_ray_position	get_ray_position(struct s_cone *cone, t_ray ray)
{
	double	angle_between_ray_and_vertex;
	static int		printcount = 0;
	
	angle_between_ray_and_vertex = acos(dot_product(vec_normalize(vec_sub(ray.loc, cone->vertex)), cone->axis));
	if (flessthan(angle_between_ray_and_vertex, cone->angle))
	{
		if (printcount++ == 0){
			printf("angle %f angle_cam_ver %f ", cone->angle, angle_between_ray_and_vertex);
			printf("over cone\n");
		}
		return (e_OVER_CONE);
	}
	angle_between_ray_and_vertex = acos(dot_product(vec_normalize(vec_sub(ray.loc, cone->vertex)), vec_neg(cone->axis)));
	if (flessthan(angle_between_ray_and_vertex, cone->angle))
	{
		if (flessthan(cos(cone->angle) / vec_length(vec_sub(cone->vertex, ray.loc)), cone->height))
		{
			if (printcount++ == 0){
				printf("%f\n", cos(cone->angle) / vec_length(vec_sub(cone->vertex, ray.loc)));
				printf("angle %f angle_cam_ver %f ", cone->angle, angle_between_ray_and_vertex);
				printf("inside cone\n");
			}
			return (e_INSIDE_CONE);
		}
		if (printcount++ == 0){
			printf("%f\n", cos(cone->angle) / vec_length(vec_sub(cone->vertex, ray.loc)));
			printf("angle %f angle_cam_ver %f ", cone->angle, angle_between_ray_and_vertex);
			printf("under cone\n");
		}
		return (e_UNDER_CONE);
	}
	else
	{
		if (printcount++ == 0){
			printf("angle %f angle_cam_ver %f ", cone->angle, angle_between_ray_and_vertex);
			printf("beside cone\n");
		}
		return (e_BESIDE_CONE);
	}
}

double	base_intersection(struct s_cone *cone, t_ray ray)
{
	double	distance;
	double	denom_base;
	t_vec	impact;

	denom_base = dot_product(cone->axis, ray.dir);	// Should this be adjusted by origins of cone and ray? Axis might need to be negated
	if (feq(denom_base, 0))
		return (INFINITY);
	distance = dot_product(vec_sub(cone->base.loc, ray.loc), cone->axis)
		/ denom_base;
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, distance));
	if (flessthan(distance, 0) || fgreaterthan(vec_distance(impact, cone->base.loc), cone->diameter / 2))
		return (INFINITY);
	return (distance);
}

// https://davidjcobb.github.io/articles/ray-cone-intersection
double	cone_intersect_distance(struct s_cone *this, t_ray ray)
{
 	double	cq;	// cone ratio squared: (radius / height) ^ 2
	double	terms[3];
	double	distance;
	t_vec	rl;			// vector from ray origin to vertex
	double	intersects[2];
	int		result_count;

	t_vec ca = vec_neg(this->axis);

	cq = pow(this->diameter / 2, 2) / pow(this->height, 2);
	rl = vec_sub(ray.loc, this->vertex);
	terms[0] = dot_product(ray.dir, ray.dir) - (cq + 1) * pow(dot_product(ray.dir, ca), 2);
	terms[1] = 2 * ((dot_product(rl, ray.dir) - (cq + 1) * dot_product(rl, ca) * dot_product(ray.dir, ca)));
	terms[2] = dot_product(rl, rl) - (cq + 1) * pow(dot_product(rl, ca), 2);
	result_count = quadratic_solver(terms[0], terms[1], terms[2], intersects);

	if (result_count == 0)	// TODO fix? Should not return always because if inside cone, we might be looking downwards and need to test the base intersection
		return (INFINITY);	// Although even in that case there should be at least one (negative) result.

	t_cone_ray_position ray_position = get_ray_position(this, ray);

	if (ray_position == e_UNDER_CONE)	// Under cone. Only the bottom can be visible.
		return (base_intersection(this, ray));
	else if (ray_position == e_OVER_CONE)	// Over cone. Only the side or tip can be visible.
	{	// TODO tip
		if (result_count == 2 && fgreaterthan(intersects[1], 0))
			distance = intersects[1];
		else
			return (INFINITY);
	}
	else if (ray_position == e_BESIDE_CONE)	// Beside cone. The side can be visible and the bottom can be visible.
	{
//		printf("intersects %f %f\n", intersects[0], intersects[1]);
		if (fgreaterthan(intersects[0], 0)){
//			printf("dist 0\n");
			distance = intersects[0];
		}
		else if (result_count == 2 && fgreaterthan(intersects[1], 0))
		{
//			printf("dist 1\n");
			distance = intersects[1];
		}
		else
			return (INFINITY);
	}
	else if (ray_position == e_INSIDE_CONE) // Inside cone. If no positive intersections, need to check bottom
	{	// TODO testing
//		printf("0 %f 1 %f results %d\n", intersects[0], intersects[1], result_count);
		if (fgreaterthan(intersects[0], 0))
			distance = intersects[0];
		else if (result_count == 2 && fgreaterthan(intersects[1], 0))
			distance = intersects[1];
		else
			return (base_intersection(this, ray));
//		if (flessthan(base_intersection(this, ray), distance))
//		{
//			printf("%f %f %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
//			printf("%f %f %f\n", this->base.loc.x, this->base.loc.y, this->base.loc.z);
//			printf("Not here %f\n", base_intersection(this, ray));
//			getchar();
//			return (base_intersection(this, ray));
//		}
//		else
//			return (distance);
	}

	t_vec hit_point = vec_add(ray.loc, vec_scal_mul(ray.dir, distance));
	t_vec vertex_to_hit = vec_sub(this->vertex, hit_point);

//	double hit_height = cos(this->angle) * vec_length(vertex_to_hit);
	double hit_height = dot_product(vertex_to_hit, this->axis);

/* 	printf("vertex %f %f %f\n", this->vertex.x, this->vertex.y, this->vertex.z);
	printf("hit point %f %f %f\n", hit_point.x, hit_point.y, hit_point.z);
	printf("hit height %f\n", hit_height);
	printf("vector length %f\n", vec_length(vertex_to_hit));
	printf("ray.destination length %f\n", vec_length(ray.destination));
 */	if (fgeq(hit_height, 0) && fleq(hit_height, this->height))
		;
	else if (fgreaterthan(hit_height, this->height)){
//		printf("here? hit_height %f\n", hit_height);
//		getchar();
		return (base_intersection(this, ray));
	}
	else if (flessthan(hit_height, 0))
	{
//		printf("there? hit_height %f\n", hit_height);
//		getchar();
		return (INFINITY);
	}
	return (distance);
}

t_color	cone_intersect_color(struct s_cone *this, struct s_scene *scene,
	t_ray ray, int bounces)
{
	double		dist;
	t_point3	impact;
	t_ray		impact_normal;
	t_vec		normal;

	(void)bounces;
//	return this->base.col;
	dist = cone_intersect_distance(this, ray);
	if (isinf(dist))
		return ((t_color){0, 0, 0, 0xFF});
	impact = vec_add(ray.loc, vec_scal_mul(ray.dir, dist));
//	if (flessthan(impact.y + 1.0, 0))
//		return (t_color){255, 255, 255, 0xFF};
	if (feq(base_intersection(this, ray), dist))
//		feq(dot_product(vec_sub(impact, this->base.loc), this->axis), 0)
//			&& fleq(vec_distance(impact, this->base.loc), this->diameter / 2))
		impact_normal = (t_ray){impact, vec_neg(this->axis)};
	else
	{
//		t_vec impact_to_vertex = vec_sub(this->vertex, impact);
//		normal = vec_normalize(vec_sub(vec_scal_mul(this->axis, 1 / cos(this->angle)),
//						 vec_normalize(impact_to_vertex)));
		t_vec	vertex_to_impact = vec_normalize(vec_sub(impact, this->vertex));
		t_vec	spine_vec = vec_neg(this->axis);
		spine_vec = vec_scal_mul(spine_vec, 1 / cos(this->angle));
		normal = vec_normalize(vec_sub(vertex_to_impact, spine_vec));
		impact_normal = (t_ray){impact, normal};
	}
//	printf("impact %f %f %f, normal %f %f %f\n", impact_normal.origin.x, impact_normal.origin.y, impact_normal.origin.z, impact_normal.destination.x, impact_normal.destination.y, impact_normal.destination.z);
//	getchar();
	if (get_ray_position(this, ray) == e_INSIDE_CONE)
		impact_normal.dir = vec_neg(impact_normal.dir);
	impact_normal.loc = vec_add(impact_normal.loc, 
		vec_scal_mul(impact_normal.dir, 0.00001));
//	printf("impact: %f %f %f normal: %f %f %f\n", impact_normal.origin.x, impact_normal.origin.y, impact_normal.origin.z, impact_normal.destination.x, impact_normal.destination.y, impact_normal.destination.z);
//	if (fgreaterthan(dot_product(ray.destination, impact_normal.destination), 0)) {
//		printf("Naag\n");
//		impact_normal.destination = vec_neg(impact_normal.destination);
//		impact_normal.destination = vec_scal_mul(impact_normal.destination, 1.00001);
//	}
	return (apply_shading(scene, this->base.col, impact_normal, ray));
}
