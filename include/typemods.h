#ifndef __TYPEMODS_H__
#define __TYPEMODS_H__

#define _CUZ_ERR_MSG_BUFFER_SZ 512

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef signed long long int longlong;

enum cuz_err_codes
{
  CUZ_SUCCESS,
  CUZ_UNDEF_ERR,
  CUZ_MALLOC_ERR
};

struct cuz_err_t
{
  uint code;
  char msg[_CUZ_ERR_MSG_BUFFER_SZ];
};

#endif