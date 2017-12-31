// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#define CATCH_CONFIG_RUNNER
#include "../../dependencies/catch.hpp"


int main( int argc, char* argv[] ) {
  int result = Catch::Session().run( argc, argv );
  std::cin.get();
  return result;
}

TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" ) {
}