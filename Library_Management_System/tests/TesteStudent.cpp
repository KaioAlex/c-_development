#include "doctest.h"
#include <memory>
#include "Student.hpp"
#include "System.hpp"

TEST_CASE("caso base = checando matricula de student"){
    std::shared_ptr<Student> s (new Student(12345, "Kaio"));

    remove("Alunos//12345.txt");
    
    CHECK(s->get_id() == 12345);
}
