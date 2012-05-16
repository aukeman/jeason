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
