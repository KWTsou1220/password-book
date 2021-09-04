#ifndef __PASSWORD_FILESYSTEM__
#define __PASSWORD_FILESYSTEM__

#include <vector>
#include <string>

void iterate_folder(const char *path);
bool folder_exist(const char *folder_path);
bool file_exist(const char *file_path);
bool create_folder(const char*);

void show_meta();
void show_account(std::string);
void add_account(
    const std::string, const std::vector<std::string>&, const std::vector<std::string>&);

#endif