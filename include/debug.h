#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "typemods.h"

#define CHECK_MEM_ALLOC(palloc, pcuz_err, ret_val_on_fail)                  \
  if ( (palloc) == NULL )                                                   \
  {                                                                         \
    (pcuz_err)->code = CUZ_MALLOC_ERR;                                      \
    snprintf ((pcuz_err)->msg, _CUZ_ERR_MSG_BUFFER_SZ,                      \
      "Memory allocation error in line %d of file %s (function %s)\n",      \
      __LINE__, __FILE__, __func__);                                        \
    return ret_val_on_fail;                                                 \
  }

void ret_void { return; }

#endif