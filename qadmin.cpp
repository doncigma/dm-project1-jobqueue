
#include <string>
#include <iostream>
// #include <libpq.h>

int add(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: qadmin add user <first name> <last name> <email> <department> <optional list of group names" << std::endl;
        std::cout << "Usage: qadmin add group <group name> <department name>" << std::endl;
        std::cout << "Usage: qadmin add department <department name> <department head> <department building>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];

    if (subcommand == "user") {
        for (int i = 3; i < argc; i++) {
            // qadmin add user <first name> <last name> <email> <department> <optional list of group names>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else if (subcommand == "group") {
        for (int i = 3; i < argc; i++) {
            // qadmin add group <group name> <department name>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else if (subcommand == "department") {
        for (int i = 3; i < argc; i++) {
            // qadmin add department <department name> <department head> <department building>
            // Q: do stuff to add argv[i] to database somehow
        }
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int list(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: qadmin list <user|group|department>" << std::endl;
        return 1;
    }

    std::string subcommand = argv[2];

    if (subcommand == "user") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all users
        }
    }
    else if (subcommand == "department") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all departments
        }
    }
    else if (subcommand == "group") {
        for (int i = 3; i < argc; i++) {
            // Q: cout << do stuff to print all groups
        }
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int remove(int argc, char **argv)
{
    if (argc < 3) {
        std::cout << "Usage: qadmin remove <user|group|department> <name>" << std::endl;
        return 1;
    }

    std::string removeType = argv[2];

    if (removeType == "user") {
        // qadmin remove user <first name> <last name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string userName = argv[3];
    }
    else if (removeType == "group") {
        // qadmin remove group <group name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string groupName = argv[3];
    }
    else if (removeType == "department") {
        // qadmin remove department <department name>
        // Q: replace data with a "deleted_at" timestamp for soft delete
        
        std::string deptName = argv[3];
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
    }

    return 0;
}

int assign(int argc, char **argv)
{
    if (argc < 4) {
        std::cout << "Usage: qadmin assign <user_to_group|group_to_department> <name1> <name2>" << std::endl;
        return 1;
    }

    std::string assignType = argv[2];
    std::string name1 = argv[3];
    std::string name2 = argv[4];

    if (assignType == "user_to_group") {
        std::string userName = argv[3];
        std::string groupName = argv[4];

        // Q: add userName to groupName
    }
    else if (assignType == "group_to_department") {
        std::string groupName = argv[3];
        std::string deptName = argv[4];

        // Q: add deptName to roupName
    }
    else {
        std::cout << "Incorrect input. Check command syntax." << std::endl;
        return 1;
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
        std::cout << "Too few arguments provided" << std::endl;
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