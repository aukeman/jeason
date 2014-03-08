#include <jeason/jeason.h>

#include <cppunit/extensions/HelperMacros.h>

#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME object_array_tests

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( deserialize_empty );
  CPPUNIT_TEST( deserialize_single );
  CPPUNIT_TEST( deserialize_multiple );

  CPPUNIT_TEST( serialize_empty );
  CPPUNIT_TEST( serialize_single );
  CPPUNIT_TEST( serialize_multiple );


  CPPUNIT_TEST_SUITE_END();
  
  struct test_object
  {
    int i;

    std::vector<int> v;
  };

  jeason<std::vector<test_object> >* j;

public:

  TEST_NAME()
    :j(NULL)
  {
    jeason<test_object>* element_parser = jeason<test_object>::build();

    element_parser->add_member( "i", &test_object::i );
    element_parser->add_member( "v", &test_object::v );
    
    this->j = jeason<std::vector<test_object> >::build(element_parser);
  }

  ~TEST_NAME()
  {
    delete this->j;
  }

  void deserialize_multiple()
  {

    std::vector<test_object> test_object_vector;
    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 0;
    test_object_vector.back().v.push_back(0);
    test_object_vector.back().v.push_back(0);

    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 0;
    test_object_vector.back().v.push_back(0);
    test_object_vector.back().v.push_back(0);

    std::stringstream buffer("[{ \"i\": 1, \"v\": [ 2, 3 ] }, "
			     " { \"i\": 3, \"v\": [ 4, 5, 6 ] }, "
			     " { \"i\": 7, \"v\": [ 8 ] }]");

    this->j->deserialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( size_t(3), test_object_vector.size() );


    CPPUNIT_ASSERT_EQUAL( 1, test_object_vector.at(0).i );

    CPPUNIT_ASSERT_EQUAL( size_t(2), test_object_vector.at(0).v.size() );
    CPPUNIT_ASSERT_EQUAL( 2, test_object_vector.at(0).v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 3, test_object_vector.at(0).v.at(1) );


    CPPUNIT_ASSERT_EQUAL( 3, test_object_vector.at(1).i );

    CPPUNIT_ASSERT_EQUAL( size_t(3), test_object_vector.at(1).v.size() );
    CPPUNIT_ASSERT_EQUAL( 4, test_object_vector.at(1).v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 5, test_object_vector.at(1).v.at(1) );
    CPPUNIT_ASSERT_EQUAL( 6, test_object_vector.at(1).v.at(2) );


    CPPUNIT_ASSERT_EQUAL( 7, test_object_vector.at(2).i );

    CPPUNIT_ASSERT_EQUAL( size_t(1), test_object_vector.at(2).v.size() );
    CPPUNIT_ASSERT_EQUAL( 8, test_object_vector.at(2).v.at(0) );
  }

  void deserialize_single()
  {
    std::vector<test_object> test_object_vector;
    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 0;
    test_object_vector.back().v.push_back(0);
    test_object_vector.back().v.push_back(0);

    std::stringstream buffer("[{ \"i\": 1, \"v\": [ 2 ] }]");

    this->j->deserialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( size_t(1), test_object_vector.size() );

    CPPUNIT_ASSERT_EQUAL( 1, test_object_vector.at(0).i );

    CPPUNIT_ASSERT_EQUAL( size_t(1), test_object_vector.at(0).v.size() );
    CPPUNIT_ASSERT_EQUAL( 2, test_object_vector.at(0).v.at(0) );
  }

  void deserialize_empty()
  {
    std::vector<test_object> test_object_vector;
    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 0;
    test_object_vector.back().v.push_back(0);
    test_object_vector.back().v.push_back(0);

    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 0;
    test_object_vector.back().v.push_back(0);
    test_object_vector.back().v.push_back(0);

    std::stringstream buffer("[]");

    this->j->deserialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( size_t(0), test_object_vector.size() );

  }

  void serialize_multiple()
  {
    std::vector<test_object> test_object_vector;

    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 1;
    test_object_vector.back().v.push_back(2);
    test_object_vector.back().v.push_back(3);

    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 4;
    test_object_vector.back().v.push_back(5);
    
    std::stringstream buffer;

    this->j->serialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("[{\"i\": 1, \"v\": [2, 3]}, {\"i\": 4, \"v\": [5]}]"), buffer.str() );

  }

  void serialize_single()
  {
    std::vector<test_object> test_object_vector;

    test_object_vector.push_back( test_object() );

    test_object_vector.back().i = 1;
    test_object_vector.back().v.push_back(2);

    std::stringstream buffer;

    this->j->serialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("[{\"i\": 1, \"v\": [2]}]"), 
			  buffer.str() );
  }

  void serialize_empty()
  {
    std::vector<test_object> test_object_vector;

    std::stringstream buffer;

    this->j->serialize(test_object_vector, buffer);

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

