
#include <string>
#include <iostream>
// #include <libpq.h>

int add(int argc, char **argv)
{
    std::string token = argv[2];

    if (token == "user") {
        for (int i = 3; i < argc; i++) {
            // do stuff to add argv[i] to database somehow
            // qadmin add user <first name> <last name> <email> <department> <optional list of group names>
        }
    }
    else if (token == "department") {
        for (int i = 3; i < argc; i++) {
            // do stuff to add argv[i] to database somehow
            // qadmin add department <department name> <department head> <department building>
        }
    }
    else if (token == "group") {
        for (int i = 3; i < argc; i++) {
            // do stuff to add argv[i] to database somehow
            // qadmin add group <group name> <department name>
        }
    }

    return 0;
}

int list(int argc, char **argv)
{
    std::string token = argv[2];

    if (token == "user") {
        for (int i = 3; i < argc; i++) {
            // do stuff to print all users
        }
    }
    else if (token == "department") {
        for (int i = 3; i < argc; i++) {
            // do stuff to print all departments
        }
    }
    else if (token == "group") {
        for (int i = 3; i < argc; i++) {
            // do stuff to print all groups
        }
    }
    return 0;
}

int remove(int argc, char **argv)
{
    std::string token = argv[2];

    if (token == "user") {
        // check for user-specific paramaters like name
        // replace data with a "deleted_at" timestamp for soft delete
        // qadmin remove user <first name> <last name>
    }
    else if (token == "group") {
        // check for group-specific paramaters like group_name
        // replace data with a "deleted_at" timestamp for soft delete
        // qadmin remove group <group name>
    }
    return 0;
}

int assign(int argc, char **argv)
{
    std::string token = argv[2];

    if (token == "user_to_group") {
        // check for group_name and user_name
        // do stuff
    }
    else if (token == "group_to_department") {
        // check for group_name and department_name
        // do stuff
    }
    return 0;
}

/**
 * TODO: Implement any other commands as needed
 */

/** 
 * Argument Parsing:
 * 
 * To access the n-th argument as a string:
 * * std::string argument = std::string{argv[n]};
 * 
 * To access the n-th argument as an integer:
 * * Use conversion functions here: https://en.cppreference.com/w/cpp/string/basic_string/stol
 */

int main(int argc, char **argv)
{

    /**
     * argc -> Number of arguments, the first argument is the name of the
     * program itself, the following values
     * (argv[1], argv[2], ... argv[argc - 1]) are the arguments passed to
     * qadmin arg1 arg2 arg3 ...
     *
     * argv is the array of char* value each of which is a pointer to
     * the start of a string containing the value of the argument
     *
     */

    if (argc < 2)
    {
        std::cerr << "Too few arguments provided" << std::endl;
        return 1;
    }

    std::string subcommand{argv[1]};

    if (subcommand == "add")
    {
        return add(argc, argv);
    }
    else if (subcommand == "list")
    {
        return list(argc, argv);
    }
    else if (subcommand == "remove")
    {
        return remove(argc, argv);
    }
    else if (subcommand == "assign")
    {
        return assign(argc, argv);
    }

    return 0;
}