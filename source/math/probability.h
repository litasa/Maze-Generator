#pragma once
#include <random>

namespace maze
{
    namespace math
    {
        namespace probability
        {
            std::default_random_engine& global_random_engine();

            void randomize();

            void randomize_with_seed(unsigned seed);

            bool flip_coin();

            int random_number(int from, int to);
        }
        
    }
}