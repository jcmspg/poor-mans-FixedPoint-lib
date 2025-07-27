/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:48:13 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/27 17:25:05 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

// 64-bit fixed-point operations implementation

// Basic arithmetic operations for 64-bit fixed-point numbers
t_fixed64	fixed64_add(t_fixed64 a, t_fixed64 b)
{
	return (a + b);
}

t_fixed64	fixed64_sub(t_fixed64 a, t_fixed64 b)
{
	return (a - b);
}

t_fixed64	fixed64_mul(t_fixed64 a, t_fixed64 b)
{
	int64_t temp = a * b; // 64-bit multiplication, may overflow
	return (t_fixed64)(temp >> FIXED_SHIFT_64);
}

t_fixed64	fixed64_div(t_fixed64 a, t_fixed64 b)
{
	if (b == 0)
		return (0);
	return (t_fixed64)((a << (FIXED_SHIFT_64 / 2)) / b);
}

// Advanced operations for 32-bit fixed-point numbers
t_fixed64	fixed64_square(t_fixed64 a)
{
	return (fixed64_mul(a, a));
}

t_fixed64	fixed64_abs(t_fixed64 a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

t_fixed64	fixed64_sqrt(t_fixed64 a)
{
	t_fixed64 x;
	t_fixed64 y;
	t_fixed64 epsilon;
	int i;

	if (a <= 0)
		return (0);
	i = 0;
	x = a;
	y = FIXED_ONE_64;
	epsilon = (1LL << (FIXED_SHIFT_64 - 8)); // 0.0625
	while ((i++ < 20) && fixed64_abs(x - y) > epsilon)
	{
		x = fixed64_div((x + y), FIXED_TWO_64); // (x + y) / 2
		y = fixed64_div(a, x);
	}
	return (x);
}