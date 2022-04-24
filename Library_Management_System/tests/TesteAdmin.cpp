#include "doctest.h"
#include <memory>
#include "Admin.hpp"

TEST_CASE("Caso Base = checando senha admin"){
    std::shared_ptr<Admin> a (new Admin("Caio", "12345"));

    CHECK(a->get_password() == "12345");
}
