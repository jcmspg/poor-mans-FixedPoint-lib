/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:41:52 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/26 20:15:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

t_fixed32	to_fixed32(float x)
{
	return (t_fixed32)(x * FIXED_ONE_32);
}

t_fixed64	to_fixed64(double x)
{
	return (t_fixed64)(x * FIXED_ONE_64);
}

float	from_fixed32(t_fixed32 x)
{
	return ((float)x / FIXED_ONE_32);
}

double	from_fixed64(t_fixed64 x)
{
	return ((double)x / FIXED_ONE_64);
}