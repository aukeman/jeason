#ifndef JEASON_IMPL_PARSE_INPUT_H
#define JEASON_IMPL_PARSE_INPUT_H

#include <string>
#include <stdlib.h>
#include <sstream>

template <typename U>
bool parse_input( const std::string& in, U& )
{
  // TODO: error checking

  return false;
}

template <> inline
bool parse_input( const std::string& in, bool& out )
{
  if ( in == "true" )
  {
    out = true;
    return true;
  }
  else if ( in == "false" )
  {
    out = false;
    return true;
  }
  else
  {
    out = false;
    return false;
  }
}

template <> inline
bool parse_input( const std::string& in, int& out )
{
  out = atoi(in.c_str());

  return true;
}

template <> inline
bool parse_input( const std::string& in, float& out )
{
  out = (float)atof(in.c_str());

  return true;
}

template <> inline
bool parse_input( const std::string& in, double& out )
{
  out = atof(in.c_str());

  return true;
}

template <> inline
bool parse_input( const std::string& in, std::string& out )
{
  out = "";

  std::stringstream in_stream(in);
  std::stringstream out_stream("");

  char c = in_stream.get();
  while ( in_stream.good() )
  {
    if ( c == '\\' )
    {
      c = in_stream.get();
      if ( in_stream.good() )
      {
	switch ( c )
	{
	case 'n':
	  c = '\n';
	  break;
	  
	case 't':
	  c = '\t';
	  break;

	case 'b':
	  c = '\b';
	  break;

	case 'f':
	  c = '\f';
	  break;

	case 'r':
	  c = '\r';
	  break;
	}
      }
    }

    if ( in_stream.good() )
    {
      out_stream << c;
      c = in_stream.get();
    }
  }

  out = out_stream.str();

  return true;
}

#endif
