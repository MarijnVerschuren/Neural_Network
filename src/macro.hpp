#pragma once


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