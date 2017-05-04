#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

namespace Shared {

	class StepTimer {

		public:

			inline void start_timing_step(const std::string label, const std::string description, std::ostream* output = nullptr)
			{
				if(_timers.find(label) != _timers.end())
					throw std::logic_error("Tried to start timer with existing label again");

				_timers.insert({ label, { description, std::chrono::steady_clock::now() } });

				if(output != nullptr)
					*output << "Begin: " << description << std::endl;
			}

			inline void stop_timing_step(const std::string label, std::ostream* output = nullptr)
			{
				auto it = _timers.find(label);
				if(it == _timers.end())
					throw std::logic_error("Tried to stop non-started timer.");

				auto endTime = std::chrono::steady_clock::now();
				auto diff = std::chrono::duration<double, std::milli>(endTime-it->second.second).count();
				_finished_timings.push_back({ it->second.first, diff });

				if(output != nullptr)
					*output << "End: " << it->second.first << "\t (" << timing_to_readable(_finished_timings.back().second) << ")" << std::endl;

				_timers.erase(it);
			}

			inline void print_timings(std::ostream& ostr) const
			{
				std::size_t maxStrLength = 0;
				for(auto timing : _finished_timings)
					maxStrLength = std::max(maxStrLength, timing.first.length());

				for(auto timing : _finished_timings)
					ostr << std::left << std::setw(maxStrLength+3) << timing.first + ": " << timing_to_readable(timing.second) << std::endl;
			}


		private:
			std::vector<std::pair<std::string, double>> _finished_timings;
			std::map<std::string, std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock>>> _timers;

			inline std::string timing_to_readable(std::size_t milliseconds) const
			{
				std::stringstream ss;

				auto hours = (milliseconds / (1000*60*60));
				auto mins =  (milliseconds % (1000*60*60)) / (1000*60);
				auto seconds =  ((milliseconds % (1000*60*60)) % (1000*60)) / 1000;
				auto milli =  (((milliseconds % (1000*60*60)) % (1000*60)) % 1000);
				ss << hours << "h " << std::setw(2) << mins << "m " << std::setw(2) << seconds << "s " << std::setw(4) << milli << "ms";

				return ss.str();
			}
	};

}
