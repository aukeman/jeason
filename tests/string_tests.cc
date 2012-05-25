#include <jeason/jeason.h>

#include <cppunit/extensions/HelperMacros.h>

#include <string>
#include <sstream>

#define TEST_NAME string_tests

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( escaped_newlines );

  CPPUNIT_TEST_SUITE_END();
  

  void escaped_newlines()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize( s, "hello\\nworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\nworld"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\nworld\""), test_buffer.str() );
      
    ifc->deserialize( s, "hello\\\\nworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\\nworld"), s );

    delete ifc;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

