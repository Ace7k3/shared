#include "stepTimer.h"

#include <sstream>
#include <iomanip>
#include <iostream>

void StepTimer::start_timing_step(const std::string label, const std::string description)
{
	if(_timers.find(label) != _timers.end())
		throw std::logic_error("Tried to start timer with existing label again");

	_timers.insert({ label, { description, std::chrono::steady_clock::now() } });
}

void StepTimer::stop_timing_step(const std::string label)
{
	auto it = _timers.find(label);
	if(it == _timers.end())
		throw std::logic_error("Tried to stop non-started timer.");

	auto endTime = std::chrono::steady_clock::now();
	auto diff = std::chrono::duration<double, std::milli>(endTime-it->second.second).count();
	_finished_timings.push_back({ it->second.first, diff });

	_timers.erase(it);
}

void StepTimer::print_timings(std::ostream& ostr)
{
	std::size_t maxStrLength = 0;
	for(auto timing : _finished_timings)
		maxStrLength = std::max(maxStrLength, timing.first.length());

	for(auto timing : _finished_timings)
		ostr << std::left << std::setw(maxStrLength+3) << timing.first + ": " << timing_to_readable(timing.second) << std::endl;
}

std::string StepTimer::timing_to_readable(std::size_t milliseconds)
{
	std::stringstream ss;

	auto hours = (milliseconds / (1000*60*60));
	auto mins =  (milliseconds % (1000*60*60)) / (1000*60);
	auto seconds =  ((milliseconds % (1000*60*60)) % (1000*60)) / 1000;
	auto milli =  (((milliseconds % (1000*60*60)) % (1000*60)) % 1000);
	ss << hours << "h " << std::setw(2) << mins << "m " << std::setw(2) << seconds << "s " << std::setw(4) << milli << "ms";

	return ss.str();
}
