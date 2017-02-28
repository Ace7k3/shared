#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>

class StepTimer {

	public:
		void start_timing_step(const std::string label, const std::string description);
		void stop_timing_step(const std::string label);
		void print_timings(std::ostream& ostr);

	private:
		std::vector<std::pair<std::string, double>> _finished_timings;
		std::map<std::string, std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>> _timers;

		std::string timing_to_readable(std::size_t milliseconds);

};
