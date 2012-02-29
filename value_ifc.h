#ifndef VALUE_IFC_H
#define VALUE_IFC_H

#include <jeason_base.h>
#include <jeason_types.h>

#include <parse_input.h>
#include <generate_output.h>
#include <create_default_value.h>

#include <iostream>

#include <vector>
#include <list>
#include <set>
#include <deque>

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
jeason_base* value_ifc<T>::get_parser()
{
  // TODO: error checking
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
//

// template<typename T>
// object_ifc<T>::object_ifc( jeason_base* object_parser ) :
//   object_parser(object_parser)
// { }

// template<typename T>
// jeason_base* object_ifc<T>::get_parser()
// { return object_parser; }


///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
simple_scalar_ifc<T>::simple_scalar_ifc()
{ }

template <typename T>
bool simple_scalar_ifc<T>::reset( T& value ) const
{
  value = create_default_value<T>();
  
  return true;
}

template <typename T>
bool simple_scalar_ifc<T>::serialize( const T& object, std::ostream& out) const
{
  return generate_output( object, out );
}

template <typename T>
bool simple_scalar_ifc<T>::deserialize( T& value, const std::string& in ) const
{
  return parse_input( in, value );
}


///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C>
collection_ifc<C>::collection_ifc(value_ifc<typename C::value_type>* element_ifc )
  :element_ifc(element_ifc)
{ }

template <typename C>
bool collection_ifc<C>::reset( C& collection ) const
{
  collection.clear();
  
  return true;
}

template <typename C>
bool collection_ifc<C>::serialize( const C& collection, 
				   std::ostream& out) const
{
  out << "[";
  
  for ( typename C::const_iterator iter = collection.begin();
	iter != collection.end();
	++iter )
  {
    if ( iter != collection.begin() )
    {
      out << ", ";
    }

    element_ifc->serialize( *iter, out );
  }
  
  out << "]";

  return true;
}

template <typename C>
bool collection_ifc<C>::deserialize( C& collection, 
				     const std::string& in ) const
{
  typename C::value_type v;
  
  if ( element_ifc->deserialize( v, in ) )
  {
    collection.insert( collection.end(), v );
    return true;
  }
  else
  {
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
scalar_member_ifc<T,U>::scalar_member_ifc( U T::*member_ptr ) :
  member_ptr(member_ptr)
{ }

template<typename T, typename U>
bool scalar_member_ifc<T,U>::reset( T& value ) const
{
  value.*member_ptr = create_default_value<U>();
  
  return true;
}

template<typename T, typename U>
bool scalar_member_ifc<T,U>::serialize( const T& value, std::ostream& out) const
{
  return generate_output( value.*member_ptr, out );
}

template<typename T, typename U>
bool scalar_member_ifc<T,U>::deserialize( T& value, 
					  const std::string& in ) const
{
  return parse_input( in, value.*member_ptr );
}

template<typename T, typename U>
bool scalar_member_ifc<T,U>::set_parser_subject( T& )
{
  // TODO: error checking

  return false;
}


///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
object_member_ifc<T,U>::object_member_ifc( U T::*member_ptr, 
					 jeason_base* parser ) :
  member_ptr(member_ptr),
  parser(parser)
{ }

template<typename T, typename U>
bool object_member_ifc<T,U>::reset( T& object ) const
{
  object.*member_ptr = create_default_value<U>();
  
  return true;
}

template<typename T, typename U>
bool object_member_ifc<T,U>::set_parser_subject( T& object )
{
  // TODO: can we do without the casting?
  ((jeason<U>*)parser)->set_subject( &(object.*member_ptr) );

  return true;
}

template<typename T, typename U>
bool object_member_ifc<T,U>::serialize( const T& object, std::ostream& out) const
{
  // TODO: can we do without the casting?
  ((jeason<U>*)parser)->serialize( object.*member_ptr, out );
  
  return false; 
}

template<typename T, typename U>
bool object_member_ifc<T,U>::deserialize( T& value, 
					  const std::string& in ) const
{
  // TODO: error checking
  
  return false;
}

template<typename T, typename U>
jeason_base* object_member_ifc<T,U>::get_parser()
{
  return parser;
}


#endif
