#include <jeason/jeason.h>

#include <cppunit/extensions/HelperMacros.h>

#include <string>
#include <sstream>

#include <vector>

#define TEST_NAME whitspace_tests

static const char* whitespace_strings[] = { "", 
					    " ", 
					    " ", 
					    "\t", 
					    "\t\t", 
					    "\n", 
					    "\n\n",
					    "\n\t\n",
					    "\n \n\t\n",
					    NULL };


class TEST_NAME : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TEST_NAME );

  CPPUNIT_TEST( empty_int_array_whitespace_test );
  CPPUNIT_TEST( single_int_array_whitespace_test );
  CPPUNIT_TEST( multiple_int_array_whitespace_test );

  CPPUNIT_TEST( empty_str_array_whitespace_test );
  CPPUNIT_TEST( single_str_array_whitespace_test );
  CPPUNIT_TEST( multiple_str_array_whitespace_test );

  CPPUNIT_TEST( object_whitespace_test );

  CPPUNIT_TEST_SUITE_END();

  struct test_object
  {
    int i;
    
    float f;

    std::string s;
  };

  typedef jeason<std::vector<int> >         int_vector_jeason;
  typedef jeason<std::vector<std::string> > str_vector_jeason;

  typedef jeason<test_object>               test_object_jeason;

  int_vector_jeason* j_int_vector;
  str_vector_jeason* j_str_vector;
  test_object_jeason* j_test_object;;

public:

  TEST_NAME()
    :j_int_vector(int_vector_jeason::build()),
     j_str_vector(str_vector_jeason::build()),
     j_test_object(test_object_jeason::build())
  {
    j_test_object->add_member( "i", &test_object::i );
    j_test_object->add_member( "f", &test_object::f );
    j_test_object->add_member( "s", &test_object::s );
  }

  ~TEST_NAME()
  {
    delete j_int_vector;
    delete j_str_vector;
    delete j_test_object;
  }

  void empty_int_array_whitespace_test()
  {
    for ( size_t pre_ws_idx = 0;
	  whitespace_strings[pre_ws_idx] != NULL;
	  ++pre_ws_idx )
    {
      for ( size_t ws_idx = 0;
	    whitespace_strings[ws_idx] != NULL;
	    ++ws_idx )
      {
	for ( size_t post_ws_idx = 0;
	      whitespace_strings[post_ws_idx] != NULL;
	      ++post_ws_idx )
	{
	  std::vector<int> int_vector;
	  int_vector.push_back(1);
	  int_vector.push_back(2);
	  int_vector.push_back(3);
	  
	  std::stringstream buffer;
	  buffer << whitespace_strings[pre_ws_idx] 
		 << "[" << whitespace_strings[ws_idx] << "]"
		 << whitespace_strings[post_ws_idx];

	  j_int_vector->deserialize( int_vector, buffer );

	  char msg[512];
	  snprintf( msg, 
		    512, 
		    "pre_ws_idx: %ul, ws_idx: %ul, post_ws_idx: %ul",
		    pre_ws_idx,
		    ws_idx,
		    post_ws_idx);

	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(0), int_vector.size() );
	}
      }
    }
  }

  void single_int_array_whitespace_test()
  {
    for ( size_t pre_ws_idx = 0;
	  whitespace_strings[pre_ws_idx] != NULL;
	  ++pre_ws_idx )
    {
      for ( size_t post_ws_idx = 0;
	    whitespace_strings[post_ws_idx] != NULL;
	    ++post_ws_idx )
      {
	std::vector<int> int_vector;
	int_vector.push_back(1);
	int_vector.push_back(2);
	int_vector.push_back(3);
	  
	std::stringstream buffer;
	buffer << "[" << whitespace_strings[pre_ws_idx] 
	       << "9"
	       << whitespace_strings[post_ws_idx] << "]";

	j_int_vector->deserialize( int_vector, buffer );
	  
	char msg[512];
	snprintf( msg, 
		  512, 
		  "pre_ws_idx: %ul, post_ws_idx: %ul",
		  pre_ws_idx,
		  post_ws_idx);

	CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(1), int_vector.size() );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 9, int_vector.at(0) );
      }
    }
  }

  void multiple_int_array_whitespace_test()
  {
    for ( size_t ws_idx_1 = 0;
	  whitespace_strings[ws_idx_1] != NULL;
	  ++ws_idx_1 )
    {
      for ( size_t ws_idx_2 = 0;
	    whitespace_strings[ws_idx_2] != NULL;
	    ++ws_idx_2 )
      {
	for ( size_t ws_idx_3 = 0;
	      whitespace_strings[ws_idx_3] != NULL;
	      ++ws_idx_3 )
	{
	  for ( size_t ws_idx_4 = 0;
		whitespace_strings[ws_idx_4] != NULL;
		++ws_idx_4 )
	    {
	      std::vector<int> int_vector;
	      int_vector.push_back(1);
	      int_vector.push_back(2);
	      int_vector.push_back(3);
	  
	      std::stringstream buffer;
	      buffer << "[" << whitespace_strings[ws_idx_1] 
		     << "8" << whitespace_strings[ws_idx_2]
		     << "," << whitespace_strings[ws_idx_3]
		     << "9" << whitespace_strings[ws_idx_4]
		     << "]";

	      j_int_vector->deserialize( int_vector, buffer );

	      char msg[512];
	      snprintf( msg, 
			512, 
			"ws_idx_1: %ul, "
			"ws_idx_2: %ul, "
			"ws_idx_3: %ul, "
			"ws_idx_4: %ul",
			ws_idx_1,
			ws_idx_2,
			ws_idx_3,
			ws_idx_4 );

	      CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(2), int_vector.size() );
	      CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 8, int_vector.at(0) );
	      CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 9, int_vector.at(1) );
	    }
	}
      }
    }
  }

  void empty_str_array_whitespace_test()
  {
    for ( size_t pre_ws_idx = 0;
	  whitespace_strings[pre_ws_idx] != NULL;
	  ++pre_ws_idx )
    {
      for ( size_t ws_idx = 0;
	    whitespace_strings[ws_idx] != NULL;
	    ++ws_idx )
      {
	for ( size_t post_ws_idx = 0;
	      whitespace_strings[post_ws_idx] != NULL;
	      ++post_ws_idx )
	{
	  std::vector<std::string> str_vector;
	  str_vector.push_back("a");
	  str_vector.push_back("b");
	  str_vector.push_back("c");
	  
	  std::stringstream buffer;
	  buffer << whitespace_strings[pre_ws_idx] 
		 << "[" << whitespace_strings[ws_idx] << "]"
		 << whitespace_strings[post_ws_idx];

	  j_str_vector->deserialize( str_vector, buffer );

	  char msg[512];
	  snprintf( msg, 
		    512, 
		    "pre_ws_idx: %ul, ws_idx: %ul, post_ws_idx: %ul",
		    pre_ws_idx,
		    ws_idx,
		    post_ws_idx);

	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(0), str_vector.size() );
	}
      }
    }
  }

  void single_str_array_whitespace_test()
  {
    for ( size_t pre_ws_idx = 0;
	  whitespace_strings[pre_ws_idx] != NULL;
	  ++pre_ws_idx )
    {
      for ( size_t str_ws_idx = 0;
	    whitespace_strings[str_ws_idx] != NULL;
	    ++str_ws_idx )
      {
	for ( size_t post_ws_idx = 0;
	      whitespace_strings[post_ws_idx] != NULL;
	      ++post_ws_idx )
	{
	  std::vector<std::string> str_vector;
	  str_vector.push_back(std::string("a"));
	  str_vector.push_back(std::string("b"));
	  str_vector.push_back(std::string("c"));
	  
	  std::stringstream buffer;
	  buffer << "[" << whitespace_strings[pre_ws_idx] 
		 << "\"" << whitespace_strings[str_ws_idx] << "\""
		 << whitespace_strings[post_ws_idx] << "]";

	  j_str_vector->deserialize( str_vector, buffer );
	  
	  char msg[512];
	  snprintf( msg, 
		    512, 
		    "pre_ws_idx: %ul, str_ws_idx: %ul, post_ws_idx: %ul",
		    pre_ws_idx,
		    str_ws_idx,
		    post_ws_idx);

	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(1), str_vector.size() );
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 
					std::string(whitespace_strings[str_ws_idx]), 
					str_vector.at(0) );
	}
      }
    }
  }

  void multiple_str_array_whitespace_test()
  {
    for ( size_t pre_ws_idx = 0;
	  whitespace_strings[pre_ws_idx] != NULL;
	  ++pre_ws_idx )
    {
      for ( size_t str_ws_idx = 0;
	    whitespace_strings[str_ws_idx] != NULL;
	    ++str_ws_idx )
      {
	for ( size_t post_ws_idx = 0;
	      whitespace_strings[post_ws_idx] != NULL;
	      ++post_ws_idx )
	{
	  std::vector<std::string> str_vector;
	  str_vector.push_back(std::string("a"));
	  str_vector.push_back(std::string("b"));
	  str_vector.push_back(std::string("c"));
	  
	  std::stringstream buffer;
	  buffer << "[" << whitespace_strings[pre_ws_idx] 
		 << "\"" << whitespace_strings[str_ws_idx] << "\""
		 << "," << whitespace_strings[post_ws_idx] 
		 << "\"" << whitespace_strings[str_ws_idx] << "\""
		 << whitespace_strings[post_ws_idx] << "]";

	  j_str_vector->deserialize( str_vector, buffer );
	  
	  char msg[512];
	  snprintf( msg, 
		    512, 
		    "pre_ws_idx: %ul, str_ws_idx: %ul, post_ws_idx: %ul",
		    pre_ws_idx,
		    str_ws_idx,
		    post_ws_idx);

	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, size_t(2), str_vector.size() );
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 
					std::string(whitespace_strings[str_ws_idx]), 
					str_vector.at(0) );
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 
					std::string(whitespace_strings[str_ws_idx]), 
					str_vector.at(1) );
	}
      }
    }
  }

  void object_whitespace_test()
  {
    for ( size_t ws_idx_1 = 0;
	  whitespace_strings[ws_idx_1] != NULL;
	  ++ws_idx_1 )
    {
      for ( size_t ws_idx_2 = 0;
	    whitespace_strings[ws_idx_2] != NULL;
	    ++ws_idx_2 )
      {
	for ( size_t ws_idx_3 = 0;
	      whitespace_strings[ws_idx_3] != NULL;
	      ++ws_idx_3 )
	{
	  test_object o;
	  o.i = 999;
	  o.f = 999.9f;
	  o.s = "999";
	  
	  std::stringstream buffer;
	  buffer << whitespace_strings[ws_idx_1] << "{"
		 << whitespace_strings[ws_idx_2] << "\"i\"" 
		 << whitespace_strings[ws_idx_3] << ":" 
		 << whitespace_strings[ws_idx_1] << "1"
		 << whitespace_strings[ws_idx_2] << ","
		 << whitespace_strings[ws_idx_3] << "\"f\""
		 << whitespace_strings[ws_idx_1] << ":"
		 << whitespace_strings[ws_idx_2] << "2.0"
		 << whitespace_strings[ws_idx_3] << ","
		 << whitespace_strings[ws_idx_1] << "\"s\""
		 << whitespace_strings[ws_idx_2] << ":"
		 << whitespace_strings[ws_idx_3] << "\"three   four\""
		 << whitespace_strings[ws_idx_1] << "}"
		 << whitespace_strings[ws_idx_2];
 
	  j_test_object->deserialize( o, buffer );

	  char msg[512];
	  snprintf( msg, 
		    512, 
		    "ws_idx_1: %ul, ws_idx_2: %ul, ws_idx_3: %ul",
		    ws_idx_1,
		    ws_idx_2,
		    ws_idx_3);

	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 1, o.i );
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, 2.0f, o.f );
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( msg, std::string("three   four"), o.s );
	}
      }
    }
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TEST_NAME );

