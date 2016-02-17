/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 17:35:19 by chuang            #+#    #+#             */
/*   Updated: 2016/02/17 17:00:49 by chuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
#include <stdlib.h>

#define BLUR 5

int			check_shadow(t_light light, t_vector inter_ray, t_env *e)
{
	float		test;
	t_vector	inter_pos;
	t_vector	light_ray;
	t_object	*tmp;

	inter_pos = add_vector(inter_ray, e->cam.pos);
	light_ray = sub_vector(light.pos, inter_pos);
	tmp = e->scene->l_obj;
	while (tmp)
	{
		test = 0;
		if (tmp->type == SPHERE)
			test = inter_sphere(inter_pos, unit_vector(light_ray), *tmp);
		else if (tmp->type == PLANE)
			test = inter_plane(inter_pos, unit_vector(light_ray), *tmp);
		else if (tmp->type == CONE)
			test = inter_cone(inter_pos, unit_vector(light_ray), *tmp);
		else if (tmp->type == CYLINDER)
			test = inter_cylinder(inter_pos, unit_vector(light_ray), *tmp);
		tmp = tmp->next;
		if (test > 0.00001 && test < (float)norm_vector(light_ray))
			return (1);
	}
	return (0);
}

t_vector	calc_normal(t_vector pos, t_object item, t_vector inter_ray)
{
	if (item.type == SPHERE)
		return (normal_sphere(pos, item, inter_ray));
	else if (item.type == PLANE)
		return (normal_plane(item, inter_ray));
	else if (item.type == CONE)
		return (normal_cone(pos, item, inter_ray));
	else
		return (normal_cylinder(pos, item, inter_ray));
}

t_color		ft_light(t_light *lights, t_object item, t_vector inter, t_env *e)
{
	t_color		tmp_color;
	float		coef;
	float		spec;

	item.color = item.checkered ? checkered_floor(inter) : item.color;
	item.color = mult_color(item.color, AMBIANT);
	while (lights && !(coef = 0))
	{
		if (!(spec = 0) && !(check_shadow(*lights, inter, e)))
		{
			coef = diffuse_light(*lights, item, inter, e);
			if (item.shine > 0 && coef)
				spec = specular_light(*lights, item, inter, e);
						tmp_color = mult_color(lights->color, (coef + spec));
			item.color = add_color(item.color, tmp_color);
		}
		if (item.reflect > 0)
		{
			tmp_color = reflection(item, inter, e);
			item.color = mult_color(add_color(item.color, tmp_color), 0.5);
		}
		lights = lights->next;
	}
	return (check_color(item.color));
}

void		init_lights(t_env *e)
{
	t_light		*test;

	test = malloc(sizeof(t_light));
	test->pos = (t_vector){5, 0, 0};
	test->dir = (t_vector){0, 1, 0};
	test->color = (t_color){255, 255, 255};
	test->intensity = 0.5;
	test->next = NULL;
	e->lights = malloc(sizeof(t_light));
	e->lights->pos = (t_vector){0, 0, 0};
	e->lights->dir = (t_vector){0, 1, 0};
	e->lights->color = (t_color){255, 255, 255};
	e->lights->intensity = 0.5;
	e->lights->next = test;
}
