#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Admin.hpp"
#include "Book.hpp"
#include "Exceptions.hpp"
#include "Student.hpp"
#include "System.hpp"
#include "User.hpp"

std::vector<std::shared_ptr<Student>> System::students;
