
#include <string>
#include <iostream>

void help() {
    std::cout << "qtool" << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "  qtool submit <APPLICATION> <ARGS> <USER> <GROUP> <DEADLINE> <RESOURCE>" << std::endl;
    std::cout << "  qtool status <JOB_ID>" << std::endl;
    std::cout << "  qtool jobs (all|running|completed|queued) <USER>" << std::endl;
    std::cout << "  qtool delete_job <JOB_ID>" << std::endl;
    // TODO: Add any additional help information
}

int submit(int argc, char** argv) {
    // TODO, implement the submit command
    return 0;
}

int status(int argc, char** argv) {
    // TODO, implement the status command
    return 0;
}

int delete_job(int argc, char** argv) {
    // TODO, implement the delete command
    return 0;
}

int jobs(int argc, char** argv) {
    // TODO, implement the jobs command
    return 0;
}

/**
 * TODO: Implement any other commands as needed
 */

int main(int argc, char** argv) {

    /**
     * argc -> Number of arguments, the first argument is the name of the
     * program itself, the following values
     * (argv[1], argv[2], ... argv[argc - 1]) are the arguments passed to 
     * qadmin arg1 arg2 arg3 ...
     * 
     * argv is the array of char* value each of which is a pointer to
     * the start of a string containing the value of the argument
     */

    if (argc < 2) {
        std::cerr << "Too few arguments provided" << std::endl;
        help();
        return 1;
    }

    std::string subcommand{argv[1]};

    if (subcommand == "submit") {
        return submit(argc, argv);
    } else if (subcommand == "status") {
        return status(argc, argv);
    } else if (subcommand == "delete_job") {
        return delete_job(argc, argv);
    } else if (subcommand == "jobs") {
        return jobs(argc, argv);
    } else {
        std::cout << "Unknown subcommand: " << subcommand;
        help();
    }

    return 0;
}