#include <random>

#include "probability.h"
namespace maze
{
    namespace math
    {
        namespace probability
        {
            std::default_random_engine& global_random_engine()
            {
                static std::default_random_engine u{};
                return u;
            }

            void randomize()
            {
                static std::random_device rd{};
                global_random_engine().seed(rd());
            }

            void randomize_with_seed(unsigned seed)
            {
                global_random_engine().seed(seed);
            }

            bool flip_coin()
            {
                static std::bernoulli_distribution d(0.5);
                return d(global_random_engine());
            }

            int random_number(int from, int to)
            {
                static std::uniform_int_distribution<> d{};
                using param_t = decltype(d)::param_type;
                return d(global_random_engine(), param_t{ from,to });
            }
        }
        
    }
}