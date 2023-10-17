#include "jobs.h"

#include <thread>
#include <random>
#include <chrono>
#include <iostream>

static std::chrono::seconds generateRuntime(int maxRuntime)
{
    std::random_device rd;                               // non-deterministic generator
    std::mt19937 gen(rd());                              // to seed mersenne twister.
    std::uniform_int_distribution<> dist(1, maxRuntime); // distribute results between 1 and maxRuntime inclusive.

    return std::chrono::seconds{dist(gen)};
}

static void runForUpTo(int maxRuntime)
{
    std::this_thread::sleep_for(generateRuntime(maxRuntime));
}

static int returnValue()
{
    std::random_device rd;                        // non-deterministic generator
    std::mt19937 gen(rd());                       // to seed mersenne twister.
    std::uniform_int_distribution<> dist(0, 100); // distribute results between 0 and 100 inclusive.
    return dist(gen) < 99 ? 0 : 1;
}

/**
 * This file defined the various job functions. You should not modify this file
 * nor do you need to modify this file
 */

int weather_simulation(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(60);
    return returnValue();
}

int physics_simulation(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(45);
    return returnValue();
}

int process_geophysical_data(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(75);
    return returnValue();
}

int parameter_sweep(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(80);
    return returnValue();
}

int train_ai_model(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(90);
    return returnValue();
}

int generate_visulization(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(20);
    return returnValue();
}

int monte_carlo_sweep(const std::string &args)
{
    std::cout << "Running " << __func__ << " with argments \"" << args << "\"" << std::endl;
    runForUpTo(30);
    return returnValue();
}