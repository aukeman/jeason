#include <cppunit/extensions/HelperMacros.h>

#include <jeason.h>
#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME object_array_tests

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( object_deserialize );
  CPPUNIT_TEST( object_serialize );

  CPPUNIT_TEST_SUITE_END();
  
  struct object
  {
    int i;

    std::vector<int> v;
  };

  void object_deserialize()
  {
    jeason<object>* element_parser = jeason<object>::build();

    element_parser->add_member( "i", &object::i );
    element_parser->add_member( "v", &object::v );
    
    jeason<std::vector<object> >* j = jeason<std::vector<object> >::build(element_parser);

    std::vector<object> object_vector;
    object_vector.push_back( object() );

    object_vector.back().i = 0;
    object_vector.back().v.push_back(0);
    object_vector.back().v.push_back(0);

    object_vector.push_back( object() );

    object_vector.back().i = 0;
    object_vector.back().v.push_back(0);
    object_vector.back().v.push_back(0);

    std::stringstream buffer("[{ \"i\": 1, \"v\": [ 2, 3 ] }, "
			     " { \"i\": 3, \"v\": [ 4, 5, 6 ] }, "
			     " { \"i\": 7, \"v\": [ 8 ] }]");

    j->deserialize(object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( size_t(3), object_vector.size() );


    CPPUNIT_ASSERT_EQUAL( 1, object_vector.at(0).i );

    CPPUNIT_ASSERT_EQUAL( size_t(2), object_vector.at(0).v.size() );
    CPPUNIT_ASSERT_EQUAL( 2, object_vector.at(0).v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 3, object_vector.at(0).v.at(1) );


    CPPUNIT_ASSERT_EQUAL( 3, object_vector.at(1).i );

    CPPUNIT_ASSERT_EQUAL( size_t(3), object_vector.at(1).v.size() );
    CPPUNIT_ASSERT_EQUAL( 4, object_vector.at(1).v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 5, object_vector.at(1).v.at(1) );
    CPPUNIT_ASSERT_EQUAL( 6, object_vector.at(1).v.at(2) );


    CPPUNIT_ASSERT_EQUAL( 7, object_vector.at(2).i );

    CPPUNIT_ASSERT_EQUAL( size_t(1), object_vector.at(2).v.size() );
    CPPUNIT_ASSERT_EQUAL( 8, object_vector.at(2).v.at(0) );

    delete j;
  }


  void object_serialize()
  {
    jeason<object>* element_parser = jeason<object>::build();

    element_parser->add_member( "i", &object::i );
    element_parser->add_member( "v", &object::v );
    
    jeason<std::vector<object> >* j = jeason<std::vector<object> >::build(element_parser);

    std::vector<object> object_vector;

    object_vector.push_back( object() );

    object_vector.back().i = 1;
    object_vector.back().v.push_back(2);
    object_vector.back().v.push_back(3);

    object_vector.push_back( object() );

    object_vector.back().i = 4;
    object_vector.back().v.push_back(5);
    
    std::stringstream buffer;

    j->serialize(object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("[{\"i\": 1, \"v\": [2, 3]}, {\"i\": 4, \"v\": [5]}]"), buffer.str() );

    delete j;
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

