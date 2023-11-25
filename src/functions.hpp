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
    Vector<T> linearCombination(const std::vector<Vector<T>> &vectors, const std::vector<T> &coefficients)
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
    Vector<T> linearCombination(std::initializer_list<Vector<T>> vectors, std::initializer_list<T> coefficients)
    {
        return linearCombination(std::vector<Vector<T>>(vectors), std::vector<T>(coefficients));
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

    /**
     * @brief Computes the cosine of angle between two vectors
     * 
     * @tparam T Type of the vector components
     * @param u First vector
     * @param v Second vector
     * @return double Cosine of angle between the vectors
     */
    template <typename T>
    double angleCos(const Vector<T> &u, const Vector<T> &v)
    {
        return (u * v) / (u.norm() * v.norm());
    }

    /**
     * @brief Computes cross product of two 3-dimensional vectors
     * 
     * @tparam T Type of the vector components
     * @param u First vector
     * @param v Second vector
     * @return Vector<T> Cross product of the vectors
     */
    template <typename T>
    Vector<T> crossProduct(const Vector<T> &u, const Vector<T> &v)
    {
        if (u.size() != 3 || v.size() != 3)
            throw std::invalid_argument("Cross product is defined only for 3-dimensional vectors");
        return Vector<T>{
            u[1] * v[2] - u[2] * v[1],
            u[2] * v[0] - u[0] * v[2],
            u[0] * v[1] - u[1] * v[0],
        };
    }

    /**
     * @brief Computes a perspective projection matrix
     * 
     * @param fov Field of view
     * @param aspect Aspect ratio
     * @param near Near clipping plane
     * @param far Far clipping plane
     * @return Matrix<float> Perspective projection matrix
     */
    Matrix<float> makeProjectionMatrix(float fov, float aspect, float near, float far)
    {
        float f = 1.0f / std::tan(fov / 2.0f);
        return Matrix<float>{
            {f / aspect, 0.0f,  0.0f,                        0.0f                              },
            {0.0f,       f,     0.0f,                        0.0f                              },
            {0.0f,       0.0f,  (far + near) / (near - far), (2.0f * far * near) / (near - far)},
            {0.0f,       0.0f, -1.0f,                        0.0f                              },
        };
    }

}

#endif
