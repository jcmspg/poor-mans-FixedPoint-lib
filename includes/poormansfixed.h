/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poormansfixed.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:45:56 by joamiran          #+#    #+#             */
/*   Updated: 2025/07/31 20:15:54 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POORMANSFIXED_H
# define POORMANSFIXED_H

# include <stdint.h>

// Fixed-point format definitions
# define FIXED_SHIFT_32 16
# define FIXED_SHIFT_64 32

// Basic constants
# define FIXED_ONE_32 (1 << FIXED_SHIFT_32)        // 1.0 in 16.16 format
# define FIXED_ONE_64 (1LL << FIXED_SHIFT_64)      // 1.0 in 32.32 format
# define FIXED_TWO_32 (2 * FIXED_ONE_32)           // 2.0 in 16.16 format
# define FIXED_TWO_64 (2LL * FIXED_ONE_64)         // 2.0 in 32.32 format
# define FIXED_HALF_32 (FIXED_ONE_32 / 2)          // 0.5 in 16.16 format
# define FIXED_HALF_64 (FIXED_ONE_64 / 2)          // 0.5 in 32.32 format

// Mathematical constants for trigonometry
# define FIXED_PI_32 (205887)                      // π ≈ 3.14159 in 16.16 format
# define FIXED_PI_64 (13493037705LL)               // π ≈ 3.14159 in 32.32 format
# define FIXED_PI_2_32 (102944)                    // π/2 ≈ 1.5708 in 16.16 format
# define FIXED_PI_2_64 (6746518852LL)              // π/2 ≈ 1.5708 in 32.32 format
# define FIXED_2PI_32 (411775)                     // 2π ≈ 6.28318 in 16.16 format
# define FIXED_2PI_64 (26986075410LL)              // 2π ≈ 6.28318 in 32.32 format

// Fixed-point type definitions
typedef int32_t	t_fixed32;                          // 32-bit fixed-point (16.16)
typedef int64_t	t_fixed64;                          // 64-bit fixed-point (32.32)

// ============================================================================
// 32-BIT FIXED-POINT OPERATIONS
// ============================================================================

// Basic arithmetic operations
t_fixed32		fixed32_add(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_sub(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_mul(t_fixed32 a, t_fixed32 b);
t_fixed32		fixed32_div(t_fixed32 a, t_fixed32 b);

// Advanced mathematical operations
t_fixed32		fixed32_abs(t_fixed32 a);
t_fixed32		fixed32_square(t_fixed32 a);
t_fixed32		fixed32_sqrt(t_fixed32 a);

// Trigonometric functions
t_fixed32		fixed32_sin(t_fixed32 angle);
t_fixed32		fixed32_cos(t_fixed32 angle);
t_fixed32		fixed32_tan(t_fixed32 angle);

// ============================================================================
// 64-BIT FIXED-POINT OPERATIONS
// ============================================================================

// Basic arithmetic operations
t_fixed64		fixed64_add(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_sub(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_mul(t_fixed64 a, t_fixed64 b);
t_fixed64		fixed64_div(t_fixed64 a, t_fixed64 b);

// Advanced mathematical operations
t_fixed64		fixed64_abs(t_fixed64 a);
t_fixed64		fixed64_square(t_fixed64 a);
t_fixed64		fixed64_sqrt(t_fixed64 a);

// Trigonometric functions
t_fixed64		fixed64_sin(t_fixed64 angle);
t_fixed64		fixed64_cos(t_fixed64 angle);
t_fixed64		fixed64_tan(t_fixed64 angle);

// ============================================================================
// CONVERSION FUNCTIONS
// ============================================================================

// Convert to fixed-point
t_fixed32		to_fixed32(float x);
t_fixed64		to_fixed64(double x);

// Convert from fixed-point
float			from_fixed32(t_fixed32 x);
double			from_fixed64(t_fixed64 x);

#endif /* POORMANSFIXED_H */
