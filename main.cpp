#include <iostream>
#include <direct.h>
#include <sys/stat.h>
#include "password_filesystem.h"
#include "password_book.h"

// 0. crypto setup
// 1. encryption algorithm
// 2. cin, getline
// 3. sys/stat.h and mkdir

extern std::string database_path;

int main()
{
    create_folder(database_path.c_str());
    
    std::cout << "Password book" << std::endl;
       
    char option;
    while (option != '6')
    {
        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Find password" << std::endl;
        std::cout << "2. Add password" << std::endl;
        std::cout << "3. Delete password" << std::endl;
        std::cout << "4. Modify password" << std::endl;
        std::cout << "5. Show all password" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "Entering your option: ";
        std::cin >> option;
        // final enter \0 will affect next function's cin
        // so cin.ignore(1, EOF) is needed for eliminating \0
        std::cin.ignore();
        operation(option);
    }

    return 0;
}