#ifndef BUILD_MEMBER_IFC_H
#define BUILD_MEMBER_IFC_H

#include <value_ifc.h>
#include <jeason.h>

class jeason_base;

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
  member_ifc<T>* build_member_ifc( U T::*member_ptr, jeason_base* )
{
  // TODO: error checking

  return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
member_ifc<T>* build_member_ifc( int T::*member_ptr, jeason_base* )
{
  return new scalar_member_ifc<T,int>( member_ptr );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
member_ifc<T>* build_member_ifc( bool T::*member_ptr, jeason_base* )
{
  return new scalar_member_ifc<T,bool>( member_ptr );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
member_ifc<T>* build_member_ifc( float T::*member_ptr, jeason_base* )
{
  return new scalar_member_ifc<T,float>( member_ptr );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
member_ifc<T>* build_member_ifc( double T::*member_ptr, jeason_base* )
{
  return new scalar_member_ifc<T,double>( member_ptr );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
member_ifc<T>* build_member_ifc( std::string T::*member_ptr, jeason_base* )
{
  return new scalar_member_ifc<T,std::string>( member_ptr );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
member_ifc<T>* build_member_ifc( std::vector<U> T::*member_ptr, 
				 jeason_base* parent )
{
  jeason<std::vector<U> >* collection_parser = jeason<std::vector<U> >::build();

  collection_parser->set_parent(parent);

  return new object_member_ifc<T,std::vector<U> >( member_ptr, collection_parser );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
member_ifc<T>* build_member_ifc( std::list<U> T::*member_ptr,
				 jeason_base* parent )
{
  jeason<std::list<U> >* collection_parser = jeason<std::list<U> >::build();

  collection_parser->set_parent(parent);

  return new object_member_ifc<T,std::list<U> >( member_ptr, collection_parser );
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
member_ifc<T>* build_member_ifc( std::deque<U> T::*member_ptr, 
				 jeason_base* parent )
{
  jeason<std::deque<U> >* collection_parser = jeason<std::deque<U> >::build();

  collection_parser->set_parent(parent);
  
  return new object_member_ifc<T,std::deque<U> >( member_ptr, collection_parser );
}


///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
  member_ifc<T>* build_member_ifc( U T::*member_ptr, jeason<U>* parser, jeason_base* parent )
{
  parser->set_parent(parent);

  return new object_member_ifc<T,U>( member_ptr, parser );
}


#endif
