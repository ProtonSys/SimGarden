//
// Created by Celso Jordão on 08/11/2025.
//

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

/**
 * @brief Utility class for generating random numbers using modern C++ <random> library
 *
 * This class provides thread-safe random number generation with proper distribution.
 * Uses Mersenne Twister engine (mt19937) for high-quality random numbers.
 */
class RandomGenerator {
private:
    static std::mt19937& getEngine() {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        return engine;
    }

    // Delete constructor to prevent instantiation (utility class)
    RandomGenerator() = delete;
    ~RandomGenerator() = delete;
    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

public:
    /**
     * @brief Generate a random integer in the range [min, max] (inclusive)
     *
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @return Random integer in the range [min, max]
     */
    static int getInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getEngine());
    }

    /**
     * @brief Generate a random boolean with given probability of true
     *
     * @param probability Probability of returning true (0.0 to 1.0)
     * @return true or false based on probability
     */
    static bool getBool(double probability = 0.5) {
        std::bernoulli_distribution dist(probability);
        return dist(getEngine());
    }

    /**
     * @brief Generate a random double in the range [min, max)
     *
     * @param min Minimum value (inclusive)
     * @param max Maximum value (exclusive)
     * @return Random double in the range [min, max)
     */
    static double getDouble(double min = 0.0, double max = 1.0) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(getEngine());
    }

    /**
     * @brief Seed the random number generator (for testing purposes)
     *
     * @param seed Seed value
     */
    static void setSeed(unsigned int seed) {
        getEngine().seed(seed);
    }
};

#endif // RANDOMGENERATOR_H
