#include "formats.h"
#include "typemods.h"
#include <stdio.h>
#include <string.h>

/*! Formats cell state to string of 'X's, ' 's, etc. wrapped in brackets
 *
 * \param s Cell state
 * \param buffer Buffer in which to store formatted string
 */
void cuz_formats_xosb(const cuz_state_t s, char *buffer) {
  char c;

  switch (s) {
  case CUZ_ON:
    c = 'X';
    break;

  case CUZ_OFF:
    c = ' ';
    break;

  case CUZ_SUSPENDED:
    c = '\\';
    break;

  default:
    c = '?';
    break;
  }

  snprintf(buffer, _CUZ_PRINTF_CELL_BUFFER_SZ, "[ %c ]", c);
}

/*! Formats cell state to string of 'X's, ' 's, etc. wrapped in spaces
 *
 * \param s Cell state
 * \param buffer Buffer in which to store formatted string
 */
void cuz_formats_xos(const cuz_state_t s, char *buffer) {
  char c;

  switch (s) {
  case CUZ_ON:
    c = 'X';
    break;

  case CUZ_OFF:
    c = ' ';
    break;

  case CUZ_SUSPENDED:
    c = '\\';
    break;

  default:
    c = '?';
    break;
  }

  snprintf(buffer, _CUZ_PRINTF_CELL_BUFFER_SZ, " %c ", c);
}
