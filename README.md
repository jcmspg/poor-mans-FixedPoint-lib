# Poor Man's Fixed Point Library

![could you spare some efficiency, sir](assets/efficiency.jpg)

## Table of Contents

- [Overview](#overview)
- [Why Fixed Point?](#why-fixed-point)
- [Features](#features)
- [Installation](#installation)
  - [Build the Library](#build-the-library)
  - [System-wide Installation](#system-wide-installation)
  - [Clean Build Files](#clean-build-files)
- [Usage](#usage)
  - [Include the Header](#include-the-header)
  - [Link the Library](#link-the-library)
  - [Basic Usage Examples](#basic-usage-examples)
- [API Reference](#api-reference)
  - [Types](#types)
  - [Constants](#constants)
  - [32-bit Operations](#32-bit-operations)
  - [64-bit Operations](#64-bit-operations)
  - [Conversion Functions](#conversion-functions)
- [Cub3D Integration Example](#cub3d-integration-example)
- [Technical Details](#technical-details)
  - [Fixed-Point Format](#fixed-point-format)
  - [Error Handling Philosophy](#error-handling-philosophy)
  - [Performance Considerations](#performance-considerations)
- [Project Structure](#project-structure)
- [Building from Source](#building-from-source)
- [Benchmarks](#benchmarks)
- [License](#license)
- [Contributing](#contributing)
- [Author](#author)

---

## Overview

A lightweight, efficient fixed-point arithmetic library designed for performance-critical applications like raycasting engines (e.g., cub3d), embedded development, and other scenarios where floating-point is overkill or unavailable.

**Disclaimer**: This library is not IEEE-compliant or intended for high-precision scientific work — it's for when floating point is overkill or unavailable.

## Why Fixed Point?

Fixed-point arithmetic offers several advantages over floating-point math:

- **Performance**: Integer operations are typically faster than floating-point operations
- **Deterministic**: Results are consistent across different platforms and architectures
- **Memory efficient**: No FPU operations required, ideal for embedded systems or performance-critical code
- **Perfect for raycasting**: Maintains adequate precision for distance calculations and trigonometric operations
- **Predictable behavior**: No floating-point edge cases or NaN/infinity issues

![pros and cons](assets/fp%20vs%20float_bw.png)

## Features

- **32-bit and 64-bit fixed-point types**
- **Basic arithmetic operations**: add, subtract, multiply, divide
- **Conversion functions**: seamless conversion between fixed-point and floating-point
- **No external dependencies**: only uses standard integer types
- **Optimized for raycasting**: designed with game engine math in mind
- **Overflow-by-design**: Fast operations without expensive overflow checks

## Installation

### Build the Library

```bash
make
```

### System-wide Installation

```bash
make install
```

This installs the library to `/usr/local/lib/` and headers to `/usr/local/include/`.

### Clean Build Files

```bash
make clean    # Remove object files
make fclean   # Remove object files and library
make re       # Clean rebuild (fclean + make)
```

## Usage

### Include the Header

```c
#include "poormansfixed.h"
```

### Link the Library

```bash
gcc your_program.c -lpoormansfixed -L/usr/local/lib
```

### Basic Usage Examples

#### 32-bit Fixed Point

```c
#include "poormansfixed.h"
#include <stdio.h>

int main(void)
{
    // Convert from float to fixed-point
    t_fixed32 a = to_fixed32(3.14f);
    t_fixed32 b = to_fixed32(2.0f);

    // Perform arithmetic
    t_fixed32 sum = fixed32_add(a, b);
    t_fixed32 product = fixed32_mul(a, b);
    t_fixed32 quotient = fixed32_div(a, b);

    // Convert back to float for display
    float result = from_fixed32(sum);
    printf("Result: %f\n", result);

    return (0);
}
```

#### 64-bit Fixed Point

```c
// For higher precision calculations
t_fixed64 x = to_fixed64(1.5);
t_fixed64 y = to_fixed64(2.5);
t_fixed64 distance_squared = fixed64_add(
    fixed64_mul(x, x),
    fixed64_mul(y, y)
);

double result = from_fixed64(distance_squared);
// Note: This gives you distance², not distance (sqrt not implemented)
```

#### Trigonometry Example

```c
#include "poormansfixed.h"
#include <stdio.h>

int main(void)
{
    // 32-bit trigonometry
    t_fixed32 angle_32 = to_fixed32(M_PI / 4);  // 45 degrees
    t_fixed32 sin_val = fixed32_sin(angle_32);
    t_fixed32 cos_val = fixed32_cos(angle_32);
    t_fixed32 tan_val = fixed32_tan(angle_32);
    
    printf("32-bit: sin(π/4) = %f\n", from_fixed32(sin_val));  // ≈ 0.707
    printf("32-bit: cos(π/4) = %f\n", from_fixed32(cos_val));  // ≈ 0.707
    printf("32-bit: tan(π/4) = %f\n", from_fixed32(tan_val));  // ≈ 1.0
    
    // 64-bit trigonometry (higher precision)
    t_fixed64 angle_64 = to_fixed64(M_PI / 6);  // 30 degrees
    t_fixed64 sin_val_64 = fixed64_sin(angle_64);
    t_fixed64 cos_val_64 = fixed64_cos(angle_64);
    
    printf("64-bit: sin(π/6) = %f\n", from_fixed64(sin_val_64));  // ≈ 0.5
    printf("64-bit: cos(π/6) = %f\n", from_fixed64(cos_val_64));  // ≈ 0.866
    
    return (0);
}
```

## API Reference

### Types

```c
typedef int32_t t_fixed32;  // 32-bit fixed-point (16.16 format)
typedef int64_t t_fixed64;  // 64-bit fixed-point (32.32 format)
```

### Constants

- `FIXED_SHIFT_32`: Fractional bits for 32-bit (16)
- `FIXED_SHIFT_64`: Fractional bits for 64-bit (32)
- `FIXED_ONE_32`: Represents 1.0 in 32-bit fixed-point (65536)
- `FIXED_ONE_64`: Represents 1.0 in 64-bit fixed-point (4294967296)

### 32-bit Operations

| Function            | Description                                      |
| ------------------- | ------------------------------------------------ |
| `fixed32_add(a, b)` | Addition: a + b                                  |
| `fixed32_sub(a, b)` | Subtraction: a - b                               |
| `fixed32_mul(a, b)` | Multiplication: a × b (uses 64-bit intermediate) |
| `fixed32_div(a, b)` | Division: a ÷ b (returns 0 if b = 0)             |
| `fixed32_abs(a)`    | Absolute value: \|a\|                            |
| `fixed32_square(a)` | Square: a²                                       |
| `fixed32_sqrt(a)`   | Square root: √a (Newton's method, ~20 iterations)|
| `fixed32_sin(a)`    | Sine: sin(a) (Taylor series, 5 terms max)       |
| `fixed32_cos(a)`    | Cosine: cos(a) = sin(a + π/2)                    |
| `fixed32_tan(a)`    | Tangent: tan(a) = sin(a) / cos(a)                |

### 64-bit Operations

| Function            | Description                                      |
| ------------------- | ------------------------------------------------ |
| `fixed64_add(a, b)` | Addition: a + b                                  |
| `fixed64_sub(a, b)` | Subtraction: a - b                               |
| `fixed64_mul(a, b)` | Multiplication: a × b (may overflow)             |
| `fixed64_div(a, b)` | Division: a ÷ b (returns 0 if b = 0)             |
| `fixed64_abs(a)`    | Absolute value: \|a\|                            |
| `fixed64_square(a)` | Square: a²                                       |
| `fixed64_sqrt(a)`   | Square root: √a (Newton's method, ~20 iterations)|
| `fixed64_sin(a)`    | Sine: sin(a) (Taylor series, 7 terms max)       |
| `fixed64_cos(a)`    | Cosine: cos(a) = sin(a + π/2)                    |
| `fixed64_tan(a)`    | Tangent: tan(a) = sin(a) / cos(a)                |

### Conversion Functions

| Function                    | Description                          |
| --------------------------- | ------------------------------------ |
| `to_fixed32(float x)`       | Convert float to 32-bit fixed-point  |
| `to_fixed64(double x)`      | Convert double to 64-bit fixed-point |
| `from_fixed32(t_fixed32 x)` | Convert 32-bit fixed-point to float  |
| `from_fixed64(t_fixed64 x)` | Convert 64-bit fixed-point to double |

## Cub3D Integration Example

Here's how you might use this library in a raycasting engine:

```c
#include "poormansfixed.h"

// Ray-wall intersection using fixed-point
typedef struct s_ray {
    t_fixed32 x, y;     // Ray position
    t_fixed32 angle;    // Ray direction angle
} t_ray;

typedef struct s_wall {
    t_fixed32 x, y;     // Wall position
} t_wall;

// Calculate ray direction using trigonometry
void calculate_ray_direction(t_ray *ray, t_fixed32 *dx, t_fixed32 *dy)
{
    *dx = fixed32_cos(ray->angle);
    *dy = fixed32_sin(ray->angle);
}

// Calculate actual distance using fixed-point sqrt
t_fixed32 calculate_distance(t_ray ray, t_wall wall)
{
    t_fixed32 dx = fixed32_sub(wall.x, ray.x);
    t_fixed32 dy = fixed32_sub(wall.y, ray.y);
    
    t_fixed32 distance_squared = fixed32_add(
        fixed32_square(dx),
        fixed32_square(dy)
    );
    
    return fixed32_sqrt(distance_squared);
}

// Fast distance comparison without sqrt
t_fixed32 calculate_distance_squared(t_ray ray, t_wall wall)
{
    t_fixed32 dx = fixed32_sub(wall.x, ray.x);
    t_fixed32 dy = fixed32_sub(wall.y, ray.y);
    
    return fixed32_add(
        fixed32_square(dx),
        fixed32_square(dy)
    );
}

// Usage in main raycasting loop
void raycast_example(void)
{
    t_ray player_ray = {
        .x = to_fixed32(5.5f),
        .y = to_fixed32(7.2f),
        .angle = to_fixed32(M_PI / 4)  // 45-degree angle
    };

    t_wall wall = {
        .x = to_fixed32(10.0f),
        .y = to_fixed32(12.0f)
    };

    // Calculate ray direction
    t_fixed32 ray_dx, ray_dy;
    calculate_ray_direction(&player_ray, &ray_dx, &ray_dy);

    // Option 1: Actual distance (slower, more accurate)
    t_fixed32 distance = calculate_distance(player_ray, wall);
    
    // Option 2: Distance squared (faster, for comparisons)
    t_fixed32 dist_sq = calculate_distance_squared(player_ray, wall);
    
    // Convert back only when needed for rendering
    float render_distance = from_fixed32(distance);
    
    printf("Ray direction: (%f, %f)\n", from_fixed32(ray_dx), from_fixed32(ray_dy));
    printf("Distance to wall: %f\n", render_distance);
}
```

## Technical Details

### Fixed-Point Format

- **32-bit**: 16.16 format (16 integer bits, 16 fractional bits)

  - Range: -32,768 to 32,767.999...
  - Precision: ~0.000015 (1/65536)
  - Best for: General game math, coordinates, basic trigonometry

- **64-bit**: 32.32 format (32 integer bits, 32 fractional bits)
  - Range: -2,147,483,648 to 2,147,483,647.999...
  - Precision: ~0.0000000002 (1/4294967296)
  - Best for: High-precision calculations, accumulated values

### Error Handling Philosophy

This is a "poor man's" library — we prioritize speed over safety:

- **Division by zero**: Returns 0 (no exceptions thrown)
- **Overflow behavior**:
  - 32-bit multiplication: Uses 64-bit intermediate, should not overflow
  - 64-bit multiplication: May overflow by design (wraps around)
  - Addition/Subtraction: Standard integer overflow behavior
- **No NaN/Infinity**: Invalid results become garbage values (as intended)

### Performance Considerations

- **Multiplication**: 32-bit uses 64-bit intermediate results to prevent overflow
- **Division**: Includes shift optimization for better precision
- **Trigonometry**: Optimized Taylor series with early termination
- **Branch-prediction friendly**: Minimal conditional logic in hot paths
- **Cache-friendly**: Simple integer operations, no lookup tables

## Project Structure

```
poormans_fixedpoint_lib/
├── includes/
│   └── poormansfixed.h      # Main header file with all definitions
├── srcs/
│   ├── conversions.c        # Float/double conversion functions
│   ├── operations_32.c      # 32-bit arithmetic operations
│   └── operations_64.c      # 64-bit arithmetic operations
├── assets/                  # Documentation images
├── Makefile                 # Build configuration
└── README.md               # This file
```

## Building from Source

### Prerequisites

- GCC compiler (or compatible)
- Make utility

### Build Commands

```bash
git clone https://github.com/jcmspg/poor-mans-FixedPoint-lib
cd poormans_fixedpoint_lib
make                    # Build the library
make install           # Install system-wide (requires sudo)
```

## Benchmarks

_TODO: Add performance comparisons between fixed-point and floating-point operations for typical raycasting scenarios._

Planned benchmarks:

- Distance calculations (32-bit fixed vs float)
- Trigonometric approximations
- Memory usage comparisons
- Cache performance analysis

## License

This project is open source. Feel free to use it in your projects, including cub3d implementations and commercial software.

## Contributing

Contributions are welcome! Priority areas for improvement:

- **Additional functions**: atan2, asin, acos implementations
- **Optimization**: Lookup tables for trigonometric functions
- **Platform optimizations**: SIMD instructions, ARM NEON support
- **Extended precision**: 128-bit fixed-point for specialized cases
- **Benchmarking suite**: Performance comparison tools
- **Advanced math**: Logarithms, exponentials, hyperbolic functions

## Author

joao gomes

---

Created for efficient raycasting in cub3d and other performance-critical applications where floating-point is overkill.

_"Could you spare some efficiency, sir?"_
