#include <cppunit/extensions/HelperMacros.h>

#include <value_ifc.h>
#include <value_ifc_builder.h>
#include <string>
#include <sstream>

#include <jeason.h>

#define TEST_NAME value_ifc_tests

class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( integer_deserialize );
  CPPUNIT_TEST( integer_serialize );

  CPPUNIT_TEST( double_deserialize );
  CPPUNIT_TEST( double_serialize );
  
  // CPPUNIT_TEST( float_deserialize );

  CPPUNIT_TEST( string_deserialize );
  CPPUNIT_TEST( string_serialize );

  CPPUNIT_TEST( integer_array_deserialize );
  CPPUNIT_TEST( integer_array_serialize );

  CPPUNIT_TEST( integer_2d_array_deserialize );
  CPPUNIT_TEST( integer_2d_array_serialize );

  CPPUNIT_TEST_SUITE_END();
  

  void integer_deserialize()
  {
    value_ifc<int>* ifc = value_ifc_builder<int>::build();

    int test_int;

#define INT_DESERIALIZE_TEST( v, msg ) \
    ifc->deserialize( test_int, #v ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, (int)v, test_int );

    INT_DESERIALIZE_TEST( -2147483647, "largest negative integer" );
    INT_DESERIALIZE_TEST( -1000, "negative integer" );
    INT_DESERIALIZE_TEST( -1, "negative one" );
    INT_DESERIALIZE_TEST( 0, "zero" );
    INT_DESERIALIZE_TEST( 1, "positive one" );
    INT_DESERIALIZE_TEST( 1000, "positive integer" );
    INT_DESERIALIZE_TEST( 2147483647, "largest positive integer" );
    
    INT_DESERIALIZE_TEST( +500, "positive sign" );

    INT_DESERIALIZE_TEST( 0.0f, "float format input" );
    INT_DESERIALIZE_TEST( 12.0f, "float format input" );
    INT_DESERIALIZE_TEST( 36.4f, "float format input" );
    INT_DESERIALIZE_TEST( -48.6f, "negative float format input" );

    delete ifc;
  }

  void integer_serialize()
  {
    value_ifc<int>* ifc = value_ifc_builder<int>::build();

    std::stringstream test_buffer;

#define INT_SERIALIZE_TEST( v, msg )  \
    ifc->serialize( v, test_buffer ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, std::string(#v), test_buffer.str() ); \
    test_buffer.str("");

    INT_SERIALIZE_TEST( -2147483647, "largest negative integer" );
    INT_SERIALIZE_TEST( -1000, "negative integer" );
    INT_SERIALIZE_TEST( -1, "negative one" );
    INT_SERIALIZE_TEST( 0, "zero" );
    INT_SERIALIZE_TEST( 1, "positive one" );
    INT_SERIALIZE_TEST( 1000, "positive integer" );
    INT_SERIALIZE_TEST( 2147483647, "largest positive integer" );

    delete ifc;
  }

  void double_deserialize()
  { 
    value_ifc<double>* ifc = value_ifc_builder<double>::build();

    double test_double;

#define DOUBLE_DESERIALIZE_TEST( v, msg ) \
    ifc->deserialize( test_double, #v ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, (double)v, test_double );

    DOUBLE_DESERIALIZE_TEST( -1e+37, "largest negative double" );
    DOUBLE_DESERIALIZE_TEST( -1000.125, "negative double" );
    DOUBLE_DESERIALIZE_TEST( -1.0, "negative one" );
    DOUBLE_DESERIALIZE_TEST( 0.0, "zero" );
    DOUBLE_DESERIALIZE_TEST( 1.0, "positive one" );
    DOUBLE_DESERIALIZE_TEST( 1000.875, "positive double" );
    DOUBLE_DESERIALIZE_TEST( 1e+37, "largest positive double" );
    
    DOUBLE_DESERIALIZE_TEST( +500.5, "positive sign" );

    DOUBLE_DESERIALIZE_TEST( 37, "double format" );

    delete ifc;
  }

  void double_serialize()
  {
    value_ifc<double>* ifc = value_ifc_builder<double>::build();

    std::stringstream test_buffer;

#define DOUBLE_SERIALIZE_TEST( v, msg )  \
    ifc->serialize( v, test_buffer ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, std::string(#v), test_buffer.str() ); \
    test_buffer.str("");

    DOUBLE_SERIALIZE_TEST( -1e+37, "largest negative double" );
    DOUBLE_SERIALIZE_TEST( -1000.125, "negative double" );
    DOUBLE_SERIALIZE_TEST( -1, "negative one" );
    DOUBLE_SERIALIZE_TEST( 0, "zero" );
    DOUBLE_SERIALIZE_TEST( 1, "positive one" );
    DOUBLE_SERIALIZE_TEST( 1000.875, "positive double" );
    DOUBLE_SERIALIZE_TEST( 1e+37, "largest positive double" );

    delete ifc;
  }

  void float_deserialize()
  { }

  void string_deserialize()
  { 
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::string test_string;

#define STRING_DESERIALIZE_TEST( v, msg ) \
    ifc->deserialize( test_string, v ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, std::string(v), test_string );

    STRING_DESERIALIZE_TEST( "", "empty string" );
    STRING_DESERIALIZE_TEST( "hello world", "lower case" );
    STRING_DESERIALIZE_TEST( "HELLO WORLD", "upper case" );
    STRING_DESERIALIZE_TEST( "Hello World", "mixed case" );
    // STRING_DESERIALIZE_TEST( "\"hello world\"", "escaped" );
    // STRING_DESERIALIZE_TEST( "hello\nworld", "multi-line" );

    delete ifc;
  }

  void string_serialize()
  { 
    value_ifc<std::string>* ifc = value_ifc_builder<std::string>::build();

    std::stringstream test_buffer;

#define STRING_SERIALIZE_TEST( v, msg )  \
    ifc->serialize( v, test_buffer ); \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, std::string(#v), test_buffer.str() ); \
    test_buffer.str("");

    STRING_SERIALIZE_TEST( "", "empty string" );
    STRING_SERIALIZE_TEST( "hello world", "lower case" );
    STRING_SERIALIZE_TEST( "HELLO WORLD", "upper case" );
    STRING_SERIALIZE_TEST( "Hello World", "mixed case" );
    STRING_SERIALIZE_TEST( "\"hello world\"", "escaped" );
    //        STRING_SERIALIZE_TEST( "hello\nworld", "multi-line" );

    delete ifc;
  }

  void integer_array_deserialize()
  {
    value_ifc<std::vector<int> >* ifc = 
      value_ifc_builder<std::vector<int> >::build();

    std::vector<int> test_collection;

    ifc->reset(test_collection);
    ifc->deserialize(test_collection, "1");
    ifc->deserialize(test_collection, "2");
    ifc->deserialize(test_collection, "3");
    ifc->deserialize(test_collection, "4");

    CPPUNIT_ASSERT_EQUAL( 1, test_collection.at(0) );
    CPPUNIT_ASSERT_EQUAL( 2, test_collection.at(1) );
    CPPUNIT_ASSERT_EQUAL( 3, test_collection.at(2) );
    CPPUNIT_ASSERT_EQUAL( 4, test_collection.at(3) );

    delete ifc;
  }

  void integer_array_serialize()
  {
    value_ifc<std::vector<int> >* ifc = 
      value_ifc_builder<std::vector<int> >::build();

    std::vector<int> test_collection;
    std::stringstream test_buffer;

    ifc->serialize( test_collection, test_buffer );
    
    CPPUNIT_ASSERT_EQUAL( std::string("[]"),
			  test_buffer.str() );
    test_buffer.str("");

    test_collection.push_back(10);
    test_collection.push_back(9);
    test_collection.push_back(8);
    test_collection.push_back(7);


    ifc->serialize( test_collection, test_buffer );

    CPPUNIT_ASSERT_EQUAL( test_buffer.str(), 
			  std::string("[10, 9, 8, 7]") );

    delete ifc;
  }

  void integer_2d_array_deserialize()
  {
    value_ifc<std::vector<std::vector<int> > >* ifc = 
      value_ifc_builder<std::vector<std::vector<int> > >::build();

    std::vector<int> inner_test_collection_1;
    std::vector<int> inner_test_collection_2;

    std::vector<std::vector<int> > outer_test_collection;

    ifc->reset(outer_test_collection);
    // ifc->deserialize(inner_test_collection_1, "1");
    // ifc->deserialize(inner_test_collection_2, "2");
    // ifc->deserialize(inner_test_collection_3, "3");
    // ifc->deserialize(inner_test_collection_4, "4");

    // ifc->deserialize(inner_test_collection_1, "1");
    // ifc->deserialize(inner_test_collection_2, "2");
    // ifc->deserialize(inner_test_collection_3, "3");
    // ifc->deserialize(inner_test_collection_4, "4");


    // CPPUNIT_ASSERT_EQUAL( 1, test_collection.at(0) );
    // CPPUNIT_ASSERT_EQUAL( 2, test_collection.at(1) );
    // CPPUNIT_ASSERT_EQUAL( 3, test_collection.at(2) );
    // CPPUNIT_ASSERT_EQUAL( 4, test_collection.at(3) );

    delete ifc;
  }

  void integer_2d_array_serialize()
  {
    value_ifc<std::vector<std::vector<int> > >* ifc = 
      value_ifc_builder<std::vector<std::vector<int> > >::build();

    std::vector<int> inner_test_collection_1;
    std::vector<int> inner_test_collection_2;

    inner_test_collection_1.push_back(1);
    inner_test_collection_1.push_back(2);
    inner_test_collection_1.push_back(3);
    inner_test_collection_1.push_back(4);

    inner_test_collection_2.push_back(7);
    inner_test_collection_2.push_back(8);
    inner_test_collection_2.push_back(9);
    inner_test_collection_2.push_back(10);

    std::vector<std::vector<int> > outer_test_collection;
    outer_test_collection.push_back( inner_test_collection_1 );
    outer_test_collection.push_back( inner_test_collection_2 );

    std::stringstream test_buffer;

    ifc->serialize( outer_test_collection, test_buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1, 2, 3, 4], [7, 8, 9, 10]]"), 
			  test_buffer.str() );

    delete ifc;
  }


};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

