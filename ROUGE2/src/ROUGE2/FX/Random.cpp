#include "r2pch.h"
#include "Random.h"

namespace ROUGE2 {
	std::mt19937 Random::s_R2Random;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;
}

