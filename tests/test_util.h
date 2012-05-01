#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <assert.h>

namespace test_util
{

template <typename C>
typename C::value_type& get_item( C& collection, size_t idx )
{
  size_t count = 0;
  typename C::iterator iter;

  for ( iter = collection.begin();
	iter != collection.end() && count < idx;
	++iter, ++count )
  { }

  if ( iter != collection.end() )
  {
    return *iter;
  }

  assert(false);

}

}

#endif
