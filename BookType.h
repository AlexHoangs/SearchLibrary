//
// Created by ALEX on 10/4/2021.
//

#ifndef SEARCHNEWBOOKS_BOOKTYPE_H
#define SEARCHNEWBOOKS_BOOKTYPE_H

#include <iostream>
#include <sstream>
#include <tuple>


//BookType holds the isbn, language, and condition of book
class BookType {

public:
    //isbn number, language, and condition of book for us to access
    int isbn;
    std::string language;
    std::string condition;

    // friend to allow functions to access private
    // overload the insertion operator
    // overload the < operator
    friend std::istream& operator>>(std::istream& in, BookType& rhs);
    friend bool operator<(const BookType& lhs, const BookType& rhs);
};

#endif //SEARCHNEWBOOKS_BOOKTYPE_H
