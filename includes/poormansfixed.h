/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poormansfixed.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:45:56 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/27 18:17:52 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POORMANSFIXED_H
# define POORMANSFIXED_H

# include <stdint.h>

# define FIXED_SHIFT_32 16
# define FIXED_SHIFT_64 32

# define FIXED_ONE_32 (1 << FIXED_SHIFT_32)
# define FIXED_ONE_64 (1LL << FIXED_SHIFT_64)
# define FIXED_TWO_32 (2 * FIXED_ONE_32)
# define FIXED_TWO_64 (2LL * FIXED_ONE_64)
# define FIXED_HALF_32 (FIXED_ONE_32 / 2)
# define FIXED_HALF_64 (FIXED_ONE_64 / 2)

// Define your types here
typedef int32_t	t_fixed32;
typedef int64_t	t_fixed64;

// 32-bit fixed-point operations
t_fixed32		fixed32_add(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_sub(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_mul(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_div(t_fixed32 a, t_fixed32 b);

// 32-bit fixed-point advanced operations
t_fixed32		fixed32_square(t_fixed32 a);
t_fixed32		fixed32_abs(t_fixed32 a);
t_fixed32		fixed32_sqrt(t_fixed32 a);

// 64-bit fixed-point operations
t_fixed64		fixed64_add(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_sub(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_mul(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_div(t_fixed64 a, t_fixed64 b);

// 64-bit fixed-point advanced operations
t_fixed64		fixed64_square(t_fixed64 a);
t_fixed64		fixed64_abs(t_fixed64 a);
t_fixed64		fixed64_sqrt(t_fixed64 a);

// Conversions

// Convert float to 32-bit fixed-point
t_fixed32		to_fixed32(float x);

// Convert double to 64-bit fixed-point
t_fixed64		to_fixed64(double x);

// Convert 32-bit fixed-point to float
float			from_fixed32(t_fixed32 x);

// Convert 64-bit fixed-point to double
double			from_fixed64(t_fixed64 x);

#endif /* POORMANSFIXED_H */
