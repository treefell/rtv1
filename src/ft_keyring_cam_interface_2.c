/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyring_cam_interface_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:04:09 by mgras             #+#    #+#             */
/*   Updated: 2016/02/17 17:06:25 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include "mlx.h"
#include "key_define.h"

void	spawn_cam_menu(t_env *e)
{
	t_color		c;
	t_vector	v;

	spawn_cam_pos_controls(c, v, e);
	spawn_cam_dir_controls(c, v, e);
	e->key.mode = 6;
	mlx_put_image_to_window(e->mlx_init.mlx, e->mlx_init.win,
							e->key.interface.img.img_ptr, 0, 0);
}

char	*ft_print_pending_campos_modif2(t_env *e)
{
	char	*cam;
	char	*tmp;
	char	*swp;

	tmp = ft_strdup("Camera Position pending Modifications : x += ");
	swp = ft_itoa(e->key.cam_inc.pos.x);
	cam = ft_strjoin(tmp, swp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	tmp = ft_strdup(" y += ");
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	tmp = ft_itoa(e->key.cam_inc.pos.y);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	return (cam);
}

void	ft_print_pending_campos_modif(t_env *e)
{
	char	*cam;
	char	*tmp;
	char	*swp;

	cam = ft_print_pending_campos_modif2(e);
	tmp = ft_strdup(" z += ");
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	tmp = ft_itoa(e->key.cam_inc.pos.z);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	mlx_string_put(e->mlx_init.mlx, e->mlx_init.win, INTER_W + 10, INTER_H / 4, 0x0, cam);
	ft_strdel(&cam);
}

char	*ft_print_pending_camdir_modif2(t_env *e)
{
	char	*cam;
	char	*tmp;
	char	*swp;

	tmp = ft_strdup("Camera Direction pending Modifications : x += ");
	swp = ft_itoa(e->key.cam_inc.dir.x);
	cam = ft_strjoin(tmp, swp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	tmp = ft_strdup(" y += ");
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	tmp = ft_itoa(e->key.cam_inc.dir.y);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	return (cam);
}

void	ft_print_pending_camdir_modif(t_env *e)
{
	char	*cam;
	char	*tmp;
	char	*swp;

	cam = ft_print_pending_camdir_modif2(e);
	tmp = ft_strdup(" z += ");
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	swp = ft_strdup(cam);
	ft_strdel(&cam);
	tmp = ft_itoa(e->key.cam_inc.dir.z);
	cam = ft_strjoin(swp, tmp);
	ft_strdel(&tmp);
	ft_strdel(&swp);
	mlx_string_put(e->mlx_init.mlx, e->mlx_init.win, INTER_W + 10, INTER_H * (3. / 4.), 0x0, cam);
	ft_strdel(&cam);
}