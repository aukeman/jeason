#ifndef JEASON_IMPL_VALUE_IFC_H
#define JEASON_IMPL_VALUE_IFC_H

#include <jeason/impl/jeason_base.h>

#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
class value_ifc
{
public:

  virtual bool reset( T& ) const = 0;

  virtual bool serialize( const T&, std::ostream& ) const = 0;

  virtual bool deserialize( T&, const std::string& ) const = 0;

  virtual jeason_base* get_parser();

};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
class simple_scalar_ifc : public value_ifc<T>
{
 public:

  simple_scalar_ifc();

  virtual bool reset( T& value ) const;

  virtual bool serialize( const T& object, std::ostream& out) const;

  virtual bool deserialize( T& value, const std::string& in ) const;
};



///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C>
class collection_ifc : public value_ifc<C>
{
 public:

  collection_ifc( value_ifc<typename C::value_type>* element_ifc );

  virtual bool reset( C& collection ) const;

  virtual bool serialize( const C& collection, std::ostream& out) const;

  virtual bool deserialize( C& collection, const std::string& in ) const;

 private:
  
  value_ifc<typename C::value_type>* element_ifc;
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T>
class member_ifc : public value_ifc<T>
{
 public:

  virtual bool set_parser_subject( T& ) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
class scalar_member_ifc : public member_ifc<T>
{
public:

  scalar_member_ifc( U T::*member_ptr );

  virtual bool reset( T& value ) const;

  virtual bool serialize( const T& value, std::ostream& out) const;

  virtual bool deserialize( T& value, const std::string& in ) const;

  virtual bool set_parser_subject( T& );

 private:

  U T::*member_ptr;

};

///////////////////////////////////////////////////////////////////////////////
//
//

template<typename T, typename U>
class object_member_ifc : public member_ifc<T>
{
public:

  object_member_ifc( U T::*member_ptr, jeason_base* parser );

  virtual bool reset( T& object ) const;

  virtual bool set_parser_subject( T& object );

  virtual bool serialize( const T& value, std::ostream& out) const;

  virtual bool deserialize( T& value, const std::string& in ) const;

  virtual jeason_base* get_parser();

 private:

  U T::*member_ptr;

  jeason_base* parser;

};



#endif
