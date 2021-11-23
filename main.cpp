#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "BookType.h"
#include "Timer.h"

int binarySearch(std::vector<BookType>& newLibrary, std::vector<BookType>& requestedLibrary, int& count)
{
    // time the binary search function
    Timer timer;

    // sort both vectors by isbn, then condition, then language backwards (alphabet backwards)
    std::sort(newLibrary.begin(), newLibrary.end());

    // range based to loop for number of requested books
    for (int bookNum = 0; bookNum < (int)requestedLibrary.size(); bookNum++)
    {
        int rhs = (newLibrary.size()-1);
        int lhs = 0;

        while (lhs <= rhs)
            {
                // constant cut in half after each iteration until no other books are found
                int mid = (rhs + lhs)/2;

                // check to see if there are any matching books
                if (requestedLibrary[bookNum].isbn == newLibrary[mid].isbn &&
                    requestedLibrary[bookNum].language == newLibrary[mid].language &&
                    requestedLibrary[bookNum].condition == newLibrary[mid].condition) {
                    count += 1;
                    break;
                }
                // if the book is greater than the middle, search the right side
                if (newLibrary[mid] < requestedLibrary[bookNum]) {
                    lhs = mid + 1;
                }
                // else, search the left side
                else {
                    rhs = mid - 1;
                }
            }
    }
    return count;
}

int linearSearch(std::vector<BookType>& newLibrary, std::vector<BookType>& requestedLibrary, int& count)
{
    // time the linear search function
    Timer timer;

    // use nested for loop to compare each requested book with all the new books
    for (int i = 0; i < (int)newLibrary.size(); i++)
    {
        for (int j = 0; j < (int)requestedLibrary.size(); j++)
        {
            //check to see if the book is the same,then add 1
            if (requestedLibrary[j].isbn == newLibrary[i].isbn &&
            requestedLibrary[j].condition == newLibrary[i].condition &&
            requestedLibrary[j].language == newLibrary[i].language) { count += 1; }
            else { continue; }
        }
    }
    return count;
}

void parseBooks(const std::string newBooks, const std::string request, std::vector<BookType>& newLibrary, std::vector<BookType>& requestedLibrary)
{
    // created a variable "B" to pass configuration data into vector
    // open if stream to act as buffer to push back config data from new books into vector
    BookType B;
    std::ifstream configNew(newBooks);

    while (configNew >> B) {
        newLibrary.push_back(B);
    }

    //same concept as above^
    std::ifstream configRequest(request);

    while (configRequest >> B) {
        requestedLibrary.push_back(B);
    }
}

int main(int argc, char** argv)
{
    // check to see if enough arguments were inputted
    if (argc < 4) {
        std::cerr << "Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>" << std::endl;
        exit(0);
    }
    // check to see if the files can be opened. If not, print error messages
    std::fstream file;
    for (int i = 1; i < argc; i++) {
        file.open(argv[i]);
        if (file.is_open()) {
            file.close();

        }
        else {
            std::cerr << "Error: cannot open file " << argv[i] << std::endl;
            exit(0);
        }
    }

    // create 2 vectors to store the new books and the requested books
    std::vector<BookType> newLibrary;
    std::vector<BookType> requestedLibrary;

    //call the function parseBooks to push back config data into vectors
    parseBooks(argv[1], argv[2], newLibrary, requestedLibrary);

    //ask user for choice of search method
    std::string userInput;

    std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;

    //loop until acceptable choice is inputted by the user
    while (true) {
        std::getline(std::cin, userInput);
        if (userInput == "l" || userInput == "b")
            break;
        std::cerr << "Incorrect choice" << std::endl;
    }

    int count = 0;

    //pass all vectors and count by reference to sort and add to count
    if (userInput[0] == 'l') {
        linearSearch(newLibrary, requestedLibrary, count);
    }

    else if (userInput[0] == 'b') {
        binarySearch(newLibrary, requestedLibrary, count);
    }

    // to test out if it is organized
//    for (int i = 0; i < (int)newLibrary.size(); i++) {
//        std::cout << newLibrary[i].isbn << " "  << newLibrary[i].language << " " << newLibrary[i].condition << std::endl;
//    }
//
//    std::cout << "\n" << std::endl;
//
//    for (int i = 0; i < (int)requestedLibrary.size(); i++) {
//        std::cout << requestedLibrary[i].isbn << " "  << requestedLibrary[i].language << " " << requestedLibrary[i].condition << std::endl;
//    }

    //open the result file and write down how many books were found, then close the file
    file.open(argv[3], std::ios::out);
    file << count << " book(s) found" << std::endl;
    file.close();

    return 0;
}
