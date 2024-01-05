/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:18:59 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/04 19:57:34 by tsankola         ###   ########.fr       */
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
	struct s_light				*lights;
	struct s_shape				*shapes;
};

struct s_scene	*new_scene(void);
void			scene_dtor(struct s_scene **scene);

#endif	/* SCENE_H */