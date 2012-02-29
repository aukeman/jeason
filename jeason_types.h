#ifndef JEASON_TYPES_H
#define JEASON_TYPES_H

#include <jeason_base.h>
#include <value_ifc_types.h>
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

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C >
class collection_jeason : public jeason<C>
{
 public:

  collection_jeason();

  void apply_array_element( const std::string& value );

  bool deserialize( C& collection, std::istream& in );
  bool serialize( const C& c, std::ostream& out) const;

 protected:

  value_ifc<C>* get_collection_ifc();

 private: 

  value_ifc<C>* collection_ifc;
};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C >
class object_collection_jeason : public jeason<C>
{
 public:

  object_collection_jeason( jeason<typename C::value_type>* );

  jeason_base* begin_object();

  bool deserialize( C& collection, std::istream& in );
  bool serialize( const C& c, std::ostream& out) const;

 private: 

  jeason<typename C::value_type>* element_parser;
};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename C >
class multidimension_collection_jeason : public jeason<C>
{
 public:

  multidimension_collection_jeason();
  multidimension_collection_jeason( jeason<typename C::value_type>* );

  jeason_base* begin_array();

  bool deserialize( C& collection, std::istream& in );
  bool serialize( const C& c, std::ostream& out) const;

 private: 

  value_ifc<C>* collection_ifc;

  jeason<typename C::value_type>* element_jeason;
};

///////////////////////////////////////////////////////////////////////////////
//
//

template <typename T>
class object_jeason : public jeason<T>
{
  typedef std::map<std::string, member_ifc<T>* > members_map_t;

 public:

  object_jeason();

  virtual void add_member( const std::string name, member_ifc<T>* value_ifc );

  jeason_base* begin_object( const std::string& name );
  jeason_base* begin_array( const std::string& name );

  void apply_value( const std::string& name, const std::string& value );

  bool deserialize( T& object, std::istream& in );
  bool serialize( const T& t, std::ostream& out ) const;

private:

  members_map_t members_map;
};


#endif
