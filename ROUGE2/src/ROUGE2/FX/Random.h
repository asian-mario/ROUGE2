#pragma once
#include <random>

namespace ROUGE2 {
	class Random {
	public:
		static void Init() {
			s_R2Random.seed(std::random_device()());
		}

		static float Float() {
			return (float)s_Distribution(s_R2Random) / (float)std::numeric_limits<uint32_t>::max();
		}
	private:
		static std::mt19937 s_R2Random;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};

}