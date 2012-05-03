#include <cppunit/extensions/HelperMacros.h>

#include <jeason.h>
#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME nested_object_member_test

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( object_deserialize );
  CPPUNIT_TEST( object_serialize );

  CPPUNIT_TEST_SUITE_END();
  
  struct inner_object
  {
    std::string a;

    std::string b;
  };

  struct outer_object
  {
    float f;
    
    int i;

    std::string s;

    std::vector<int> v;

    inner_object inner;
  };

  void object_deserialize()
  {
    jeason<inner_object>* inner_parser = jeason<inner_object>::build();

    inner_parser->add_member( "a", &inner_object::a );
    inner_parser->add_member( "b", &inner_object::b );

    jeason<outer_object>* j = jeason<outer_object>::build();

    j->add_member( "f", &outer_object::f );
    j->add_member( "i", &outer_object::i );
    j->add_member( "s", &outer_object::s );
    j->add_member( "v", &outer_object::v );

    j->add_member( "inner", &outer_object::inner, inner_parser );

    
    outer_object o;
    o.f = 99.0f;
    o.i = 99;
    o.s = "99";

    o.v.push_back(7);
    o.v.push_back(8);
    o.v.push_back(9);

    o.inner.a = "hello";
    o.inner.b = "world";
    
    std::stringstream buffer("{ \"f\": 37.5, \"i\": 37, \"s\": \"37\", \"v\": [ 3, 7 ],  \"inner\": { \"a\": \"3\", \"b\": \"7\" } }");

    j->deserialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( 37.5f, o.f );
    CPPUNIT_ASSERT_EQUAL( 37, o.i );
    CPPUNIT_ASSERT_EQUAL( std::string("37"), o.s );

    CPPUNIT_ASSERT_EQUAL( size_t(2), o.v.size() );
    CPPUNIT_ASSERT_EQUAL( 3, o.v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 7, o.v.at(1) );

    CPPUNIT_ASSERT_EQUAL( std::string("3"), o.inner.a );
    CPPUNIT_ASSERT_EQUAL( std::string("7"), o.inner.b );

    delete j;
  }


  void object_serialize()
  {
    jeason<inner_object>* inner_parser = jeason<inner_object>::build();

    inner_parser->add_member( "a", &inner_object::a );
    inner_parser->add_member( "b", &inner_object::b );

    jeason<outer_object>* j = jeason<outer_object>::build();

    j->add_member( "f", &outer_object::f );
    j->add_member( "i", &outer_object::i );
    j->add_member( "s", &outer_object::s );

    j->add_member( "v", &outer_object::v );

    j->add_member( "inner", &outer_object::inner, inner_parser );

    outer_object o;
    o.f = 37.5;
    o.i = 37;
    o.s = "37";
    
    o.v.push_back(3);
    o.v.push_back(7);

    o.inner.a = "3";
    o.inner.b = "7";

    std::stringstream buffer;

    j->serialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("{\"f\": 37.5, \"i\": 37, \"inner\": {\"a\": \"3\", \"b\": \"7\"}, \"s\": \"37\", \"v\": [3, 7]}"), buffer.str() );

    delete j;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

