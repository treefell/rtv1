/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:45:01 by chuang            #+#    #+#             */
/*   Updated: 2016/02/16 20:37:15 by mguillon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** plus la specular est grande moins la tache est grande
*/
#define SPECULAR 100

float	specular_light(t_light light, t_object item, t_vector inter, t_env *e)
{
	t_vector	shine;
	t_vector	light_ray;
	t_vector	normal;
	float		spec;

	light_ray = sub_vector(light.pos, add_vector(inter, e->cam.pos));
	normal = calc_normal(e->cam.pos, item, inter);
	shine = mult_vector(normal, (2.0f * dotpro_vector(light_ray, normal)));
	shine = sub_vector(light_ray, shine);
	spec = dotpro_vector(inter, shine);
	if (spec > 0)
	{
		spec = dotpro_vector(normal, shine) / norm_vector(shine);
		spec = powf(spec, SPECULAR) * item.shine;
	}
	if (spec > 2000000)
		spec = 2000000;
	if (spec < 0)
		spec = 0;
	return (spec);
}