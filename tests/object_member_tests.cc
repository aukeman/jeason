#include <cppunit/extensions/HelperMacros.h>

#include <jeason.h>
#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME object_member_test

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

    std::vector<int> v1;

    inner_object inner1;

    std::vector<int> v2;

    inner_object inner2;
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
    j->add_member( "v1", &outer_object::v1 );
    j->add_member( "inner1", &outer_object::inner1, inner_parser );
    j->add_member( "v2", &outer_object::v2 );
    j->add_member( "inner2", &outer_object::inner2, inner_parser );
    
    outer_object o;
    o.f = 99.0f;
    o.i = 99;
    o.s = "99";

    o.v1.push_back(7);
    o.v1.push_back(8);
    o.v1.push_back(9);

    o.inner1.a = "hello";
    o.inner1.b = "world";

    o.v2.push_back(-1);
    o.v2.push_back(-1);
    o.v2.push_back(-1);

    o.inner2.a = "abc";
    o.inner2.b = "xyz";

    std::stringstream buffer("{ \"i\": 37, \"s\": \"37\", \"f\": 37.5, \"v1\": [ 3, 7 ],  \"inner1\": { \"a\": \"3\", \"b\": \"7\" }, \"v2\": [7, 3, 5], \"inner2\": { \"a\": \"7\", \"b\": \"3\" } }");

    j->deserialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( 37.5f, o.f );
    CPPUNIT_ASSERT_EQUAL( 37, o.i );
    CPPUNIT_ASSERT_EQUAL( std::string("37"), o.s );

    CPPUNIT_ASSERT_EQUAL( size_t(2), o.v1.size() );
    CPPUNIT_ASSERT_EQUAL( 3, o.v1.at(0) );
    CPPUNIT_ASSERT_EQUAL( 7, o.v1.at(1) );

    CPPUNIT_ASSERT_EQUAL( std::string("3"), o.inner1.a );
    CPPUNIT_ASSERT_EQUAL( std::string("7"), o.inner1.b );

    CPPUNIT_ASSERT_EQUAL( size_t(3), o.v2.size() );
    CPPUNIT_ASSERT_EQUAL( 7, o.v2.at(0) );
    CPPUNIT_ASSERT_EQUAL( 3, o.v2.at(1) );
    CPPUNIT_ASSERT_EQUAL( 5, o.v2.at(2) );

    CPPUNIT_ASSERT_EQUAL( std::string("7"), o.inner2.a );
    CPPUNIT_ASSERT_EQUAL( std::string("3"), o.inner2.b );

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

    j->add_member( "v1", &outer_object::v1 );

    j->add_member( "inner1", &outer_object::inner1, inner_parser );

    j->add_member( "v2", &outer_object::v2 );

    j->add_member( "inner2", &outer_object::inner2, inner_parser );

    outer_object o;
    o.f = 37.5;
    o.i = 37;
    o.s = "37";
    
    o.v1.push_back(3);
    o.v1.push_back(7);

    o.inner1.a = "3";
    o.inner1.b = "7";

    o.v2.push_back(7);
    o.v2.push_back(3);
    o.v2.push_back(5);

    o.inner2.a = "7";
    o.inner2.b = "3";

    std::stringstream buffer;

    j->serialize(o, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("{\"f\": 37.5, \"i\": 37, \"inner1\": {\"a\": \"3\", \"b\": \"7\"}, \"inner2\": {\"a\": \"7\", \"b\": \"3\"}, \"s\": \"37\", \"v1\": [3, 7], \"v2\": [7, 3, 5]}"), buffer.str() );

    delete j;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

