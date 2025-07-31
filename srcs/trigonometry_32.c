/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometry_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:00:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/31 20:17:12 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

static t_fixed32	normalize_angle_32(t_fixed32 angle)
{
    while (angle < 0)
        angle = fixed32_add(angle, FIXED_2PI_32);
    while (angle >= FIXED_2PI_32)
        angle = fixed32_sub(angle, FIXED_2PI_32);
    return (angle);
}

static t_fixed32	sin_taylor_32(t_fixed32 x)
{
    t_fixed32	result;
    t_fixed32	term;
    t_fixed32	x_squared;
    t_fixed32	temp;
    int			sign;

    result = x;
    term = x;
    x_squared = fixed32_mul(x, x);
    sign = -1;
    temp = 0;
    while (temp < to_fixed32(5.0f) && fixed32_abs(term) > (FIXED_ONE_32 >> 16))
    {
        term = fixed32_mul(term, x_squared);
        if (temp == 0)
            term = fixed32_div(term, to_fixed32(6.0f));
        else if (temp == to_fixed32(1.0f))
            term = fixed32_div(term, to_fixed32(20.0f));
        else if (temp == to_fixed32(2.0f))
            term = fixed32_div(term, to_fixed32(42.0f));
        else
            term = fixed32_div(term, to_fixed32(72.0f));
        if (sign > 0)
            result = fixed32_add(result, term);
        else
            result = fixed32_sub(result, term);
        sign = -sign;
        temp = fixed32_add(temp, to_fixed32(1.0f));
    }
    return (result);
}

static t_fixed32	sin_first_quadrant(t_fixed32 normalized)
{
    return (sin_taylor_32(normalized));
}

static t_fixed32	sin_second_quadrant(t_fixed32 normalized)
{
    t_fixed32	quadrant_angle;

    quadrant_angle = fixed32_sub(FIXED_PI_32, normalized);
    return (sin_taylor_32(quadrant_angle));
}

static t_fixed32	sin_third_quadrant(t_fixed32 normalized)
{
    t_fixed32	quadrant_angle;

    quadrant_angle = fixed32_sub(normalized, FIXED_PI_32);
    return (fixed32_sub(0, sin_taylor_32(quadrant_angle)));
}

static t_fixed32	sin_fourth_quadrant(t_fixed32 normalized)
{
    t_fixed32	quadrant_angle;

    quadrant_angle = fixed32_sub(FIXED_2PI_32, normalized);
    return (fixed32_sub(0, sin_taylor_32(quadrant_angle)));
}

t_fixed32	fixed32_sin(t_fixed32 angle)
{
    t_fixed32	normalized;

    normalized = normalize_angle_32(angle);
    if (normalized <= FIXED_PI_2_32)
        return (sin_first_quadrant(normalized));
    else if (normalized <= FIXED_PI_32)
        return (sin_second_quadrant(normalized));
    else if (normalized <= fixed32_add(FIXED_PI_32, FIXED_PI_2_32))
        return (sin_third_quadrant(normalized));
    else
        return (sin_fourth_quadrant(normalized));
}

t_fixed32	fixed32_cos(t_fixed32 angle)
{
    return (fixed32_sin(fixed32_add(angle, FIXED_PI_2_32)));
}

t_fixed32	fixed32_tan(t_fixed32 angle)
{
    t_fixed32	cos_val;

    cos_val = fixed32_cos(angle);
    if (fixed32_abs(cos_val) < (FIXED_ONE_32 >> 12))
        return (0);
    return (fixed32_div(fixed32_sin(angle), cos_val));
}