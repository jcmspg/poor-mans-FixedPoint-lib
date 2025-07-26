/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:43:35 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/26 20:16:08 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

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