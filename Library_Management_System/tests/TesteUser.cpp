#include "doctest.h"
#include <memory>
#include "User.hpp"

TEST_CASE("caso base = checando nome user"){
    std::shared_ptr<User> u (new User("caio"));

    CHECK(u->get_name() == "caio");
}
