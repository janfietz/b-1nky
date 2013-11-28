/***************************************************************************//**
  \file bcEndian.h

  \brief
    Interface for endian-neutral code.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2011, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    3/10/09 Max Gekk - Created.
 ******************************************************************************/
#ifndef _BC_ENDIAN_H
#define _BC_ENDIAN_H
#ifdef _BIG_ENDIAN_
  #ifdef _DO_NOT_USE_BE
    #undef _BIG_ENDIAN_
  #endif //_DO_NOT_USE_BE
#endif //_BIG_ENDIAN_

/******************************************************************************
                             Definitions section
 ******************************************************************************/
/* Macroses for reversing of bit fields in structure type depending on endian. */
#if defined _BIG_ENDIAN_
  #define  BIT_FIELDS_1(f1) f1;
  #define  BIT_FIELDS_2(f1, f2) f2; f1;
  #define  BIT_FIELDS_3(f1, f2, f3)  f3; f2; f1;
  #define  BIT_FIELDS_4(f1, f2, f3, f4)  f4; f3; f2; f1;
  #define  BIT_FIELDS_5(f1, f2, f3, f4, f5)  f5; f4; f3; f2; f1;
  #define  BIT_FIELDS_6(f1, f2, f3, f4, f5, f6)  f6; f5; f4; f3; f2; f1;
  #define  BIT_FIELDS_7(f1, f2, f3, f4, f5, f6, f7)  f7; f6; f5; f4; f3; f2; f1;
  #define  BIT_FIELDS_8(f1, f2, f3, f4, f5, f6, f7, f8)  \
      f8; f7; f6; f5; f4; f3; f2; f1;
#else /* _LITTLE_ENDIAN_ by default */
  #define  BIT_FIELDS_1(f1) f1;
  #define  BIT_FIELDS_2(f1, f2) f1; f2;
  #define  BIT_FIELDS_3(f1, f2, f3)  f1; f2; f3;
  #define  BIT_FIELDS_4(f1, f2, f3, f4)  f1; f2; f3; f4;
  #define  BIT_FIELDS_5(f1, f2, f3, f4, f5)  f1; f2; f3; f4; f5;
  #define  BIT_FIELDS_6(f1, f2, f3, f4, f5, f6)  f1; f2; f3; f4; f5; f6;
  #define  BIT_FIELDS_7(f1, f2, f3, f4, f5, f6, f7)  f1; f2; f3; f4; f5; f6; f7;
  #define  BIT_FIELDS_8(f1, f2, f3, f4, f5, f6, f7, f8) \
      f1; f2; f3; f4; f5; f6; f7; f8;
#endif /* _BIG_ENDIAN_ */

/* various macroses to swap bytes */
#ifdef _BIG_ENDIAN_
// Toggles the endianism of u16 (by swapping its bytes).
#if (defined __GNUC__)
  #define swap16(x) ((uint16_t)__builtin_bswap_16((uint16_t)(x)))
#elif (defined __ICCAVR32__)
  #define swap16(x) ((uint16_t)__swap_bytes_in_halfwords((uint16_t)(x)))
#else
  #error unknown compiler
#endif

// Toggles the endianism of u32 (by swapping its bytes).
#if (defined __GNUC__)
  #define swap32(x) ((uint32_t)__builtin_bswap_32((uint32_t)(x)))
#elif (defined __ICCAVR32__)
  #define swap32(x) ((uint32_t)__swap_bytes((uint32_t)(x)))
#else
  #error unknown compiler
#endif

// Toggles the endianism of u64 (by swapping its bytes).
#define swap64(x) ((uint64_t)(((uint64_t)swap32((uint64_t)(x) >> 32)) | ((uint64_t)swap32((uint64_t)(x)) << 32)))

#define CPU_TO_LE16(x) swap16(x)
#define CPU_TO_LE32(x) swap32(x)
#define CPU_TO_LE64(x) swap64(x)
#define LE16_TO_CPU(x) swap16(x)
#define LE32_TO_CPU(x) swap32(x)
#define LE64_TO_CPU(x) swap64(x)

/* Converting of constants from CPU endian to little endian. */
#define CCPU_TO_LE16(x) ((uint16_t)(\
  (((uint16_t)(x) & (uint16_t)0x00ffU) << 8) | \
  (((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define CCPU_TO_LE32(x) ((uint32_t)(\
  (((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) | \
  (((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) | \
  (((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) | \
  (((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))

#define CCPU_TO_LE64(x) ((uint64_t)(\
  (((uint64_t)(x) & (uint64_t)0x00000000000000ffULL) << 56) | \
  (((uint64_t)(x) & (uint64_t)0x000000000000ff00ULL) << 40) | \
  (((uint64_t)(x) & (uint64_t)0x0000000000ff0000ULL) << 24) | \
  (((uint64_t)(x) & (uint64_t)0x00000000ff000000ULL) <<  8) | \
  (((uint64_t)(x) & (uint64_t)0x000000ff00000000ULL) >>  8) | \
  (((uint64_t)(x) & (uint64_t)0x0000ff0000000000ULL) >> 24) | \
  (((uint64_t)(x) & (uint64_t)0x00ff000000000000ULL) >> 40) | \
  (((uint64_t)(x) & (uint64_t)0xff00000000000000ULL) >> 56)))

/* Converting of constants from little endian to CPU endian. */
#define CLE16_TO_CPU(x) CCPU_TO_LE16(x)
#define CLE32_TO_CPU(x) CCPU_TO_LE32(x)
#define CLE64_TO_CPU(x) CCPU_TO_LE64(x)

#else //_BIG_ENDIAN_

#define CPU_TO_LE16(x) (x)
#define CPU_TO_LE32(x) (x)
#define CPU_TO_LE64(x) (x)
#define LE16_TO_CPU(x) (x)
#define LE32_TO_CPU(x) (x)
#define LE64_TO_CPU(x) (x)
#define CLE16_TO_CPU(x) (x)
#define CLE32_TO_CPU(x) (x)
#define CLE64_TO_CPU(x) (x)

/* Converting of constants from CPU endian to little endian. */
#define CCPU_TO_LE16(x) (x)
#define CCPU_TO_LE32(x) (x)
#define CCPU_TO_LE64(x) (x)

#endif

/******************************************************************************
  \brief The macro for declaration of bit fields with little endian order.

    Total size of bit fields must equal 8 bit (or one octet).

  \param amount - amount of bit fields in octet.
  \param fields - list of bit fields that are separated by ','.
 ******************************************************************************/
#define  LITTLE_ENDIAN_OCTET(amount, fields) BIT_FIELDS_ ## amount fields

#endif /* _BC_ENDIAN_H */
/* eof bcEndian.h */
