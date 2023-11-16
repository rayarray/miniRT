/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:11:14 by tsankola          #+#    #+#             */
/*   Updated: 2023/11/16 19:04:01 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "scene.h"
#include "elem_sphere.h"

/* 
# Ambient lighting: type identifier | ambient lighting ratio | colors (RGB)
A	0.2	255,255,255
# Camera: type identifier | xyz coordinates | orientation vector | FOV
C	-50.0,0,20	0,0,1	70
# Light: type identifier | xyz coordinates | brightness ratio | colors (RGB)
L	-40.0,50.0,0.0	0.6	10,0,255
# Sphere: type identifier | xyz coordinates | diameter | colors (RGB)
sp	0.0,0.0,20.6	12.6	10,0,255
# Plane: type identifier | xyz coordinates of a point | normal vector | colors (RGB)
pl	0.0,0.0,-10.0	0.0,1.0,0.0	0,0,225
# Cylinder: type identifer | xyz coordinates | vector of axis of cylinder | diameter | height | colors (RGB)
cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
 */

int	create_an_element(struct s_shape **elem, struct s_elem_base *base)
{
	if (base->type == e_SPHERE)
		*elem = malloc(sizeof(struct s_sphere));
/* 	else if (base->type == e_PLANE)
		*elem = malloc(sizeof(struct s_plane));
	else if (base->type == e_CYLINDER)
		*elem = malloc(sizeof(struct s_cylinder)); */
	if (*elem == NULL)
		return (1);
	
		;// sphere etc. constructor here
	return (0);
}

t_elem_count	countbases(const struct s_elem_base *bases, int basecount)
{
	t_elem_count	ret;
	int		i;

	i = -1;
	ret = (t_elem_count){0, 0, 0, 0, 0};
	while (++i < basecount)
	{
		if (bases[i].type == e_LIGHT)
			ret.lightcount++;
		else if (bases[i].type == e_CAMERA)
			ret.cameracount++;
		else if (bases[i].type == e_AMBIENT_LIGHTING)
			ret.ambientcount++;
		else if (bases[i].type != e_NAE)
			ret.shapecount++;
		if (bases[i].type != e_NAE)
			ret.elemcount++;
	}
	if (ret.elemcount == basecount)
		return (ret);
	return ((t_elem_count){-1,-1,-1,-1,-1});	// Additional check. Shouldn't get here ever.
}

struct s_scene	*create_scene(const struct s_elem_base *bases, t_elem_count count)
{
	struct s_scene	*scene;
	int				bases_i;
	int				elem_i;
	int				err;

	// INIT Move to own function
	// scene = malloc(sizeof(struct s_scene) * 1);
	// if (scene == NULL)
	// 	return (NULL);
	// scene->lights = NULL;
	// scene->shapes = ft_calloc(sizeof(struct s_shape *), (basecount + 1));	// allocates a few lines more than needed because camera, lights and ambient light are their own fields but that is of no concern
	// if (scene->shapes == NULL)
	// 	return (NULL);
	// INIT
	bases_i = -1;
	elem_i = -1;
	err = scene_ator(&scene, count.lightcount, count.shapecount);
	while (err == 0 && ++bases_i < basecount)
	{
		if (bases[bases_i].type == e_AMBIENT_LIGHTING)
			err = bases[bases_i].ctor(&scene->ambient, bases[bases_i].args);
		else if (bases[bases_i].type == e_CAMERA)
			err = bases[bases_i].ctor(&scene->camera, bases[bases_i].args);
		else if (bases[bases_i].type == e_LIGHT)
			err = bases[bases_i].ctor(&scene->light, bases[bases_i].args);
		else if (bases[bases_i].type != e_NAE)
			err = bases[bases_i].ctor(&scene->shapes[++elem_i], bases[bases_i].args);
		else
			printf("Bad element type index %d\n", bases_i);	// Shouldn't get here
	}
	if (err == 0)
		return (scene);
	return (NULL);
}
