/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:33:34 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:08:10 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	v_norm(t_vec v)
{
	t_vec	norm;
	float	len;

	len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	norm.x = v.x / len;
	norm.y = v.y / len;
	norm.z = v.z / len;
	return (norm);
}

float	v_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	v_mult(t_vec v, float m)
{
	t_vec res;

	res.x = m * v.x;
	res.y = m * v.y;
	res.z = m * v.z;
	return (res);
}

t_vec	v_sub(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec	v_add(t_vec v1, t_vec v2)
{
	t_vec res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}
