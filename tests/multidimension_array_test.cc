#include <cppunit/extensions/HelperMacros.h>

#include <jeason.h>
#include <string>
#include <sstream>

#include <vector>

#include <test_util.h>

#define TEST_NAME multidimension_array_tests

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

  CPPUNIT_TEST( integer_vector_deserialize_3d );
  CPPUNIT_TEST( integer_vector_serialize_3d );

  CPPUNIT_TEST( integer_vector_deserialize_4d );
  CPPUNIT_TEST( integer_vector_serialize_4d );


  CPPUNIT_TEST_SUITE_END();

  typedef std::vector<std::vector<int> > int_vector_2d;
  typedef jeason<int_vector_2d> int_vector_2d_jeason;

  typedef std::list<std::list<int> > int_list_2d;
  typedef jeason<int_list_2d >     int_list_2d_jeason;

  typedef std::deque<std::deque<int> > int_deque_2d;
  typedef jeason<int_deque_2d>   int_deque_2d_jeason;

  typedef std::vector<std::vector<std::vector<int> > > int_vector_3d;
  typedef jeason<int_vector_3d> int_vector_3d_jeason;

  typedef std::vector<std::vector<std::vector<std::vector<int> > > > int_vector_4d;
  typedef jeason<int_vector_4d> int_vector_4d_jeason;


  // EMPTY VECTOR ///////////////////////////////////////////////////
  
  void empty_vector_deserialize()
  {
    int_vector_2d_jeason* j = int_vector_2d_jeason::build();
				  
    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      int_vector_2d v;
      v.push_back(std::vector<int>());
      v.push_back(std::vector<int>());

      std::stringstream buffer(*iter);

      j->deserialize( v, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), v.size() );

    }

    delete j;
  }

  void empty_vector_serialize()
  {
    int_vector_2d_jeason* j = int_vector_2d_jeason::build();

    int_vector_2d v;
    std::stringstream buffer("");

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // EMPTY LIST ///////////////////////////////////////////////////

  void empty_list_deserialize()
  {
    int_list_2d_jeason* j = int_list_2d_jeason::build();

    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      int_list_2d l;
      l.push_back(std::list<int>());
      l.push_back(std::list<int>());

      std::stringstream buffer(*iter);

      j->deserialize( l, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), l.size() );

    }

    delete j;
  }

  void empty_list_serialize()
  {
    int_list_2d_jeason* j = int_list_2d_jeason::build();

    int_list_2d l;
    std::stringstream buffer("");

    j->serialize( l, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // EMPTY DEQUE ///////////////////////////////////////////////////

  void empty_deque_deserialize()
  {
    int_deque_2d_jeason* j = int_deque_2d_jeason::build();

    for ( const char** iter = empty_collection_strings;
	  *iter != NULL;
	  ++iter )
    {
      int_deque_2d d;
      d.push_back(std::deque<int>());
      d.push_back(std::deque<int>());

      std::stringstream buffer(*iter);

      j->deserialize( d, buffer );

      CPPUNIT_ASSERT_EQUAL_MESSAGE( *iter, size_t(0), d.size() );

    }

    delete j;
  }

  void empty_deque_serialize()
  {
    int_deque_2d_jeason* j = int_deque_2d_jeason::build();

    int_deque_2d d;
    std::stringstream buffer("");

    j->serialize( d, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[]"), buffer.str() );
    
    delete j;
  }

  // // INTEGER VECTOR ///////////////////////////////////////////////////

  void integer_vector_deserialize()
  {
    int_vector_2d_jeason* j = int_vector_2d_jeason::build();

    int_vector_2d v;

    std::stringstream buffer;
    buffer << "[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]";

    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.size()  );
    
    CPPUNIT_ASSERT_EQUAL( size_t(5), v.at(0).size() );

    CPPUNIT_ASSERT_EQUAL( 1, v.at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 2, v.at(0).at(1) );
    CPPUNIT_ASSERT_EQUAL( 3, v.at(0).at(2) );
    CPPUNIT_ASSERT_EQUAL( 4, v.at(0).at(3) );
    CPPUNIT_ASSERT_EQUAL( 5, v.at(0).at(4) );

    CPPUNIT_ASSERT_EQUAL( 6, v.at(1).at(0) );
    CPPUNIT_ASSERT_EQUAL( 7, v.at(1).at(1) );
    CPPUNIT_ASSERT_EQUAL( 8, v.at(1).at(2) );
    CPPUNIT_ASSERT_EQUAL( 9, v.at(1).at(3) );
    CPPUNIT_ASSERT_EQUAL( 10, v.at(1).at(4) );

    delete j;
  }

  void integer_vector_serialize()
  {
    int_vector_2d_jeason* j = int_vector_2d_jeason::build();

    std::vector<int> a;
    a.push_back(1);

    int_vector_2d v;
    v.push_back(a);

    std::stringstream buffer;

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1]]"), buffer.str() );

    std::vector<int> b;
    b.push_back(6);

    v.push_back(b);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1], [6]]"), buffer.str() );

    v.at(0).push_back(2);
    v.at(0).push_back(3);
    v.at(0).push_back(4);
    v.at(0).push_back(5);

    v.at(1).push_back(7);
    v.at(1).push_back(8);
    v.at(1).push_back(9);
    v.at(1).push_back(10);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]"), buffer.str() );

    delete j;
  }

  // // INTEGER LIST ///////////////////////////////////////////////////

  void integer_list_deserialize()
  {
    using test_util::get_item;

    int_list_2d_jeason* j = int_list_2d_jeason::build();

    int_list_2d v;

    std::stringstream buffer;
    buffer << "[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]";

    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.size()  );
    
    CPPUNIT_ASSERT_EQUAL( size_t(5), get_item(v, 0).size() );

    std::list<int>& first = get_item(v, 0);
    std::list<int>& second = get_item(v, 1);
    

    CPPUNIT_ASSERT_EQUAL( 1, get_item(first, 0) );
    CPPUNIT_ASSERT_EQUAL( 2, get_item(first, 1) );
    CPPUNIT_ASSERT_EQUAL( 3, get_item(first, 2) );
    CPPUNIT_ASSERT_EQUAL( 4, get_item(first, 3) );
    CPPUNIT_ASSERT_EQUAL( 5, get_item(first, 4) );

    CPPUNIT_ASSERT_EQUAL( 6, get_item(second, 0) );
    CPPUNIT_ASSERT_EQUAL( 7, get_item(second, 1) );
    CPPUNIT_ASSERT_EQUAL( 8, get_item(second, 2) );
    CPPUNIT_ASSERT_EQUAL( 9, get_item(second, 3) );
    CPPUNIT_ASSERT_EQUAL( 10, get_item(second, 4) );

    delete j;
  }

  void integer_list_serialize()
  {
    using test_util::get_item;

    int_list_2d_jeason* j = int_list_2d_jeason::build();

    std::list<int> a;
    a.push_back(1);

    int_list_2d v;
    v.push_back(a);

    std::stringstream buffer;

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1]]"), buffer.str() );

    std::list<int> b;
    b.push_back(6);

    v.push_back(b);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1], [6]]"), buffer.str() );

    get_item(v, 0).push_back(2);
    get_item(v, 0).push_back(3);
    get_item(v, 0).push_back(4);
    get_item(v, 0).push_back(5);

    get_item(v, 1).push_back(7);
    get_item(v, 1).push_back(8);
    get_item(v, 1).push_back(9);
    get_item(v, 1).push_back(10);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]"), buffer.str() );

    delete j;
  }

  // // INTEGER DEQUE ///////////////////////////////////////////////////

  void integer_deque_deserialize()
  {
    using test_util::get_item;

    int_deque_2d_jeason* j = int_deque_2d_jeason::build();

    int_deque_2d v;

    std::stringstream buffer;
    buffer << "[ [ 1, 2, 3, 4, 5 ], [ 6, 7, 8, 9, 10 ] ]";

    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.size()  );
    
    CPPUNIT_ASSERT_EQUAL( size_t(5), get_item(v, 0).size() );

    std::deque<int>& first = get_item(v, 0);
    std::deque<int>& second = get_item(v, 1);
    

    CPPUNIT_ASSERT_EQUAL( 1, get_item(first, 0) );
    CPPUNIT_ASSERT_EQUAL( 2, get_item(first, 1) );
    CPPUNIT_ASSERT_EQUAL( 3, get_item(first, 2) );
    CPPUNIT_ASSERT_EQUAL( 4, get_item(first, 3) );
    CPPUNIT_ASSERT_EQUAL( 5, get_item(first, 4) );

    CPPUNIT_ASSERT_EQUAL( 6, get_item(second, 0) );
    CPPUNIT_ASSERT_EQUAL( 7, get_item(second, 1) );
    CPPUNIT_ASSERT_EQUAL( 8, get_item(second, 2) );
    CPPUNIT_ASSERT_EQUAL( 9, get_item(second, 3) );
    CPPUNIT_ASSERT_EQUAL( 10, get_item(second, 4) );

    delete j;
  }

  void integer_deque_serialize()
  {
    using test_util::get_item;

    int_deque_2d_jeason* j = int_deque_2d_jeason::build();

    std::deque<int> a;
    a.push_back(1);

    int_deque_2d v;
    v.push_back(a);

    std::stringstream buffer;

    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1]]"), buffer.str() );

    std::deque<int> b;
    b.push_back(6);

    v.push_back(b);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1], [6]]"), buffer.str() );

    get_item(v, 0).push_back(2);
    get_item(v, 0).push_back(3);
    get_item(v, 0).push_back(4);
    get_item(v, 0).push_back(5);

    get_item(v, 1).push_back(7);
    get_item(v, 1).push_back(8);
    get_item(v, 1).push_back(9);
    get_item(v, 1).push_back(10);

    buffer.str("");
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]"), buffer.str() );

    delete j;
  }

  // // INTEGER VECTOR 3D /////////////////////////////////////////////////

  void integer_vector_deserialize_3d()
  {
    int_vector_3d_jeason* j = int_vector_3d_jeason::build();

    int_vector_3d v;

    std::stringstream buffer;
    buffer << "[[[1, 2], [3, 4], [5]], [[6, 7, 8], [], [9, 10]]]";
                
    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.size()  );
    
    CPPUNIT_ASSERT_EQUAL( size_t(3), v.at(0).size() );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(1).size() );
    CPPUNIT_ASSERT_EQUAL( size_t(1), v.at(0).at(2).size() );

    CPPUNIT_ASSERT_EQUAL( size_t(3), v.at(1).size() );

    CPPUNIT_ASSERT_EQUAL( size_t(3), v.at(1).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( size_t(0), v.at(1).at(1).size() );
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(1).at(2).size() );
    
    CPPUNIT_ASSERT_EQUAL( 1, v.at(0).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 2, v.at(0).at(0).at(1) );

    CPPUNIT_ASSERT_EQUAL( 3, v.at(0).at(1).at(0) );
    CPPUNIT_ASSERT_EQUAL( 4, v.at(0).at(1).at(1) );

    CPPUNIT_ASSERT_EQUAL( 5, v.at(0).at(2).at(0) );

    CPPUNIT_ASSERT_EQUAL( 6, v.at(1).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 7, v.at(1).at(0).at(1) );
    CPPUNIT_ASSERT_EQUAL( 8, v.at(1).at(0).at(2) );

    CPPUNIT_ASSERT_EQUAL( 9, v.at(1).at(2).at(0) );
    CPPUNIT_ASSERT_EQUAL( 10, v.at(1).at(2).at(1) );

    delete j;
  }

  void integer_vector_serialize_3d()
  {
    int_vector_3d_jeason* j = int_vector_3d_jeason::build();

    std::vector<int> a, b, c, d, e;
    a.push_back(1);
    a.push_back(2);

    b.push_back(3);
    b.push_back(4);

    c.push_back(5);

    d.push_back(6);
    d.push_back(7);
    d.push_back(8);
    
    e.push_back(9);
    e.push_back(10);

    int_vector_2d first, second;

    first.push_back(a);
    first.push_back(b);
    first.push_back(c);

    second.push_back(d);
    second.push_back( std::vector<int>() );
    second.push_back(e);

    int_vector_3d v;

    v.push_back(first);
    v.push_back(second);

    std::stringstream buffer;
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[[1, 2], [3, 4], [5]], [[6, 7, 8], [], [9, 10]]]"), buffer.str() );

    delete j;
  }

  // // INTEGER VECTOR 4D /////////////////////////////////////////////////

  void integer_vector_deserialize_4d()
  {
    int_vector_4d_jeason* j = int_vector_4d_jeason::build();

    int_vector_4d v;

    std::stringstream buffer;
    buffer << "[[[[1, 2], [3, 4]], [[5, 6]]], [[[7, 8]], [[9, 10]]]]";
                
    j->deserialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.size()  );
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).size() );
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(0).size() );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(0).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( 1, v.at(0).at(0).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 2, v.at(0).at(0).at(0).at(1) );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(0).at(1).size() );
    CPPUNIT_ASSERT_EQUAL( 3, v.at(0).at(0).at(1).at(0) );
    CPPUNIT_ASSERT_EQUAL( 4, v.at(0).at(0).at(1).at(1) );

    CPPUNIT_ASSERT_EQUAL( size_t(1), v.at(0).at(1).size() );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(0).at(1).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( 5, v.at(0).at(1).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 6, v.at(0).at(1).at(0).at(1) );

    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(1).size() );
    
    CPPUNIT_ASSERT_EQUAL( size_t(1), v.at(1).at(0).size() );
    
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(1).at(0).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( 7, v.at(1).at(0).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 8, v.at(1).at(0).at(0).at(1) );

    CPPUNIT_ASSERT_EQUAL( size_t(1), v.at(1).at(1).size() );
    
    CPPUNIT_ASSERT_EQUAL( size_t(2), v.at(1).at(1).at(0).size() );
    CPPUNIT_ASSERT_EQUAL( 9, v.at(1).at(1).at(0).at(0) );
    CPPUNIT_ASSERT_EQUAL( 10, v.at(1).at(1).at(0).at(1) );

    delete j;
  }

  void integer_vector_serialize_4d()
  {
    int_vector_4d_jeason* j = int_vector_4d_jeason::build();

    std::vector<int> a, b, c, d, e;
    a.push_back(1);
    a.push_back(2);

    b.push_back(3);
    b.push_back(4);

    c.push_back(5);
    c.push_back(6);

    d.push_back(7);
    d.push_back(8);
    
    e.push_back(9);
    e.push_back(10);

    int_vector_2d a1, a2, b1, b2;
    a1.push_back(a);
    a1.push_back(b);

    a2.push_back(c);

    b1.push_back(d);
    
    b2.push_back(e);

    int_vector_3d first, second;

    first.push_back(a1);
    first.push_back(a2);

    second.push_back(b1);
    second.push_back(b2);

    int_vector_4d v;

    v.push_back(first);
    v.push_back(second);

    std::stringstream buffer;
    j->serialize( v, buffer );

    CPPUNIT_ASSERT_EQUAL( std::string("[[[[1, 2], [3, 4]], [[5, 6]]], [[[7, 8]], [[9, 10]]]]"), buffer.str() );

    delete j;
  }


};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

