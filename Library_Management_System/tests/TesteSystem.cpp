#include "doctest.h"
#include <memory>
#include "System.hpp"

TEST_CASE("caso base = tamanho lista de Adminstradores"){
    System::init_list();
    int size = System::get_admin_size();

    CHECK(size == 2);
}

TEST_CASE(""){
    System::login();
    System::init_students();

    CHECK(System::borrow_book()==0);
}

TEST_CASE("Método .get_book()"){
    System::init_students();
    std::shared_ptr<Book> b (System::get_book("682-9-10-537778-6",0));

    CHECK(b->get_isbn() == "682-9-10-537778-6");
}

TEST_CASE("Método .return_book()"){
    System::init_students();

    CHECK(System::return_book()==0);
}

TEST_CASE("Método .show_menu()"){
    CHECK(System::show_menu()==0);
}

TEST_CASE(""){
     CHECK(System::show_adm_menu()==0);
}
