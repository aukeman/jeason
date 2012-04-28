#ifndef CREATE_DEFAULT_VALUE_H
#define CREATE_DEFAULT_VALUE_H

template <typename U>
U create_default_value()
{
  return U();
}

template <> inline
int create_default_value()
{
  return 0;
}

template <> inline
float create_default_value()
{
  return 0.0f;
}

template <> inline
double create_default_value()
{
  return 0.0;
}

template<> inline
bool create_default_value()
{
  return false;
}

template<> inline
std::string create_default_value()
{
  return std::string("");
}

#endif
