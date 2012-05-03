#ifndef JEASON_H
#define JEASON_H

#include <jeason_base.h>
#include <value_ifc_types.h>

#include <value_ifc_builder.h>

#include <jeason_types.h>

#include <build_member_ifc.h>
#include <jeason_builder.h>

#include <value_ifc.h>

#include <iostream>

#include <map>

extern std::istream* jeason_input_stream_ptr;

int yyparse( jeason_base* );

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
jeason<T>::jeason() : 
  subject(NULL), 
  parent(NULL)
{ }

template <typename T>
jeason_base* jeason<T>::get_parent()
{ return parent; }

template <typename T>
void jeason<T>::set_parent( jeason_base* parent )
{ this->parent = parent; }

template <typename T>
void jeason<T>::set_subject(T* subject)
{ this->subject = subject; }

template <typename T>
T* jeason<T>::get_subject()
{ return this->subject; }

template <typename T>
template <typename U>
void jeason<T>::add_member( const std::string& name, 
			    U T::*member_ptr )
{
  add_member( name, build_member_ifc(member_ptr) );
}

template <typename T>
template <typename U>
void jeason<T>::add_member(const std::string& name, 
			   U T::*member_ptr, 
			   jeason<U>* parser)
{
  parser->set_parent(this);
  add_member( name, build_member_ifc(member_ptr, parser) );
}

template <typename T>
void jeason<T>::add_member( const std::string name, member_ifc<T>* )
{
  // TODO: error checking
}

template <typename T>
void jeason<T>::apply_value( const std::string&, const std::string& value )
{
  // TODO: error checking
}

template <typename T>
void jeason<T>::apply_array_element( const std::string& value )
{
  // TODO error checking
}

template <typename T>
jeason_base* jeason<T>::begin_object()
{
  // TODO: error checking
  return NULL;
}

template <typename T>
jeason_base* jeason<T>::begin_object( const std::string& name )
{
  // TODO: error checking
  return NULL;
}

template <typename T>
jeason_base* jeason<T>::end_object()
{
  if ( this->get_parent() )
  {
    return this->get_parent();
  }
  else
  {
    // TODO: error checking
    return NULL;
  }
}

template <typename T>
jeason_base* jeason<T>::begin_array()
{
  // TODO: error checking
  return NULL;
}

template <typename T>
jeason_base* jeason<T>::begin_array( const std::string& name )
{
  // TODO: error checking
  return NULL;
}

template <typename T>
jeason_base* jeason<T>::end_array()
{
  if ( this->get_parent() )
  {
    return this->get_parent();
  }
  else
  {
    // TODO: error checking
    return NULL;
  }
}

template <typename T>
jeason<T>* jeason<T>::build()
{
  return jeason_builder<T>::build();
}

template <typename T>
template <typename U>
jeason<T>* jeason<T>::build( jeason<U>* element_parser )
{
  return jeason_builder<T>::build(element_parser);
}


///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C>
collection_jeason<C>::collection_jeason() :
  collection_ifc( value_ifc_builder<C>::build() )
{ }

template <typename C>
void collection_jeason<C>::apply_array_element( const std::string& value )
{
  collection_ifc->deserialize( *this->get_subject(), value );
}

template <typename C>
bool collection_jeason<C>::deserialize( C& collection, std::istream& in )
{
  jeason_input_stream_ptr = &in;
  this->set_subject( &collection );
  
  collection_ifc->reset(*this->get_subject());

  yyparse( this );
  
  jeason_input_stream_ptr = NULL;
  this->set_subject(NULL);
  
  return true;
}

template <typename C>
bool collection_jeason<C>::serialize( const C& c, std::ostream& out) const
{
  bool result = true;
  
  collection_ifc->serialize( c, out );
  
  return result;
}

template <typename C>
value_ifc<C>* collection_jeason<C>::get_collection_ifc()
{
  return collection_ifc;
}


///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C>
object_collection_jeason<C>::object_collection_jeason( 
			     jeason<typename C::value_type>* element_parser ) :
  element_parser( element_parser )
{ 
  element_parser->set_parent(this);
}

template <typename C>
jeason_base* object_collection_jeason<C>::begin_object()
{
  this->get_subject()->insert( this->get_subject()->end(),
			       typename C::value_type() );
  
  element_parser->set_subject( &(this->get_subject()->back()) );
  
  return element_parser;
}

template <typename C>
bool object_collection_jeason<C>::deserialize( C& collection, std::istream& in )
{
  jeason_input_stream_ptr = &in;
  this->set_subject( &collection );
  
  //  this->get_collection_ifc()->reset(*this->get_subject());
  this->get_subject()->clear();

  yyparse( this );
  
  jeason_input_stream_ptr = NULL;
  this->set_subject(NULL);
  
  return true;
}

template <typename C>
bool object_collection_jeason<C>::serialize(const C& c, std::ostream& out) const
{
  bool result = true;
  
  out << "[";

  for ( typename C::const_iterator iter = c.begin();
	iter != c.end();
	++iter )
  {
    if ( iter != c.begin() )
    {
      out << ", ";
    }

    element_parser->serialize(*iter, out);
  }


  out << "]";

  return result;
}

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C>
multidimension_collection_jeason<C>::multidimension_collection_jeason() :
  collection_ifc( value_ifc_builder<C>::build() ),
  element_jeason( jeason_builder<typename C::value_type>::build() )
{ 
  element_jeason->set_parent(this);
}

template <typename C>
jeason_base* multidimension_collection_jeason<C>::begin_array() 
{
  this->get_subject()->insert( this->get_subject()->end(),
			       typename C::value_type() );
  
  element_jeason->set_subject( &(this->get_subject()->back()) );
  
  return element_jeason;
}

template <typename C>
bool multidimension_collection_jeason<C>::deserialize( C& collection, 
						       std::istream& in )
{
  jeason_input_stream_ptr = &in;
  
  collection_ifc->reset(collection);
  
  set_subject( &collection );
  
  yyparse( this );
  
  jeason_input_stream_ptr = NULL;
  this->set_subject(NULL);
  
  return true;
}

template <typename C>
bool multidimension_collection_jeason<C>::serialize( const C& c, 
						     std::ostream& out) const
{
  bool result = true;
  
  collection_ifc->serialize( c, out );
  
  return result;
}

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
object_jeason<T>::object_jeason() :
  members_map()
{ }

template <typename T>
void object_jeason<T>::add_member( const std::string name, 
					   member_ifc<T>* member_ifc )
{
  members_map[name] = member_ifc;
}

template <typename T>
jeason_base* object_jeason<T>::begin_object( const std::string& name )
{
  typename members_map_t::iterator member = members_map.find(name);

  if ( member != members_map.end() )
  {
    member->second->reset( *(this->get_subject()) );
    member->second->set_parser_subject( *(this->get_subject()) );

    // TODO: why does array member not have parent at this point?
    // causing SEGFAULT in unit tests

    return member->second->get_parser();
  }
  else
  {
    // TODO: error checking
    
    return NULL;
  }

}

template <typename T>
jeason_base* object_jeason<T>::begin_array( const std::string& name )
{
  return begin_object(name);
}

template <typename T>
void object_jeason<T>::apply_value( const std::string& name, 
				    const std::string& value )
{
  typename members_map_t::iterator member = members_map.find(name);
  
  if ( member != members_map.end() )
  {
    member->second->reset( *(this->get_subject()) );
    
    member->second->deserialize( *(this->get_subject()), value );
  }

  // TODO: error checking
}

template <typename T>
bool object_jeason<T>::deserialize( T& object, std::istream& in )
{
  jeason_input_stream_ptr = &in;
  this->set_subject( &object );
  
  yyparse( this );
  
  jeason_input_stream_ptr = NULL;
  this->set_subject(NULL);
  
  return true;
}

template <typename T>
bool object_jeason<T>::serialize( const T& t, std::ostream& out ) const
{
  out << "{";
  
  for ( typename members_map_t::const_iterator member = members_map.begin();
	member != members_map.end();
	++member )
  {
    if ( member != members_map.begin() )
    {
      out << ", ";
    }
    
    out << "\"" << member->first << "\"" << ": "; // name
    
    member->second->serialize( t, out ); // value
  }

  out << "}";

  return true;
}


#endif


