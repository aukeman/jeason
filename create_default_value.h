#ifndef CREATE_DEFAULT_VALUE_H
#define CREATE_DEFAULT_VALUE_H

template <typename U>
U create_default_value()
{
  return U();
}

template <>
int create_default_value()
{
  return 0;
}

template <>
float create_default_value()
{
  return 0.0f;
}

template <>
double create_default_value()
{
  return 0.0;
}

template<>
bool create_default_value()
{
  return false;
}

template<>
std::string create_default_value()
{
  return std::string("");
}

#endif
