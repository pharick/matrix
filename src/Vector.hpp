#ifndef M42_VECTOR_HPP
#define M42_VECTOR_HPP

#include <cstddef>
#include <string>
#include <ostream>
#include <utility>
#include <vector>

#include "VectorView.hpp"

namespace m42
{
    template <Arithmetic T>
    class VectorView;

    /**
     * @brief Vector class
     *
     * @tparam T Type of vector elements
     */
    template <Arithmetic T>
    class Vector : public VectorView<T>
    {
    public:
        Vector();
        Vector(size_t size);
        Vector(std::initializer_list<T> list);
        Vector(const T *data, size_t size);
        Vector(const Vector &other);
        Vector(const VectorView<T> &v);
        Vector(Vector &&other) noexcept;
        Vector &operator=(Vector other);
        ~Vector();
    };

    /**
     * @brief Default constructor
     *
     */
    template <Arithmetic T>
    Vector<T>::Vector() : VectorView<T>(nullptr, 0) {}

    /**
     * @brief Construct a new Vector object with a given size
     *
     * @param size Size of the vector
     */
    template <Arithmetic T>
    Vector<T>::Vector(size_t size) : VectorView<T>(new T[size], size) {}

    /**
     * @brief Construct a new Vector object from an initializer list
     *
     * @param list Initializer list
     */
    template <Arithmetic T>
    Vector<T>::Vector(std::initializer_list<T> list) : VectorView<T>(new T[list.size()], list.size())
    {
        size_t i = 0;
        for (auto &elem : list)
            VectorView<T>::_data[i++] = elem;
    }

    /**
     * @brief Construct a new Vector object from a pointer to the vector data
     *
     * @param data Pointer to the vector data
     */
    template <Arithmetic T>
    Vector<T>::Vector(const T *data, size_t size) : VectorView<T>(new T[size], size)
    {
        for (size_t i = 0; i < size; i++)
            VectorView<T>::_data[i] = data[i];
    }

    /**
     * @brief Copy constructor
     *
     * @param other Vector to copy
     */
    template <Arithmetic T>
    Vector<T>::Vector(const Vector &other) : VectorView<T>(new T[other.size()], other.size())
    {
        for (size_t i = 0; i < other.size(); i++)
            VectorView<T>::_data[i] = other[i];
    }

    /**
     * @brief Construct a new Vector object from a VectorView
     *
     * @param other
     */
    template <Arithmetic T>
    Vector<T>::Vector(const VectorView<T> &v) : Vector(v.data(), v.size()) {}

    /**
     * @brief Move constructor
     *
     * @param other Vector to move
     */
    template <Arithmetic T>
    Vector<T>::Vector(Vector &&other) noexcept : VectorView<T>(other.data(), other.size())
    {
        other._data = nullptr;
        other._size = 0;
    }

    /**
     * @brief Assignment operator
     *
     * @param other Right-hand side of the assignment
     * @return Vector<T, N>& Left-hand side after assignment
     */
    template <Arithmetic T>
    Vector<T> &Vector<T>::operator=(Vector<T> other)
    {
        // copy and swap idiom
        std::swap(VectorView<T>::_data, other._data);
        VectorView<T>::_size = other._size;
        return *this;
    }

    /**
     * @brief Destroy Vector object
     */
    template <Arithmetic T>
    Vector<T>::~Vector()
    {
        delete[] VectorView<T>::_data;
    }

}

#endif
