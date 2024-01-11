/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsankola <tsankola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:18:59 by rleskine          #+#    #+#             */
/*   Updated: 2024/01/11 18:01:40 by tsankola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "libft.h"
# include "shape_bonus.h"
# include "vector_bonus.h"
# include "camera_bonus.h"
# include "ambient_lighting_bonus.h"
# include "light_bonus.h"

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