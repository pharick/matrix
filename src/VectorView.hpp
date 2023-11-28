#ifndef M42_VECTOR_VIEW_HPP
#define M42_VECTOR_VIEW_HPP

#include "common.hpp"
#include "Matrix.hpp"

namespace m42
{

    template <Arithmetic T>
    class Vector;

    template <Arithmetic T>
    class Matrix;

    /**
     * @brief Represents data in memory as a vector
     *
     * @tparam T Type of vector elements
     */
    template <Arithmetic T>
    class VectorView
    {
    protected:
        T *_data;
        size_t _size;

    public:
        using value_type = T;

        VectorView() = delete;
        VectorView(T *data, size_t size);
        VectorView(const VectorView &other) = default;
        VectorView &operator=(const VectorView &other);
        VectorView &operator=(const Vector<T> &v);
        ~VectorView() = default;

        size_t size() const;
        T *data();
        const T *data() const;
        Matrix<T> reshape() const;
        double norm1() const;
        double norm() const;
        double normInf() const;
        bool isApprox(const VectorView &other, double epsilon = 1e-8) const;

        T &operator[](size_t index);
        const T &operator[](size_t index) const;
        bool operator==(const VectorView &other) const;
        Vector<T> operator+(const VectorView &other) const;
        Vector<T> operator-(const VectorView &other) const;
        VectorView<T> &operator+=(const VectorView &other);
        VectorView<T> &operator-=(const VectorView &other);
        Vector<T> operator*(T scalar) const;
        VectorView<T> operator*=(T scalar);
        Vector<T> operator/(T scalar);
        VectorView<T> operator/=(T scalar);
        T operator*(const VectorView &other) const;
        Vector<T> operator-() const;
        operator std::string() const;
    };

    /**
     * @brief Construct a new VectorView object
     *
     * @param data Pointer to data
     * @param size Size of vector
     */
    template <Arithmetic T>
    VectorView<T>::VectorView(T *data, size_t size) : _data(data), _size(size) {}

    /**
     * @brief Assignment operator
     *
     * @param other VectorView to copy
     * @return VectorView& Reference to self
     */
    template <Arithmetic T>
    VectorView<T> &VectorView<T>::operator=(const VectorView &other)
    {
        if (size() != other.size())
            throw std::invalid_argument("VectorView must be of the same size");
        if (data() == other.data())
            return *this;
        for (size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
        return *this;
    }

    /**
     * @brief Assign a vector to the vector view
     * 
     * @param v Vector to assign
     */
    template <Arithmetic T>
    VectorView<T> &VectorView<T>::operator=(const Vector<T> &v)
    {
        if (size() != v.size())
            throw std::invalid_argument("Vector must be of the same size");
        for (size_t i = 0; i < _size; i++)
            _data[i] = v[i];
        return *this;
    }

    /**
     * @brief Get the size of the vector
     *
     * @return size_t Size of the vector
     */
    template <Arithmetic T>
    size_t VectorView<T>::size() const
    {
        return _size;
    }

    /**
     * @brief Get data pointer
     *
     * @return T* Pointer to data
     */
    template <Arithmetic T>
    T *VectorView<T>::data()
    {
        return _data;
    }

    /**
     * @brief Get const data pointer
     *
     * @return const T* Pointer to data
     */
    template <Arithmetic T>
    const T *VectorView<T>::data() const
    {
        return _data;
    }

    /**
     * @brief Reshape vector into size x 1 matrix
     *
     * @return Matrix<T> Reshaped vector
     */
    template <Arithmetic T>
    Matrix<T> VectorView<T>::reshape() const
    {
        Matrix<T> result(_size, 1);
        result.setRow(0, *this);
        return result;
    }

    /**
     * @brief Calculate the manhattan norm of the vector
     *
     * @return double manhattan norm
     */
    template <Arithmetic T>
    double VectorView<T>::norm1() const
    {
        T result = 0;
        for (size_t i = 0; i < _size; i++)
            result += std::abs(_data[i]);
        return result;
    }

    /**
     * @brief Calculate the euclidean norm of the vector
     *
     * @return double euclidean norm
     */
    template <Arithmetic T>
    double VectorView<T>::norm() const
    {
        // use std::pow instead of std::sqrt
        T result = 0;
        for (size_t i = 0; i < _size; i++)
            result = std::fma(_data[i], _data[i], result);
        return std::pow(result, 0.5);
    }

    /**
     * @brief Calculate the infinity norm of the vector
     *
     * @return double infinity norm
     */
    template <Arithmetic T>
    double VectorView<T>::normInf() const
    {
        T result = 0;
        for (size_t i = 0; i < _size; i++)
            result = std::max(result, std::abs(_data[i]));
        return result;
    }

    /**
     * @brief Check if two vectors are approximately equal
     *
     * @param other Vector to compare
     * @param epsilon Maximum difference between elements
     * @return true Vectors are approximately equal
     * @return false Vectors are not approximately equal
     */
    template <Arithmetic T>
    bool VectorView<T>::isApprox(const VectorView &other, double epsilon) const
    {
        if (_size != other._size)
            return false;
        for (size_t i = 0; i < _size; i++)
            if (std::abs(_data[i] - other._data[i]) > epsilon)
                return false;
        return true;
    }

    /**
     * @brief Get element at the given index
     *
     * @param index Index of element
     * @return T& Element at index
     */
    template <Arithmetic T>
    T &VectorView<T>::operator[](size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return _data[index];
    }

    /**
     * @brief Get const reference to the element at the given index
     *
     * @param index Index of element
     * @return const T& Element at index
     */
    template <Arithmetic T>
    const T &VectorView<T>::operator[](size_t index) const
    {
        return const_cast<VectorView<T> *>(this)->operator[](index);
    }

    /**
     * @brief Compare two vectors for equality
     *
     * @param other Vector to compare
     * @return true Vectors are equal
     * @return false Vectors are not equal
     */
    template <Arithmetic T>
    bool VectorView<T>::operator==(const VectorView &other) const
    {
        if (_size != other._size)
            return false;
        if (_data == other._data)
            return true;
        for (size_t i = 0; i < _size; i++)
            if (_data[i] != other._data[i])
                return false;
        return true;
    }

    /**
     * @brief Add two vectors
     *
     * @param other Vector to add
     * @return Vector& Result of addition
     */
    template <Arithmetic T>
    Vector<T> VectorView<T>::operator+(const VectorView &other) const
    {
        if (_size != other._size)
            throw std::invalid_argument("Vectors must be of the same size");
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; i++)
            result[i] = _data[i] + other._data[i];
        return result;
    }

    /**
     * @brief Subtract two vectors
     *
     * @param other Vector to subtract
     * @return Vector& Result of subtraction
     */
    template <Arithmetic T>
    Vector<T> VectorView<T>::operator-(const VectorView &other) const
    {
        return (*this) + (-other);
    }

    /**
     * @brief Add two vectors and assign the result to the first vector
     *
     * @param other Vector to add
     * @return Vector& Result of addition
     */
    template <Arithmetic T>
    VectorView<T> &VectorView<T>::operator+=(const VectorView &other)
    {
        (*this) = (*this) + other;
        return *this;
    }

    /**
     * @brief Subtract two vectors and assign the result to the first vector
     *
     * @param other Vector to subtract
     * @return Vector& Result of subtraction
     */
    template <Arithmetic T>
    VectorView<T> &VectorView<T>::operator-=(const VectorView &other)
    {
        (*this) = (*this) - other;
        return *this;
    }

    /**
     * @brief Multiply a vector by a scalar
     *
     * @param scalar Scalar to multiply by
     * @return Vector& Result of multiplication
     */
    template <Arithmetic T>
    Vector<T> VectorView<T>::operator*(T scalar) const
    {
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; i++)
            result[i] = _data[i] * scalar;
        return result;
    }

    /**
     * @brief Multiply a vector by a scalar and assign the result to the vector
     *
     * @param scalar Scalar to multiply by
     * @return Vector& Result of multiplication
     */
    template <Arithmetic T>
    VectorView<T> VectorView<T>::operator*=(T scalar)
    {
        (*this) = (*this) * scalar;
        return *this;
    }

    /**
     * @brief Divide a vector by a scalar
     *
     * @param scalar Scalar to divide by
     * @return Vector Result of division
     */
    template <Arithmetic T>
    Vector<T> VectorView<T>::operator/(T scalar)
    {
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; i++)
            result[i] = _data[i] / scalar;
        return result;
    }

    /**
     * @brief Divide a vector by a scalar and assign the result to the vector
     *
     * @param scalar Scalar to divide by
     * @return Vector& Result of division
     */
    template <Arithmetic T>
    VectorView<T> VectorView<T>::operator/=(T scalar)
    {
        (*this) = (*this) / scalar;
        return *this;
    }

    /**
     * @brief Dot product of two vectors
     *
     * @param other Vector to multiply by
     * @return T Dot product
     */
    template <Arithmetic T>
    T VectorView<T>::operator*(const VectorView &other) const
    {
        if (_size != other._size)
            throw std::invalid_argument("Vectors must be of the same size");
        T result = 0;
        // use std::fma
        for (size_t i = 0; i < _size; i++)
            result = std::fma(_data[i], other._data[i], result);
        return result;
    }

    /**
     * @brief Negate a vector
     *
     * @return Vector Negated vector
     */
    template <Arithmetic T>
    Vector<T> VectorView<T>::operator-() const
    {
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; i++)
            result[i] = -_data[i];
        return result;
    }

    /**
     * @brief Return a string representation of the vector
     *
     * @return std::string String representation of the vector
     */
    template <Arithmetic T>
    VectorView<T>::operator std::string() const
    {
        std::string str = "[";
        for (size_t i = 0; i < size(); i++)
        {
            str += std::to_string((*this)[i]);
            if (i < size() - 1)
                str += " ";
        }
        str += "]";
        return str;
    }

    /**
     * @brief fmt::formatter specialization for vector
     *
     * @param v VectorView to format
     * @return auto Vector formatted as a string
     */
    template <Arithmetic T>
    auto format_as(const VectorView<T> &v)
    {
        return static_cast<std::string>(v);
    }

    /**
     * @brief Output stream operator for VectorView
     *
     * @param os Output stream
     * @param v VectorView to output
     * @return std::ostream& Output stream
     */
    template <Arithmetic T>
    std::ostream &operator<<(std::ostream &os, const VectorView<T> &v)
    {
        return os << static_cast<std::string>(v);
    }

}

#endif
