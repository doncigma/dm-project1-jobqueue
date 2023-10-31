#include <string>
#include <iostream>

void help() {
    std::cout << "qtool" << std::endl;
    std::cout << "Usage: " << std::endl;
    std::cout << "  qtool submit <application> <arguments> <user> <group> <deadline> <resource_requirement>" << std::endl;
    std::cout << "  qtool status <id>" << std::endl;
    std::cout << "  qtool jobs (all|running|completed|queued) <user>" << std::endl;
    std::cout << "  qtool delete_job <id>" << std::endl;
    // TODO: Add any additional help information
}

int submit(int argc, char** argv) {
    // submit new job to qworker
    // qtool submit <application> <arguments> <user> <group> <deadline> <resource_requirement>
    // qtool submit simulation myUser myGroup ‘10-15-2023 15:55:00’ “CPU=5,MEM=10”
    
    if (argc < 7) {
        std::cout << "Usage: qtool submit <application> <arguments> <user> <group> <deadline> <resource_requirement>" << std::endl;
        return 1;
    }
    std::string application = argv[2];
    std::string args = argv[3];
    std::string user = argv[4];
    std::string group = argv[5];
    std::string deadline = argv[6];
    std::string resource = argv[7];
    
    std::string uniqueID = ""; // Q: random ID generator
    std::cout << "Job submitted, ID = " << uniqueID << std::endl;
    return 0;
}

int status(int argc, char** argv) {
    // qtool status <id>
    
    if (argc < 3) {
        std::cout << "Usage: qtool status <id>" << std::endl;
        return 1;
    }

    std::string status = argv[1];
    std::string ID = argv[2];

    if (status == "queued") {
        std::cout << "Job ID: " << ID << std::endl;
        std::cout << "Job User: " << job.user << std::endl; // Q: somehow access jobs user and time_stamp from database
        std::cout << "Queued at: " << job.time_stamp << std::endl; // ^^
    }
    else if (status == "running") {
        std::cout << "Running" << std::endl;
    }
    else if (status == "completed") {
        std::cout << "Completed" << std::endl;
    }

    return 0;
}

int delete_job(int argc, char** argv) {
    // qtool delete_job <id>
    
    if (argc < 3) {
        std::cout << "Usage: qtool delete_job <id>" << std::endl;
        return 1;
    }
    std::string status = argv[1];
    std::string ID = argv[2];

    if (status == "queued") {
        // Q: somehow remove job based on ID
        std::cout << "Deletion completed." << std::endl;
    }
    else std::cout << "Deletion failed. Job status: " << status << std::endl;

    return 0;
}

int jobs(int argc, char** argv) {
    // qtool jobs (all|running|completed|queued) <user>

    if (argc < 3) {
        std::cout << "Usage: qtool jobs (all|running|completed|queued) <user>" << std::endl;
        return 1;
    }
    std::string filter = argv[2];
    std::string user = argv[3];

    std::string subcommand = argv[2];

    if (subcommand == "all") {
        // print all jobs for user
        // Q: print job.ID, application name, job.status, reqs, user
        // if queued, print time_stamp
        // if runnung, print start_time
        // if completed, print completed_time
    }
    else if (subcommand == "running") {
        // print all running jobs for user
        // Q: print job.ID, application name, job.status, reqs, user, print start_time
    }
    else if (subcommand == "completed") {
        // print all completed jobs for user
        // Q: print job.ID, application name, job.status, reqs, user, print completed_time 
    }
    else if (subcommand == "queued") {
        // print all queued jobs for user
        // Q: print job.ID, application name, job.status, reqs, user, print time_stamp
    }

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
    } 
    else if (subcommand == "status") {
        return status(argc, argv);
    } 
    else if (subcommand == "delete_job") {
        return delete_job(argc, argv);
    } 
    else if (subcommand == "jobs") {
        return jobs(argc, argv);
    } 
    else {
        std::cout << "Unknown subcommand: " << subcommand;
        help();
    }

    return 0;
}