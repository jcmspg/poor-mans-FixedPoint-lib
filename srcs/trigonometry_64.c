/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometry_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:00:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/31 20:17:53 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/poormansfixed.h"

static t_fixed64	normalize_angle_64(t_fixed64 angle)
{
    while (angle < 0)
        angle = fixed64_add(angle, FIXED_2PI_64);
    while (angle >= FIXED_2PI_64)
        angle = fixed64_sub(angle, FIXED_2PI_64);
    return (angle);
}

static t_fixed64	sin_taylor_64(t_fixed64 x)
{
    t_fixed64	result;
    t_fixed64	term;
    t_fixed64	x_squared;
    t_fixed64	temp;
    int			sign;

    result = x;
    term = x;
    x_squared = fixed64_mul(x, x);
    sign = -1;
    temp = 0;
    while (temp < to_fixed64(7.0) && fixed64_abs(term) > (FIXED_ONE_64 >> 24))
    {
        term = fixed64_mul(term, x_squared);
        if (temp == 0)
            term = fixed64_div(term, to_fixed64(6.0));
        else if (temp == to_fixed64(1.0))
            term = fixed64_div(term, to_fixed64(20.0));
        else if (temp == to_fixed64(2.0))
            term = fixed64_div(term, to_fixed64(42.0));
        else if (temp == to_fixed64(3.0))
            term = fixed64_div(term, to_fixed64(72.0));
        else if (temp == to_fixed64(4.0))
            term = fixed64_div(term, to_fixed64(110.0));
        else if (temp == to_fixed64(5.0))
            term = fixed64_div(term, to_fixed64(156.0));
        else
            term = fixed64_div(term, to_fixed64(210.0));
        if (sign > 0)
            result = fixed64_add(result, term);
        else
            result = fixed64_sub(result, term);
        sign = -sign;
        temp = fixed64_add(temp, to_fixed64(1.0));
    }
    return (result);
}

static t_fixed64	sin_first_quadrant_64(t_fixed64 normalized)
{
    return (sin_taylor_64(normalized));
}

static t_fixed64	sin_second_quadrant_64(t_fixed64 normalized)
{
    t_fixed64	quadrant_angle;

    quadrant_angle = fixed64_sub(FIXED_PI_64, normalized);
    return (sin_taylor_64(quadrant_angle));
}

static t_fixed64	sin_third_quadrant_64(t_fixed64 normalized)
{
    t_fixed64	quadrant_angle;

    quadrant_angle = fixed64_sub(normalized, FIXED_PI_64);
    return (fixed64_sub(0, sin_taylor_64(quadrant_angle)));
}

static t_fixed64	sin_fourth_quadrant_64(t_fixed64 normalized)
{
    t_fixed64	quadrant_angle;

    quadrant_angle = fixed64_sub(FIXED_2PI_64, normalized);
    return (fixed64_sub(0, sin_taylor_64(quadrant_angle)));
}

t_fixed64	fixed64_sin(t_fixed64 angle)
{
    t_fixed64	normalized;

    normalized = normalize_angle_64(angle);
    if (normalized <= FIXED_PI_2_64)
        return (sin_first_quadrant_64(normalized));
    else if (normalized <= FIXED_PI_64)
        return (sin_second_quadrant_64(normalized));
    else if (normalized <= fixed64_add(FIXED_PI_64, FIXED_PI_2_64))
        return (sin_third_quadrant_64(normalized));
    else
        return (sin_fourth_quadrant_64(normalized));
}

t_fixed64	fixed64_cos(t_fixed64 angle)
{
    return (fixed64_sin(fixed64_add(angle, FIXED_PI_2_64)));
}

t_fixed64	fixed64_tan(t_fixed64 angle)
{
    t_fixed64	cos_val;

    cos_val = fixed64_cos(angle);
    if (fixed64_abs(cos_val) < (FIXED_ONE_64 >> 20))
        return (0);
    return (fixed64_div(fixed64_sin(angle), cos_val));
}