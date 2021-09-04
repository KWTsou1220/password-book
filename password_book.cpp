#include <iostream>
#include <string>
#include <vector>
#include "password_book.h"
#include "password_filesystem.h"


void find_password()
{
    std::string dummy;
    std::string meta_category;

    show_meta();

    std::cout << std::endl << std::endl << "Find (meta account): " << std::endl;
    std::getline(std::cin, meta_category);
    
    show_account(meta_category.c_str());
}

void delete_password()
{
    show_meta();

    std::string meta_category;
    int delete_number;

    std::cout << "Delete (meta account): ";
    std::getline(std::cin, meta_category);

    show_account(meta_category.c_str());

    std::cout << "Delete how many number of accounts: ";
    std::cin >> delete_number;
    std::cin.ignore();
    for (size_t idx = 0; idx < delete_number; ++idx)
    {
        //TODO: delete operation
    }

    show_account(meta_category.c_str());
}

void add_password()
{
    int add_number;
    std::string meta_category;
    std::vector<std::string> account_names;
    std::vector<std::string> passwords;


    show_meta();

    std::cout << "Add (meta account): ";
    std::getline(std::cin, meta_category);
    
    show_account(meta_category.c_str());

    std::cout << "Add how many number of accounts: ";
    std::cin >> add_number;
    std::cin.ignore();

    for (size_t idx = 0; idx < add_number; ++idx)
    {
        std::string account_name;
        std::string password;
        
        // if account name exists, then overwrite old password
        std::cout << "account: ";
        getline(std::cin, account_name);
        std::cout << "password: ";
        getline(std::cin, password);
        account_names.push_back(account_name);
        passwords.push_back(password);
    }
    add_account(meta_category.c_str(), account_names, passwords);
    show_account(meta_category.c_str());
}

void modify_password()
{
    show_meta();

    std::string meta_category;
    int modify_number;

    std::cout << "Modify (meta account): ";
    std::getline(std::cin, meta_category);
    std::cin.ignore();
    for (size_t idx = 0; idx < modify_number; ++idx)
    {
        //TODO: we should first verify if it is existing meta
    }

    show_account(meta_category.c_str());
}

void show_password()
{
    //TODO
}


void operation(char option)
{
    switch (option)
    {
    case '1':
        find_password();
        break;
    case '2':
        add_password();
        break;
    case '3':
        delete_password();
        break;
    case '4':
        modify_password();
        break;
    case '5':
        show_password();
        break;
    case '6':
        std::cout << "Exit!" << std::endl;
        break;
    default:
        std::cout << "No such option!" << std::endl;
        break;
    }
}
