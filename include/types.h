#ifndef __TYPES_H__
#define __TYPES_H__

#include <type_traits>

// static cast enum to its integral type
template < typename E >
constexpr auto to_integral (E e) -> typename std::underlying_type < E >::type 
{
  return static_cast < typename std::underlying_type < E >::type > (e);
}

#endif /* __TYPES_H__ */