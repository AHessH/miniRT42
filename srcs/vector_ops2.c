/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:57:23 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:08:25 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	v_cross(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

float	v_len(t_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	check_normal(t_vec *vec, t_scene *scene)
{
	if (vec->x < -1.0f || vec->y < -1.0f || vec->z < -1.0f
		|| vec->x > 1.0f || vec->y > 1.0f || vec->z > 1.0f)
		error_exit("Wrong normal vectors\n", scene);
}

t_vec	v_proj(t_vec v1, t_vec v2)
{
	float	d12;
	float	d22;

	d12 = v_dot(v1, v2);
	d22 = v_dot(v2, v2);
	return (v_mult(v2, d12 / d22));
}
