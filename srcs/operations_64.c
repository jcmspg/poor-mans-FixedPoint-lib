/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:48:13 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/26 20:16:08 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

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
