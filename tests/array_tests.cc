#include <cppunit/extensions/HelperMacros.h>

#include <jeason/jeason.h>

#include <string>
#include <sstream>

#include <vector>

#define TEST_NAME array_tests

static const char* empty_collection_strings[] = { "[]", 
						  " []", 
						  "[] ", 
						  " [ ]", 
						  "[ ] ", 
						  " [ ] ", 
						  " [    ] ",
						  "     [          ]      ",
						  "[\n]",
						  "\n[\n]\n",
						  NULL };


class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( empty_vector_deserialize );
  CPPUNIT_TEST( empty_vector_serialize );

  CPPUNIT_TEST( empty_list_deserialize );
  CPPUNIT_TEST( empty_list_serialize );

  CPPUNIT_TEST( empty_deque_deserialize );
  CPPUNIT_TEST( empty_deque_serialize );

  CPPUNIT_TEST( integer_vector_deserialize );
  CPPUNIT_TEST( integer_vector_serialize );

  CPPUNIT_TEST( integer_list_deserialize );
  CPPUNIT_TEST( integer_list_serialize );

  CPPUNIT_TEST( integer_deque_deserialize );
  CPPUNIT_TEST( integer_deque_serialize );

  CPPUNIT_TEST( string_vector_deserialize );
  CPPUNIT_TEST( string_vector_serialize );


  CPPUNIT_TEST_SUITE_END();

  typedef jeason<std::vector<int> >         int_vector_jeason;
  typedef jeason<std::list<int> >           int_list_jeason;
  typedef jeason<std::deque<int> >          int_deque_jeason;

  typedef jeason<std::vector<std::string> >         string_vector_jeason;


  // EMPTY VECTOR ///////////////////////////////////////////////////
  
  void empty_vector_deserialize()
  {
    int_vector_jeason* j = int_vector_jeason::build();
				  
    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      std::vector<int> v;
      v.push_back(1);
      v.push_back(2);

      std::stringstream buffer(*iter);

      j->deserialize( v, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), v.size() );

    }

    delete j;
  }

  void empty_vector_serialize()
  {
    int_vector_jeason* j = int_vector_jeason::build();

    std::vector<int> v;
    std::stringstream buffer("");

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // EMPTY LIST ///////////////////////////////////////////////////

  void empty_list_deserialize()
  {
    int_list_jeason* j = int_list_jeason::build();

    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      std::list<int> l;
      l.push_back(1);
      l.push_back(2);

      std::stringstream buffer(*iter);

      j->deserialize( l, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), l.size() );

    }

    delete j;
  }

  void empty_list_serialize()
  {
    int_list_jeason* j = int_list_jeason::build();

    std::list<int> l;
    std::stringstream buffer("");

    j->serialize( l, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // EMPTY DEQUE ///////////////////////////////////////////////////

  void empty_deque_deserialize()
  {
    int_deque_jeason* j = int_deque_jeason::build();

    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      std::deque<int> d;
      d.push_back(1);
      d.push_back(2);

      std::stringstream buffer(*iter);

      j->deserialize( d, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), d.size() );

    }

    delete j;
  }

  void empty_deque_serialize()
  {
    int_deque_jeason* j = int_deque_jeason::build();

    std::deque<int> d;
    std::stringstream buffer("");

    j->serialize( d, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // INTEGER VECTOR ///////////////////////////////////////////////////

  void integer_vector_deserialize()
  {
    int_vector_jeason* j = int_vector_jeason::build();

    std::vector<int> v;

    std::stringstream buffer;
    buffer << "[ 1, 2, 3, 4, 5 ]";

    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(5), v.size()  );

    CPPUNIT_ASSERT_EQUAL( 1, v.at(0) );
    CPPUNIT_ASSERT_EQUAL( 2, v.at(1) );
    CPPUNIT_ASSERT_EQUAL( 3, v.at(2) );
    CPPUNIT_ASSERT_EQUAL( 4, v.at(3) );
    CPPUNIT_ASSERT_EQUAL( 5, v.at(4) );

    delete j;
  }

  void integer_vector_serialize()
  {
    int_vector_jeason* j = int_vector_jeason::build();

    std::vector<int> v;
    v.push_back(1);

    std::stringstream buffer;

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1]"), buffer.str() );

    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    buffer.str("");

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1, 2, 3, 4, 5]"), buffer.str() );

    delete j;
  }

  // INTEGER LIST ///////////////////////////////

  void integer_list_deserialize()
  {
    int_list_jeason* j = int_list_jeason::build();

    std::list<int> l;

    std::stringstream buffer;
    buffer << "[ 1, 2, 3, 4, 5 ]";

    j->deserialize( l, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(5), l.size()  );

    int idx = 1;
    for ( std::list<int>::iterator iter = l.begin();
	  iter != l.end();
	  ++iter, ++idx )
    {
      CPPUNIT_ASSERT_EQUAL( idx, *iter );
    }

    delete j;
  }

  void integer_list_serialize()
  {
    int_list_jeason* j = int_list_jeason::build();

    std::list<int> l;
    l.push_back(1);

    std::stringstream buffer;

    j->serialize( l, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1]"), buffer.str() );

    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    buffer.str("");

    j->serialize( l, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1, 2, 3, 4, 5]"), buffer.str() );

    delete j;
  }

  // INTEGER DEQUE ///////////////////////////////

  void integer_deque_deserialize()
  {
    int_deque_jeason* j = int_deque_jeason::build();

    std::deque<int> d;

    std::stringstream buffer;
    buffer << "[ 1, 2, 3, 4, 5 ]";

    j->deserialize( d, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(5), d.size()  );

    int idx = 1;
    for ( std::deque<int>::iterator iter = d.begin();
	  iter != d.end();
	  ++iter, ++idx )
    {
      CPPUNIT_ASSERT_EQUAL( idx, *iter );
    }

    delete j;
  }

  void integer_deque_serialize()
  {
    int_deque_jeason* j = int_deque_jeason::build();

    std::deque<int> d;
    d.push_back(1);

    std::stringstream buffer;

    j->serialize( d, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1]"), buffer.str() );

    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    d.push_back(5);

    buffer.str("");

    j->serialize( d, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[1, 2, 3, 4, 5]"), buffer.str() );

    delete j;
  }

  // STRING VECTOR ///////////////////////////////////////////////////

  void string_vector_deserialize()
  {
    string_vector_jeason* j = string_vector_jeason::build();

    std::vector<std::string> v;

    std::stringstream buffer;
    buffer << "[ \"a\", \"\", \" \", \"hello world\", \"hello world\" ]";

    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(5), v.size()  );

    CPPUNIT_ASSERT_EQUAL( std::string("a"), v.at(0) );
    CPPUNIT_ASSERT_EQUAL( std::string(""), v.at(1) );
    CPPUNIT_ASSERT_EQUAL( std::string(" "), v.at(2) );
    CPPUNIT_ASSERT_EQUAL( std::string("hello world"), v.at(3) );
    CPPUNIT_ASSERT_EQUAL( std::string("hello world"), v.at(4) );

    delete j;
  }

  void string_vector_serialize()
  {
    string_vector_jeason* j = string_vector_jeason::build();

    std::vector<std::string> v;
    v.push_back("x");

    std::stringstream buffer;

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[\"x\"]"), buffer.str() );

    v.push_back("");
    v.push_back(" ");
    v.push_back("hello world");
    v.push_back("hello world");

    buffer.str("");

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[\"x\", \"\", \" \", \"hello world\", \"hello world\"]"), buffer.str() );

    delete j;
  }


};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

