#ifndef __TYPEMODS_H__
#define __TYPEMODS_H__

#define _CUZ_ERR_MSG_BUFFER_SZ 512
#define _CUZ_NBR_BUFFER_SZ 32
#define _CUZ_PRINTF_CELL_BUFFER_SZ 64

typedef unsigned char uchar;
typedef short unsigned int suint;
typedef unsigned int uint;
typedef unsigned long ulong;

enum cuz_err_codes {
  CUZ_SUCCESS,
  CUZ_UNDEF_ERR,
  CUZ_MALLOC_ERR,
  CUZ_BUFFER_ERR
};

struct cuz_err_t {
  uint code;
  char msg[_CUZ_ERR_MSG_BUFFER_SZ];
};

#endif
