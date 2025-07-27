/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:43:35 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/27 17:18:35 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

// 32-bit fixed-point operations implementation

// Basic arithmetic operations for 32-bit fixed-point numbers
t_fixed32	fixed32_add(t_fixed32 a, t_fixed32 b)
{
	return (a + b);
}

t_fixed32	fixed32_sub(t_fixed32 a, t_fixed32 b)
{
	return (a - b);
}

t_fixed32	fixed32_mul(t_fixed32 a, t_fixed32 b)
{
	return ((t_fixed32)(((int64_t)a * (int64_t)b) >> FIXED_SHIFT_32));
}

t_fixed32	fixed32_div(t_fixed32 a, t_fixed32 b)
{
	if (b == 0)
		return (0);
	return ((t_fixed32)(((int64_t)a << FIXED_SHIFT_32) / (int64_t)b));
}

// Advanced operations for 32-bit fixed-point numbers
t_fixed32	fixed32_square(t_fixed32 a)
{
	return (fixed32_mul(a, a));
}

t_fixed32	fixed32_abs(t_fixed32 a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

t_fixed32	fixed32_sqrt(t_fixed32 a)
{
	t_fixed32	x;
	t_fixed32	y;
	t_fixed32	epsilon;
	int			i;

	if (a <= 0)
		return (0);
	i = 0;
	x = a;
	y = FIXED_ONE_32;
	epsilon = (1 << (FIXED_SHIFT_32 - 4)); // 0.0625
	while (fixed32_abs(x - y) > epsilon && i++ < 10)
	{
		x = fixed32_div((x + y), FIXED_ONE_32 * 2); // (x + y) / 2
		y = fixed32_div(a, x);
	}
	return (x);
}
