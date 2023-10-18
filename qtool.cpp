
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
    // submit new job to qworker
    // cout << "Job submitted, ID = " << usr.ID << endl;
    // qtool submit <application> <arguments> <user> <group> <deadline> <resource_requirement>
    // qtool submit simulation myUser myGroup ‘10-15-2023 15:55:00’ “CPU=5,MEM=10”
    return 0;
}

int status(int argc, char** argv) {
    // qtool status <id>
    
    if (argv[2] == job.ID) {
        if (job.status == "queued") {
            std::cout << "Job ID: " << job.ID << std::endl;
            std::cout << "Job User: " << job.user << std::endl;
            std::cout << "Queued at: " << job.time_stamp << std::endl;
        }
        else if (job.status == "running") {
            std::cout << "Running" << std::endl;
        }
        else if (job.status == "completed") {
            std::cout << "Completed" << std::endl;
        }
    }

    return 0;
}

int delete_job(int argc, char** argv) {
    // qtool delete_job <id>
    
    if (job.status == "queued") {
        remove(job.ID);
        std::cout << "Deletion completed." << std::endl;
    }
    else std::cout << "Deletion failed. Job status: " << job.status << std::endl;

    return 0;
}

int jobs(int argc, char** argv) {
    // qtool jobs (all|running|completed|queued) <user>

    std::string token = argv[2];

    if (token == "all") {
        // print all jobs for user
        // print job.ID, application name, job.status, reqs, user
        // if queued, print time_stamp
        // if runnung, print start_time
        // if completed, print completed_time
    }
    else if (token == "running") {
        // print all running jobs for user
        // print job.ID, application name, job.status, reqs, user
        // if queued, print time_stamp
        // if runnung, print start_time
        // if completed, print completed_time
    }
    else if (token == "completed") {
        // print all completed jobs for user
        // print job.ID, application name, job.status, reqs, user
        // if queued, print time_stamp
        // if runnung, print start_time
        // if completed, print completed_time 
    }
    else if (token == "queued") {
        // print all queued jobs for user
        // print job.ID, application name, job.status, reqs, user
        // if queued, print time_stamp
        // if runnung, print start_time
        // if completed, print completed_time
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