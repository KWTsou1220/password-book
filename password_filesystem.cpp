#include <iostream>
#include <vector>
#include <fstream>
#include <direct.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
using ios = std::ios;


std::string database_path = ".\\book";

void iterate_folder(const char *path)
{
    // obtain current working file path
    char *current_path = new char[256];
    _getcwd(current_path, 256);
    
    
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(path)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", path);
        return;
    }
    chdir(path); // change currently working directory
    while((entry = readdir(dp)) != NULL) {
        stat(entry->d_name, &statbuf); // obtain file status
        if(S_ISDIR(statbuf.st_mode)) {
            // Found a directory, but ignore . and ..
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%s\n", entry->d_name);
            // Recurse at a new indent level
            iterate_folder(entry->d_name);
        }
        else printf("%s\n", entry->d_name);
    }

    chdir(current_path);
    closedir(dp);
}

bool folder_exist(const char *folder_path)
{
    struct stat info;
    return (stat(folder_path, &info) == 0) && (info.st_mode & S_IFDIR);
}

bool file_exist(const char *file_path) {
    struct stat info;
    return (stat(file_path, &info) == 0);
}

bool create_folder(const char *folder_path)
{
    if (folder_exist(folder_path)) return true;
    else
    {
        if (mkdir(folder_path)) return true;
        else return false;
    }
}

void show_meta()
{
    std::cout << std::endl << "---------------------------" << std::endl;
    if (folder_exist(database_path.c_str()))
    {
        iterate_folder(database_path.c_str());
    }
    std::cout << "---------------------------" << std::endl;
    system("pause");
}

void show_account(std::string meta_category)
{
    std::ifstream meta_read;
    std::string meta_path = database_path + "\\" + meta_category + ".txt";
    
    std::cout << std::endl << "---------------------------" << std::endl;
    
    if (file_exist(meta_path.c_str()))
    {
        meta_read.open(meta_path, ios::in);
        while (!meta_read.eof())
        {
            std::string account_name;
            std::string password;

            getline(meta_read, account_name);
            if (!(account_name.compare(""))) break;
            std::cout << account_name << std::endl;

            getline(meta_read, password);
        }
    }
    else
    {
        std::cout << "Meta category does not exist!" << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    system("pause");
}

//TODO
void add_account(
    const std::string meta_category,
    const std::vector<std::string> &account_names,
    const std::vector<std::string> &passwords)
{
    bool add_flag;
    std::ifstream meta_read;
    std::ofstream meta_write;
    std::vector<std::string> old_account_names = {};
    std::vector<std::string> old_passwords = {};
    std::vector<std::string> new_account_names = {};
    std::vector<std::string> new_passwords = {};
    std::string meta_path = database_path + "\\" + meta_category + ".txt";

    if (file_exist(meta_path.c_str()))
    {
        meta_read.open(meta_path, ios::in);
        //while (!meta_read.eof())
        while (!meta_read.eof())
        {
            std::string account_name;
            std::string password;

            getline(meta_read, account_name);
            if (!(account_name.compare(""))) break;
            old_account_names.push_back(account_name);

            getline(meta_read, password);
            old_passwords.push_back(password);
        }

        for (size_t idx = 0; idx < passwords.size(); ++idx)
        {
            new_account_names.push_back(account_names[idx]);
            new_passwords.push_back(passwords[idx]);
        }

        for (size_t idx = 0; idx < old_passwords.size(); ++idx)
        {
            add_flag = true;
            for (size_t jdx = 0; jdx < passwords.size(); ++jdx)
            {
                if (!(account_names[jdx].compare(old_account_names[idx])))
                {
                    // equal
                    add_flag = false;
                    break;
                }
                else
                {
                    // not equal
                }
            }

            if (add_flag)
            {
                new_account_names.push_back(old_account_names[idx]);
                new_passwords.push_back(old_passwords[idx]);
            }
        }

        meta_write.open(meta_path, ios::out);
        for (size_t idx = 0; idx < new_passwords.size(); ++idx)
        {
            if (!(meta_write << new_account_names[idx] << std::endl)) std::cerr << "write error\n";
            meta_write << new_passwords[idx] << std::endl;
        }
    }
    else
    {
        meta_write.open(meta_path, ios::out);
        if (!meta_write.is_open()) std::cerr << "open error\n";
        for (size_t idx = 0; idx < passwords.size(); ++idx)
        {
            if (!(meta_write << account_names[idx] << std::endl)) std::cerr << "write error\n";
            meta_write << passwords[idx] << std::endl;
        }
        meta_write.close();
    }

    if (meta_read.is_open()) meta_read.close();
    if (meta_write.is_open()) meta_write.close();
}