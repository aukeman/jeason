#include <cppunit/extensions/HelperMacros.h>

#include <jeason.h>
#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME simple_object_member_test

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( empty_simple_object_deserialize );
  CPPUNIT_TEST( empty_simple_object_serialize );

  CPPUNIT_TEST( simple_object_deserialize );
  CPPUNIT_TEST( simple_object_serialize );

  CPPUNIT_TEST_SUITE_END();
  
  struct simple_object
  {
    float f;
    
    int i;

    std::string s;
  };

  void empty_simple_object_deserialize()
  {
    jeason<simple_object>* j = jeason<simple_object>::build();

    simple_object so;
    so.f = 99.0f;
    so.i = 99;
    so.s = "99";

    std::stringstream buffer("{}");

    j->deserialize(so, buffer);

    CPPUNIT_ASSERT_EQUAL( 99.0f, so.f );
    CPPUNIT_ASSERT_EQUAL( 99, so.i );
    CPPUNIT_ASSERT_EQUAL( std::string("99"), so.s );

    delete j;
  }


  void empty_simple_object_serialize()
  {
    jeason<simple_object>* j = jeason<simple_object>::build();

    simple_object so;
    so.f = 99.0f;
    so.i = 99;
    so.s = "99";

    std::stringstream buffer;

    j->serialize(so, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("{}"), buffer.str() );

    delete j;
  }

  void simple_object_deserialize()
  {
    jeason<simple_object>* j = jeason<simple_object>::build();

    j->add_member( "f", &simple_object::f );
    j->add_member( "i", &simple_object::i );
    j->add_member( "s", &simple_object::s );

    simple_object so;
    so.f = 99.0f;
    so.i = 99;
    so.s = "99";

    std::stringstream buffer("{ \"f\": 37.5, \"i\": 37, \"s\": \"37\" }");

    j->deserialize(so, buffer);

    CPPUNIT_ASSERT_EQUAL( 37.5f, so.f );
    CPPUNIT_ASSERT_EQUAL( 37, so.i );
    CPPUNIT_ASSERT_EQUAL( std::string("37"), so.s );

    delete j;
  }


  void simple_object_serialize()
  {
    jeason<simple_object>* j = jeason<simple_object>::build();

    j->add_member( "f", &simple_object::f );
    j->add_member( "i", &simple_object::i );
    j->add_member( "s", &simple_object::s );

    simple_object so;
    so.f = 37.5;
    so.i = 37;
    so.s = "37";

    std::stringstream buffer;

    j->serialize(so, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("{\"f\": 37.5, \"i\": 37, \"s\": \"37\"}"), buffer.str() );

    delete j;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

