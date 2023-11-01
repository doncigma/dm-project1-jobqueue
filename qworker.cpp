
#include <atomic>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <unordered_map>

#include "jobs.h"

std::atomic_bool g_keepRunning = true;

/**
 * @brief Signal handler which is executed by the operating system when Ctrl-C
 * is pressed to kill the running program. Marks the global g_keepRunning
 * variable as false so the while loop terminates
 * 
 * @param signum Signal number sent from the Operating System to the process
 */
void signalHandler(int signum) {
    g_keepRunning = false;
}

int runJob(const std::string& jobName, const std::string& arguments) {
    /**
     * std::unordered_map (https://en.cppreference.com/w/cpp/container/unordered_map)
     * from job name -> function pointer
     * (https://www.cprogramming.com/tutorial/function-pointers.html)
     * which is called to run that job type
     */
    static std::unordered_map<std::string, int(*)(const std::string&)> jobFunctions{
       {std::string{"weather_simulation"}, weather_simulation},
       {std::string{"physics_simulation"}, physics_simulation},
       {std::string{"process_geophysical_data"}, process_geophysical_data},
       {std::string{"parameter_sweep"}, parameter_sweep},
       {std::string{"train_ai_model"}, train_ai_model},
       {std::string{"generate_visulization"}, generate_visulization},
       {std::string{"monte_carlo_sweep"}, monte_carlo_sweep}
    };

    return jobFunctions[jobName](arguments);
}

/**
 * Variables to hold the available CPU + memory this worker has available to
 * run jobs. This worker can only run jobs with resource requirements equal
 * to or lower than these values
 */
uint16_t availableCPU, availableMem;
std::string schedulingPolicy;

int main(int argc, char** argv) {

    // Register signalHandler to gracefully terminate the process when ctrl-l is pressed in the terminal
    //signal(SIGINT, signalHandler);

    if (argc < 4) {
        std::cerr << "Invalid arguments passed" << std::endl;
        std::cout << "qworker <CPU> <MEM> <SCHEDULING POLICY>" << std::endl;
        return 1;
    }

    availableCPU = std::stoul(argv[1]);
    availableMem = std::stoul(argv[2]);
    schedulingPolicy = std::string{argv[3]};

    while (g_keepRunning) {

        // TODO, fetch next job from the database

        // TODO, mark the job as running

        // TODO, run the job function from jobs.h based on the application name
        // See the runJob() function for this

        // TODO, update the state of the job to completed.

        // Go to sleep for a period of time
        std::this_thread::sleep_for(std::chrono::milliseconds{5000});
    }


    return 0;
}