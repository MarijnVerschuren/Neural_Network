#pragma once
#include <stdint.h>
#include <Eigen/Dense>

#define dynamic_f64_matrix Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
#define dynamic_f64_row_vector Eigen::Matrix<double, Eigen::Dynamic, 1>
#define dynamic_f64_column_vector Eigen::Matrix<double, 1, Eigen::Dynamic>

#ifdef __GNUC__  // gcc compilers
	#define BS16(x) __builtin_bswap16(x)
	#define BS32(x) __builtin_bswap32(x)
	#define BS64(x) __builtin_bswap64(x)

	#define FORCE_INLINE __attribute__((always_inline))
#endif	// __GNUC__
#ifdef __MSVC__
	#define BS16(x) _byteswap_ushort(x)
	#define BS32(x) _byteswap_ulong(x)
	#define BS64(x) _byteswap_uint64(x)

	#define FORCE_INLINE __forceinline
#endif	// __MSVC__