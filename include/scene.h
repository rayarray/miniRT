/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:18:59 by rleskine          #+#    #+#             */
/*   Updated: 2023/11/16 18:20:22 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "shape.h"
# include "vector.h"
# include "camera.h"
# include "ambient_lighting.h"
# include "light.h"

struct s_scene
{
	struct s_camera				camera;
	struct s_ambient_lighting	ambient;
	struct s_light				**lights;	// Array of lights to support multiple lights
	struct s_shape				**shapes;	// Array of shapes
};

int	hitSphere(const t_vec center, double radius, const t_ray ray);

int	scene_ator(struct s_scene **scene, int lightcount, int shapecount);

#endif	/* SCENE_H */