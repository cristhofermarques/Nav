#ifndef NAV_BIT_H
#define NAV_BIT_H

#include <Types/Nav_Value_Type.h>

#define NAV_BIT8_CREATE_MASK(bitRow) ((((Bit8)1) << bitRow))
#define NAV_BIT16_CREATE_MASK(bitRow) ((((Bit16)1) << bitRow))
#define NAV_BIT32_CREATE_MASK(bitRow) ((((Bit32)1) << bitRow))
#define NAV_BIT64_CREATE_MASK(bitRow) ((((Bit64)1) << bitRow))

#define NAV_BIT_GET( value, bitRow) ((value) & (1 << bitRow))
#define NAV_BIT_ENABLE( value, bitRow) ((value) |= (1 << bitRow))
#define NAV_BIT_DISABLE( value, bitRow) ((value) &= ~(1 << bitRow))

#endif