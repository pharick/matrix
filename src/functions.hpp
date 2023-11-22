#ifndef M42_FUNCTIONS_HPP
#define M42_FUNCTIONS_HPP

#include "Vector.hpp"

namespace m42
{

   /**
     * @brief Computes a linear combination of vectors
     * 
     * @tparam T Type of the vector components
     * @param vectors std::vector of vectors
     * @param coefficients std::vector of coefficients
     * @return Vector<T> Linear combination of vectors
     */
    template <Arithmetic T>
    Vector<T> linear_combination(const std::vector<Vector<T>> &vectors, const std::vector<T> &coefficients)
    {
        if (vectors.size() != coefficients.size())
            throw std::invalid_argument("Vectors and coefficients collections must be of the same size");
        size_t vector_size = vectors[0].size();
        for (const auto &vector : vectors)
        {
            if (vector.size() != vector_size)
                throw std::invalid_argument("Vectors must be of the same size");
        }

        Vector<T> result(vector_size);
        // using std::fma
        for (size_t i = 0; i < vector_size; i++)
        {
            T sum = 0;
            for (size_t j = 0; j < vectors.size(); j++)
                sum = std::fma(vectors[j][i], coefficients[j], sum);
            result[i] = sum;
        }

        return result;
    }

    /**
     * @brief Computes a linear combination of vectors
     * 
     * @tparam T Type of the vector components
     * @param vectors Initializer list of vectors
     * @param coefficients Initializer list of coefficients
     * @return Vector<T> Linear combination of vectors
     */
    template <Arithmetic T>
    Vector<T> linear_combination(std::initializer_list<Vector<T>> vectors, std::initializer_list<T> coefficients)
    {
        return linear_combination(std::vector<Vector<T>>(vectors), std::vector<T>(coefficients));
    }

    /**
     * @brief Linearly interpolates between two values
     * 
     * @tparam T Type of the values
     * @param u First value
     * @param v Second value
     * @param t Interpolation parameter
     * @return T Interpolated value
     */
    template <typename T>
    T lerp(T u, T v, double t)
    {
        return u + (v - u) * t;
    }

}

#endif
