#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

class Book{
    private:
        std::string title;
        std::string author;
        std::string isbn;
        int numberOfPages;
        int amountOwned = 0;

    public:
        Book();
        Book(std::string);
        Book(std::string,std::string,std::string,int);

        bool can_borrow();
		void return_book(int);
        void borrow();

        std::string get_isbn();
        void set_isbn(std::string);
        std::string get_title();
        std::string get_author();
        int get_amount();

        virtual ~Book();

};

#endif
