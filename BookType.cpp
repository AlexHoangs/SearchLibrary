//
// Created by ALEX on 10/4/2021.
//
//
// Created by ALEX on 10/4/2021.
//
#include "BookType.h"

// make it easy on ourselves by making numbering each condition
int condition2(std::string condition)
{
    if (condition == "new")
        return 1;

    if (condition == "used")
        return 2;

    if (condition == "digital")
        return 3;

    return -1;
}

// overload the operator to work with our custom build objects
bool operator<(const BookType& lhs, const BookType& rhs) {
    //convert the condition into a number
    int lhsn = condition2(lhs.condition);
    int rhsn = condition2(rhs.condition);

    // check to see if the isbn is the same
    // if they're not, check to see if lhs is less than rhs
    // if lhs is less than rhs, return false and swap positions
    // else, return true
    if (lhs.isbn != rhs.isbn) {
        return lhs.isbn > rhs.isbn;
    }
    // check to see if the condition is the same
    // if lhsn is less than rhsn, return true
    // else return false and swap positions
    else if (lhsn != rhsn) {
        return lhsn < rhsn;
    }
    // sort by language if everything else is equal
    // compare function compares the strings of the languages
    // return greater than 0 to sort backwards
    // if the two strings are equal it will be equal to 0
    // english and french. e < f so it would return < 0 but we want it to be reversed so
    // we return the comparison to be greater than 0
    else {
        return lhs.language.compare(rhs.language) > 0;
    }
}

// overload the istream operator to work with our custom build objects
std::istream& operator>>(std::istream& in, BookType& rhs) {
    // get the line and parse out the commas
    std::string s;
    std::getline(in, s);
    std::stringstream ss(s);

    char comma;
    // first get the isbn then parse the comma
    ss >> rhs.isbn;
    ss >> comma;

    // then get the language and condition and parse the commas
    std::getline(ss, rhs.language, ',');
    std::getline(ss, rhs.condition, ',');

    return in;
}


