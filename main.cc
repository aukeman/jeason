#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <set>

#include <stdlib.h>

#include <jeason.h>

struct inner_struct_t
{
  bool d;
  bool e;
};

struct test_struct_t
{
  int a;
  float b;
  std::string c;

  inner_struct_t inner_struct;

  std::vector<std::vector<std::vector<int> > > f;
};

int main()
{
  //  vector_jeason<int> jeason;

  // typedef std::vector<int> inner_collection_t;
  // typedef std::vector<inner_collection_t> collection_t;
  // typedef std::vector<collection_t> outer_collection_t;

  // outer_collection_t test_collection;

  // jeason<outer_collection_t>* serializer = jeason<outer_collection_t>::build();

  // std::stringstream test_stream;
  // test_stream << "[ [ [10, 9, 8], [7, 6, 5], [4, 3, 2, 1] ], [ [1,2], [3,4] ] ]";

  // serializer->deserialize( test_collection, test_stream );

  // serializer->serialize( test_collection, std::cout );

  // delete serializer;


  std::stringstream test_stream;
  // test_stream << "{ \"a\": 1, \"b\": 99.9, \"c\": \"hello_world\", \"inner_struct\": { \"d\": true, \"e\": false }, \"f\": [ [ [1, 2], [3, 4] ], [ [6, 7, 8], [9], [] ] ] }";

  // jeason<inner_struct_t>* inner_struct_serializer = jeason<inner_struct_t>::build();

  // inner_struct_serializer->add_member( "d", &inner_struct_t::d );
  // inner_struct_serializer->add_member( "e", &inner_struct_t::e );

  // jeason<test_struct_t>* serializer = jeason<test_struct_t>::build();

  // serializer->add_member( "a", &test_struct_t::a );
  // serializer->add_member( "b", &test_struct_t::b );
  // serializer->add_member( "c", &test_struct_t::c );
  // serializer->add_member( "inner_struct", &test_struct_t::inner_struct, inner_struct_serializer );
  // serializer->add_member( "f", &test_struct_t::f );
  

  // test_struct_t test_struct;
  // serializer->deserialize( test_struct, test_stream );

  // serializer->serialize( test_struct, std::cout );
    
  test_stream << "[ {\"d\": true, \"e\": false}, {\"d\": false, \"e\": true} ]";

  jeason<inner_struct_t>* inner_struct_parser = jeason<inner_struct_t>::build();

  inner_struct_parser->add_member( "d", &inner_struct_t::d );
  inner_struct_parser->add_member( "e", &inner_struct_t::e );

  typedef std::vector<inner_struct_t> inner_struct_collection_t;

  jeason<inner_struct_collection_t>* serializer = 
    jeason<inner_struct_collection_t>::build( inner_struct_parser );

  inner_struct_collection_t c;
  serializer->deserialize( c, test_stream );

  serializer->serialize( c, std::cout );

  return 0;
}
