/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:18:59 by rleskine          #+#    #+#             */
/*   Updated: 2023/12/12 11:55:34 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "libft.h"
# include "shape.h"
# include "vector.h"
# include "camera.h"
# include "ambient_lighting.h"
# include "light.h"

struct s_scene
{
	struct s_camera				*camera;
	struct s_ambient_lighting	*ambient;
	struct s_light				*lights;	// Linked list of lights to support multiple lights. This is a bonus feature
	struct s_shape				*shapes;	// Linked list of shapes
};

// int		hitSphere(const t_vec center, double radius, const t_ray ray);	// DEPRECATED

struct s_scene	*new_scene(void);
void			scene_dtor(struct s_scene **scene);

#endif	/* SCENE_H */