#include <unistd.h>
#include "../includes/rtv1.h"
#include "../libft/includes/libft.h"

void			input_plane(t_env *e)
{
	t_object	*node;

	node = create_object(e);
	node->type = PLANE;
	position(node);
	normal(node);
	constant(node);
	color_choice(&node->color);
}

void			input_sphere(t_env *e)
{
	t_object	*node;

	node = create_object(e);
	node->type = SPHERE;
	position(node);
	radius(node);
	color_choice(&node->color);
}
void			input_cylinder(t_env *e)
{
	t_object	*node;

	node = create_object(e);
	node->type = CYLINDER;
	position(node);
	radius(node);
	height(node);
	color_choice(&node->color);
}


void			input_cone(t_env *e)
{
	t_object	*node;

	node = create_object(e);
	node->type = CONE;
	position(node);
	radius(node);
	height(node);
	color_choice(&node->color);
}
