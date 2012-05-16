#ifndef JEASON_IMPL_JEASON_BASE_H
#define JEASON_IMPL_JEASON_BASE_H

#include <string>
#include <istream>

class jeason_base
{
 public:

  virtual jeason_base* begin_object()=0;
  virtual jeason_base* begin_object( const std::string& name )=0;
  virtual jeason_base* end_object()=0;

  virtual void apply_value( const std::string& name, 
			    const std::string& value )=0;

  virtual jeason_base* begin_array()=0;
  virtual jeason_base* begin_array( const std::string& name )=0;
  virtual jeason_base* end_array()=0;

  virtual void apply_array_element( const std::string& )=0;

};

#endif
