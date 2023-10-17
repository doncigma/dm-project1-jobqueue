#pragma once

/**
 * @brief This header defines the various job types which can run in the
 * system. When the qworker program pulls jobs from the database to execute,
 * it will run the function declared here based on a matching name.
 *
 * Each job function returns an integer. If 0, the job ran successfully,
 * if 1, the job failed.
 *
 */

#include <string>

int weather_simulation(const std::string &args);

int physics_simulation(const std::string &args);

int process_geophysical_data(const std::string &args);

int parameter_sweep(const std::string& args);

int train_ai_model(const std::string &args);

int generate_visulization(const std::string &args);

int monte_carlo_sweep(const std::string& args);