#ifndef GENERATE_OUTPUT_H
#define GENERATE_OUTPUT_H

#include <ostream>
#include <string>

#include <limits>

#include <sstream>

template <typename U>
bool generate_output( const U& in, std::ostream& out )
{
  out << in;

  return true;
}

template <> inline
bool generate_output( const bool& in, std::ostream& out )
{
  static const std::string TRUE_STRING("true");
  static const std::string FALSE_STRING("false");

  out << ( in ? TRUE_STRING : FALSE_STRING );

  return true;
}

template <> inline
bool generate_output( const double& in, std::ostream& out )
{
  std::streamsize old_precision = 
    out.precision( std::numeric_limits<double>::digits10 );

  out << in;

  out.precision( old_precision );

  return true;
}

template <> inline
bool generate_output( const float& in, std::ostream& out )
{
  std::streamsize old_precision = 
    out.precision( std::numeric_limits<float>::digits10 );

  out << in;

  out.precision( old_precision );

  return true;
}

template <> inline
bool generate_output( const std::string& in, std::ostream& out )
{
  out << "\"";

  std::stringstream stream(in);

  char c = stream.get();
  while ( stream.good() )
  {
    switch ( c )
    {
    case '\\':
    case '\"':
    case '/':
    case '\b':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
      out << '\\';
    }

    switch ( c )
    {
    case '\b':
      out << 'b';
      break;

    case '\f':
      out << 'f';
      break;

    case '\n':
      out << 'n';
      break;

    case '\r':
      out << 'r';
      break;
      
    case '\t':
      out << 't';
      break;

    default:
      out << c;
    }

    c = stream.get();
  }

  out << "\"";
}

#endif
