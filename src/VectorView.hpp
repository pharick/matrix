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
        VectorView() = delete;
        VectorView(T *data, size_t size);
        VectorView(const VectorView &other) = default;
        VectorView &operator=(const VectorView &other) = default;
        ~VectorView() = default;

        size_t size() const;
        T *data();
        const T *data() const;
        Matrix<T> reshapeIntoMatrix(size_t width, size_t height) const;

        T &operator[](size_t index);
        const T &operator[](size_t index) const;
        bool operator==(const VectorView &other) const;
        Vector<T> operator+(const VectorView &other) const;
        Vector<T> operator-(const VectorView &other) const;
        VectorView<T> &operator+=(const VectorView &other);
        VectorView<T> &operator-=(const VectorView &other);
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
     * @brief Reshape vector to a matrix
     *
     * @param width Width of matrix
     * @param height Height of matrix
     * @return Matrix<T> Matrix with vector data
     */
    template <Arithmetic T>
    Matrix<T> VectorView<T>::reshapeIntoMatrix(size_t width, size_t height) const
    {
        if (width * height != _size)
            throw std::invalid_argument("Invalid matrix size");
        return Matrix<T>(_data, width, height);
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
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return _data[index];
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
        if (_size != other._size)
            throw std::invalid_argument("Vectors must be of the same size");
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; i++)
            result[i] = _data[i] - other._data[i];
        return result;
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
        if (_size != other._size)
            throw std::invalid_argument("Vectors must be of the same size");
        for (size_t i = 0; i < _size; i++)
            _data[i] += other._data[i];
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
        if (_size != other._size)
            throw std::invalid_argument("Vectors must be of the same size");
        for (size_t i = 0; i < _size; i++)
            _data[i] -= other._data[i];
        return *this;
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
