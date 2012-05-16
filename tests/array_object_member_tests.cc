#include <cppunit/extensions/HelperMacros.h>

#include <jeason/jeason.h>

#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME array_object_member_test

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( object_deserialize );
  CPPUNIT_TEST( object_serialize );

  CPPUNIT_TEST_SUITE_END();
  
  struct object_with_collection
  {
    float f;
    
    int i;

    std::string s;

    std::vector<int> v;
  };

  void object_deserialize()
  {
    jeason<object_with_collection>* j = jeason<object_with_collection>::build();

    j->add_member( "f", &object_with_collection::f );
    j->add_member( "i", &object_with_collection::i );
    j->add_member( "s", &object_with_collection::s );
    j->add_member( "v", &object_with_collection::v );

    object_with_collection o;
    o.f = 99.0f;
    o.i = 99;
    o.s = "99";

    o.v.push_back(7);
    o.v.push_back(8);
    o.v.push_back(9);

    std::stringstream buffer("{ \"f\": 37.5, \"i\": 37, \"s\": \"37\", \"v\": [ 3, 7 ] }");

    j->deserialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( 37.5f, o.f );
    CPPUNIT_ASSERT_EQUAL( 37, o.i );
    CPPUNIT_ASSERT_EQUAL( std::string("37"), o.s );

    CPPUNIT_ASSERT_EQUAL( size_t(2), o.v.size() );
    CPPUNIT_ASSERT_EQUAL( 3, o.v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 7, o.v.at(1) );

    delete j;
  }


  void object_serialize()
  {
    jeason<object_with_collection>* j = jeason<object_with_collection>::build();

    j->add_member( "f", &object_with_collection::f );
    j->add_member( "i", &object_with_collection::i );
    j->add_member( "s", &object_with_collection::s );

    j->add_member( "v", &object_with_collection::v );

    object_with_collection o;
    o.f = 37.5;
    o.i = 37;
    o.s = "37";
    
    o.v.push_back(3);
    o.v.push_back(7);

    std::stringstream buffer;

    j->serialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("{\"f\": 37.5, \"i\": 37, \"s\": \"37\", \"v\": [3, 7]}"), buffer.str() );

    delete j;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

