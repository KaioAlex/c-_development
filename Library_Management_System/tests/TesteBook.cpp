#include "doctest.h"
#include <memory>
#include "Book.hpp"

TEST_CASE("Construtor padrão"){
     std::shared_ptr<Book> b (new Book());
     b->set_isbn("123456789-0");

     CHECK(b->get_isbn() == "123456789-0");
}

TEST_CASE("Construtor personalizado"){
     std::shared_ptr<Book> b (new Book("ola", "caio", "12345",10));

     CHECK(b->get_title() == "ola");
}

TEST_CASE("Caso Base = checando isbn do livro"){
    std::shared_ptr<Book> b (new Book("12345"));

    b->return_book(2014343432);

    CHECK(b->get_isbn() == "12345");
}

TEST_CASE("método can_borrow"){
     std::shared_ptr<Book> b (new Book("ola", "caio", "12345",0));

     CHECK(b->can_borrow() == 0);
}
