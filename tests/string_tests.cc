#include <jeason/jeason.h>

#include <cppunit/extensions/HelperMacros.h>

#include <string>
#include <sstream>

#define TEST_NAME string_tests

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( escaped_newline );
  CPPUNIT_TEST( escaped_tab );
  CPPUNIT_TEST( escaped_backspace );
  CPPUNIT_TEST( escaped_formfeed );
  CPPUNIT_TEST( escaped_carriage_return );

  CPPUNIT_TEST( escaped_quote );
  CPPUNIT_TEST( escaped_backslash );
  CPPUNIT_TEST( escaped_forward_slash );

  // TODO: unicode characters!

  CPPUNIT_TEST_SUITE_END();
  

  void escaped_newline()
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

  void escaped_tab()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\tworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\tworld"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\tworld\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_backspace()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\bworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\bworld"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\bworld\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_formfeed()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\fworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\fworld"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\fworld\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_carriage_return()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\rworld");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\rworld"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\rworld\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_quote()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\\"world");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\"world"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\\"world\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_backslash()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\\\world");
    CPPUNIT_ASSERT_EQUAL( std::string("hello\\world"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\\\world\""), test_buffer.str() );

    delete ifc;
  }

  void escaped_forward_slash()
  {
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string s;
    std::stringstream test_buffer;

    ifc->deserialize(s, "hello\\/world");
    CPPUNIT_ASSERT_EQUAL( std::string("hello/world"), s );

    ifc->serialize( s, test_buffer );
    CPPUNIT_ASSERT_EQUAL( std::string("\"hello\\/world\""), test_buffer.str() );

    delete ifc;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

