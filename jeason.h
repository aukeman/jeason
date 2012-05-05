#ifndef JEASON_H
#define JEASON_H

#include <jeason_base.h>
#include <value_ifc.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
class jeason : public jeason_base
{
 public:

  jeason();

  jeason_base* get_parent();
  void set_parent( jeason_base* );

  T* get_subject();
  void set_subject(T*);

  virtual bool deserialize( T&, std::istream& in )=0;
  virtual bool serialize( const T&, std::ostream& out ) const=0;

  template <typename U>
  void add_member( const std::string& name, U T::*member_ptr );

  template <typename U>
  void add_member(const std::string& name, U T::*member_ptr, jeason<U>* parser);

  virtual void add_member( const std::string name, member_ifc<T>* );

  void apply_value( const std::string&, const std::string& value );
  void apply_array_element( const std::string& value );

  jeason_base* begin_object();
  jeason_base* begin_object( const std::string& name );
  jeason_base* end_object();

  jeason_base* begin_array();
  jeason_base* begin_array( const std::string& name );
  jeason_base* end_array();

  static jeason<T>* build();

  template <typename U>
  static jeason<T>* build( jeason<U>* element_parser );

protected:

 private:

  T* subject;

  jeason_base* parent;

};

#include <concrete_jeason_types.inl>
#include <jeason_definitions.inl>
#include <value_ifc_definitions.inl>

#endif
