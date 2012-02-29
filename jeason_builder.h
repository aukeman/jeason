#ifndef JEASON_BUILDER_H
#define JEASON_BUILDER_H

#include <list>
#include <vector>
#include <deque>

#include <jeason_types.h>

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
class jeason_builder
{
 public:
  
  static jeason<T>* build()
  {
    return new object_jeason<T>;
  }

};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename U>
class jeason_builder<std::vector<std::vector<U> > >
{
 public:

  static jeason<std::vector<std::vector<U> > >* build()
  {
    return new multidimension_collection_jeason<std::vector<std::vector<U> > >();
  }

  static jeason<std::vector<std::vector<U> > >* build( jeason<std::vector<U> >* element_parser )
  {
    return new multidimension_collection_jeason<std::vector<std::vector<U> > >(element_parser);
  }

};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename U>
class jeason_builder<std::vector<U> >
{
 public:

  static jeason<std::vector<U> >* build()
  {
    return new collection_jeason<std::vector<U> >();
  }

  static jeason<std::vector<U> >* build( jeason<U>* element_parser )
  {
    return new object_collection_jeason<std::vector<U> >(element_parser);
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename U>
class jeason_builder<std::list<U> >
{
 public:

  static jeason<std::list<U> >* build()
  {
    return new collection_jeason<std::list<U> >();
  }

  static jeason<std::list<U> >* build( jeason<U>* element_parser )
  {
    return new object_collection_jeason<std::list<U> >(element_parser);
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename U>
class jeason_builder<std::deque<U> >
{
 public:

  static jeason<std::deque<U> >* build()
  {
    return new collection_jeason<std::deque<U> >();
  }

  static jeason<std::deque<U> >* build( jeason<U>* element_parser )
  {
    return new object_collection_jeason<std::deque<U> >(element_parser);
  }
};


#endif
