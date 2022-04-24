#include "doctest.h"
#include <memory>
#include "Exceptions.hpp"

TEST_CASE("caso base"){

     CHECK_THROWS_AS(throw InvalidIdException(), InvalidIdException);
}

TEST_CASE("caso base"){

     CHECK_THROWS_AS(throw InvalidBookException(), InvalidBookException);
}

TEST_CASE("caso base"){

     CHECK_THROWS_AS(throw EmptyBook(), EmptyBook);
}
