
#include <string>
#include <iostream>

int add(int argc, char **argv)
{
    // TODO, implement the add command
    return 0;
}

int list(int argc, char **argv)
{
    // TODO, implement the list command
    return 0;
}

int remove(int argc, char **argv)
{
    // TODO, implement the list command
    return 0;
}

int assign(int argc, char **argv)
{
    // TODO, implement the list command
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