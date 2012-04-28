#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include <string>

#include <stdlib.h>

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
  out = in;

  return true;
}

#endif
