#ifndef M42_MATRIX_HPP
#define M42_MATRIX_HPP

#include <cstddef>
#include <string>
#include <ostream>
#include <utility>

#include "common.hpp"
#include "Vector.hpp"

namespace m42
{

    template <Arithmetic T>
    class VectorView;

    template <Arithmetic T>
    class Vector;

    /**
     * @brief Matrix class
     * 
     * @tparam T Type of matrix components
     */
    template <Arithmetic T>
    class Matrix
    {
    private:
        T *_data;
        size_t _width;
        size_t _height;

    public:
        Matrix();
        Matrix(size_t width, size_t height);
        Matrix(std::initializer_list<T> list, size_t width, size_t height);
        Matrix(const T *data, size_t width, size_t height);
        Matrix(const Matrix &other);
        Matrix(Matrix &&other) noexcept;
        Matrix &operator=(Matrix other);
        ~Matrix();

        size_t width() const;
        size_t height() const;
        bool isSquare() const;
        T *data();
        const T *data() const;
        Vector<T> reshapeIntoVector() const;

        VectorView<T> operator[](size_t i);
        const VectorView<T> operator[](size_t i) const;
        bool operator==(const Matrix &other) const;
        operator std::string() const;
    };

    /**
     * @brief Construct an empty Matrix object
     */
    template <Arithmetic T>
    Matrix<T>::Matrix() : _data(nullptr), _width(0), _height(0) {}

    /**
     * @brief Construct a new Matrix object with the given width and height
     * 
     * @param width Width of the matrix
     * @param height Height of the matrix
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(size_t width, size_t height) : _data(new T[width * height]), _width(width), _height(height) {}

    /**
     * @brief Construct a new Matrix object from an initializer list
     * 
     * @param list Initializer list
     * @param width Width of the matrix
     * @param height Height of the matrix
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(std::initializer_list<T> list, size_t width, size_t height) : Matrix(width, height)
    {
        if (list.size() != width * height)
            throw std::invalid_argument("Invalid initializer list size");
        size_t i = 0;
        for (auto &elem : list)
            _data[i++] = elem;
    }

    /**
     * @brief Construct a new Matrix object from a pointer to the matrix data
     * 
     * @param data Pointer to the matrix data
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(const T *data, size_t width, size_t height) : Matrix(width, height)
    {
        for (size_t i = 0; i < width * height; i++)
            _data[i] = data[i];
    }

    /**
     * @brief Copy constructor
     * 
     * @param other Matrix to copy
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(const Matrix &other) : Matrix(other._width, other._height)
    {
        for (size_t i = 0; i < _width * _height; i++)
            _data[i] = other._data[i];
    }

    /**
     * @brief Move constructor
     * 
     * @param other Matrix to move
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(Matrix &&other) noexcept : _data(std::move(other._data)), _width(other._width), _height(other._height)
    {
        other._data = nullptr;
        other._width = 0;
        other._height = 0;
    }

    /**
     * @brief Assignment operator
     * 
     * @param other Right-hand side of the assignment
     * @return Matrix<T, W, H>& Left-hand side after assignment
     */
    template <Arithmetic T>
    Matrix<T> &Matrix<T>::operator=(Matrix<T> other)
    {
        // copy and swap idiom
        std::swap(_data, other._data);
        std::swap(_width, other._width);
        std::swap(_height, other._height);
        return *this;
    }

    /**
     * @brief Destroy the Matrix object
     */
    template <Arithmetic T>
    Matrix<T>::~Matrix()
    {
        delete[] _data;
    }

    /**
     * @brief Return the width of the matrix
     * 
     * @return size_t Width of the matrix
     */
    template <Arithmetic T>
    size_t Matrix<T>::width() const
    {
        return _width;
    }

    /**
     * @brief Return the height of the matrix
     * 
     * @return size_t Height of the matrix
     */
    template <Arithmetic T>
    size_t Matrix<T>::height() const
    {
        return _height;
    }

    /**
     * @brief Return whether the matrix is square
     * 
     * @tparam T Type of matrix components
     * @return bool Whether the matrix is square
     */
    template <Arithmetic T>
    bool Matrix<T>::isSquare() const
    {
        return _width == _height;
    }

    /**
     * @brief Return a pointer to the matrix data
     * 
     * @return const T* Pointer to the matrix data
     */
    template <Arithmetic T>
    T *Matrix<T>::data()
    {
        return _data;
    }

    /**
     * @brief Return a const pointer to the matrix data
     * 
     * @return const T* Const pointer to the matrix data
     */
    template <Arithmetic T>
    const T *Matrix<T>::data() const
    {
        return _data;
    }

    /**
     * @brief Reshape the matrix into a vector
     * 
     * @return Vector<T> Vector with matrix data
     */
    template <Arithmetic T>
    Vector<T> Matrix<T>::reshapeIntoVector() const
    {
        return Vector<T>(_data, _width * _height);
    }

    /**
     * @brief Return an i-th vector of the matrix
     * 
     * @param i Index of the vector
     * @return VectorView<T> i-th vector of the matrix
     */
    template <Arithmetic T>
    VectorView<T> Matrix<T>::operator[](size_t i)
    {
        return VectorView(_data + i * _height, _height);
    }

    /**
     * @brief Return an i-th vector of the matrix
     * 
     * @param i Index of the vector
     * @return Vector<const T> i-th vector of the matrix
     */
    template <Arithmetic T>
    const VectorView<T> Matrix<T>::operator[](size_t i) const
    {
        return VectorView(_data + i * _height, _height);
    }

    /**
     * @brief Return whether the matrix is equal to another matrix
     * 
     * @param other Matrix to compare to
     * @return bool Whether the matrix is equal to the other matrix
     */
    template <Arithmetic T>
    bool Matrix<T>::operator==(const Matrix<T> &other) const
    {
        if (_width != other._width || _height != other._height)
            return false;
        for (size_t i = 0; i < _width; i++)
            if ((*this)[i] != other[i])
                return false;
        return true;
    }

    /**
     * @brief Return a string representation of the matrix
     * 
     * @return std::string String representation of the matrix
     */
    template <Arithmetic T>
    Matrix<T>::operator std::string() const
    {
        // column-major order
        std::string str = "[";
        for (size_t i = 0; i < _width; i++)
        {
            for (size_t j = 0; j < _height; j++)
            {
                str += std::to_string(_data[j * _width + i]);
                if (j < _height - 1)
                    str += " ";
            }
            if (i < _width - 1)
                str += "\n ";
        }
        str += "]";
        return str;
    }

    /**
     * @brief fmt::formatter specialization for Matrix
     * 
     * @param v Matrix to format
     * @return auto Matrix formatted as a string
     */
    template <Arithmetic T>
    auto format_as(const Matrix<T> &v)
    {
        return static_cast<std::string>(v);
    }
    
    /**
     * @brief Output stream operator for Matrix
     * 
     * @param os Output stream
     * @param m Matrix to output
     * @return std::ostream& Output stream
     */
    template <Arithmetic T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &m)
    {
        return os << static_cast<std::string>(m);
    }

}

#endif
