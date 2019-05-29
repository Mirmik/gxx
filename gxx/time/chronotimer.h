#ifndef GXX_CHRONOTIMER_H
#define GXX_CHRONOTIMER_H

#include <chrono>

namespace gxx 
{
	class chronotimer 
	{
		std::chrono::high_resolution_clock::time_point begstamp;
		std::chrono::high_resolution_clock::time_point endstamp;

	public:
		chronotimer(){};

		void start() { begstamp = std::chrono::high_resolution_clock::now(); }
		void stop() { endstamp = std::chrono::high_resolution_clock::now(); }

		size_t millis() const { return std::chrono::duration_cast<std::chrono::milliseconds>(endstamp - begstamp).count(); }
		size_t micros() const { return std::chrono::duration_cast<std::chrono::microseconds>(endstamp - begstamp).count(); }
	};
}

#endif