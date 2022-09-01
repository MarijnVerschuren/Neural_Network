#pragma once

#define int8 char
#define uint8 unsigned char
#define int16 short
#define uint16 unsigned short
#define int32 long
#define uint32 unsigned long
#define int64 long long
#define uint64 unsigned long long

#define f32 float
#define f64 double



#ifdef __GNUC__  // gcc compilers
	#ifdef __x86_64__

		#define int128 __int128
		#define uint128 unsigned __int128

		#define BS128(x) __builtin_bswap128(x)

	#endif	// __x86_64__

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