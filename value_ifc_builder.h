#ifndef VALUE_IFC_BUILDER_H
#define VALUE_IFC_BUILDER_H

#include <list>
#include <map>
#include <deque>
#include <set>
#include <vector>

#include <value_ifc.h>


///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
class value_ifc_builder
{
 public:

  static value_ifc<T>* build()
  {
    return new simple_scalar_ifc<T>();
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename U>
class value_ifc_builder<std::vector<U> >
{
 public:

  static value_ifc<std::vector<U> >* build()
  {
    return new collection_ifc<std::vector<U> >( value_ifc_builder<U>::build() );
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename U>
class value_ifc_builder<std::list<U> >
{
 public:

  static value_ifc<std::list<U> >* build()
  {
    return new collection_ifc<std::list<U> >( value_ifc_builder<U>::build() );
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename U>
class value_ifc_builder<std::deque<U> >
{
 public:

  static value_ifc<std::deque<U> >* build()
  {
    return new collection_ifc<std::deque<U> >( value_ifc_builder<U>::build() );
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename U>
class value_ifc_builder<std::set<U> >
{
 public:

  static value_ifc<std::set<U> >* build()
  {
    return new collection_ifc<std::set<U> >( value_ifc_builder<U>::build() );
  }
};





#endif
