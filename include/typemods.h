#ifndef __TYPEMODS_H__
#define __TYPEMODS_H__

#define _CUZ_ERR_MSG_BUFFER_SZ 256

typedef unsigned int uint;
typedef unsigned long ulong;

enum cuz_err_codes
{
  CUZ_SUCCESS,
  CUZ_UNDEF_ERR,
  CUZ_MEMORY_ALLOC_ERR
};

struct cuz_err_t
{
  uint code;
  char msg[_CUZ_ERR_MSG_BUFFER_SZ];
};

#endif