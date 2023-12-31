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
        using value_type = T;

        Matrix();
        Matrix(size_t width, size_t height);
        Matrix(std::initializer_list<T> list, size_t width, size_t height);
        Matrix(std::initializer_list<std::initializer_list<T>> list);
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
        Vector<T> reshape() const;
        Vector<T> row(size_t i) const;
        void setRow(size_t i, const Vector<T> &vector);
        T trace() const;
        Matrix transpose() const;
        bool isAprrox(const Matrix &other, double epsilon = 1e-8) const;
        Matrix rowEchelon() const;
        T determinant() const;
        Matrix inverse() const;
        T cofactor(size_t i, size_t j) const;
        Matrix getSubmatrix(size_t i, size_t j) const;
        size_t rank() const;

        VectorView<T> operator[](size_t i);
        const VectorView<T> operator[](size_t i) const;
        bool operator==(const Matrix &other) const;
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix &operator+=(const Matrix &other);
        Matrix &operator-=(const Matrix &other);
        Matrix operator*(T scalar) const;
        Matrix &operator*=(T scalar);
        Vector<T> operator*(const Vector<T> &vector) const;
        Matrix operator*(const Matrix &other) const;
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
        // row-major order to column-major order
        for (size_t i = 0; i < width; i++)
            for (size_t j = 0; j < height; j++)
                (*this)[i][j] = *(list.begin() + j * width + i);
    }

    /**
     * @brief Construct a new Matrix object from an initializer list of initializer lists
     *
     * @param list Initializer list of initializer lists
     */
    template <Arithmetic T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) : Matrix(list.begin()->size(), list.size())
    {
        for (size_t i = 0; i < _height; i++)
            if ((list.begin() + i)->size() != _width)
                throw std::invalid_argument("All rows must have the same size");
        // row-major order to column-major order
        for (size_t i = 0; i < _width; i++)
            for (size_t j = 0; j < _height; j++)
                (*this)[i][j] = *((list.begin() + j)->begin() + i);
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
     * @brief Reshape the matrix with height 1 into a vector
     *
     * @return Vector<T> Reshaped matrix
     */
    template <Arithmetic T>
    Vector<T> Matrix<T>::reshape() const
    {
        if (_height > 1)
            throw std::invalid_argument("Matrix must be a row vector");
        return Vector<T>(_data, _width * _height);
    }

    /**
     * @brief Return an i-th row of the matrix
     *
     * @param i Index of the row
     * @return Vector<T> i-th row of the matrix
     */
    template <Arithmetic T>
    Vector<T> Matrix<T>::row(size_t i) const
    {
        // data is stored in column-major order
        Vector<T> result(_width);
        for (size_t j = 0; j < _width; j++)
            result[j] = (*this)[j][i];
        return result;
    }

    /**
     * @brief Set an i-th row of the matrix
     *
     * @param i Index of the row
     * @param vector Vector to set the row to
     */
    template <Arithmetic T>
    void Matrix<T>::setRow(size_t i, const Vector<T> &vector)
    {
        if (_width != vector.size())
            throw std::invalid_argument("Matrix width must be equal to vector size");
        // data is stored in column-major order
        for (size_t j = 0; j < _width; j++)
            (*this)[j][i] = vector[j];
    }

    /**
     * @brief Return the trace of the matrix
     *
     * @return T Trace of the matrix
     */
    template <Arithmetic T>
    T Matrix<T>::trace() const
    {
        if (!isSquare())
            throw std::invalid_argument("Matrix must be square");
        T result = 0;
        for (size_t i = 0; i < _width; i++)
            result += (*this)[i][i];
        return result;
    }

    /**
     * @brief Return the transpose of the matrix
     *
     * @return Matrix<T> Transpose of the matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Matrix<T> result(_height, _width);
        for (size_t i = 0; i < _height; i++)
            result[i] = row(i);
        return result;
    }

    /**
     * @brief Return whether the matrix is approximately equal to another matrix
     *
     * @param other Matrix to compare to
     * @param epsilon Epsilon
     * @return bool Whether the matrix is approximately equal to the other matrix
     */
    template <Arithmetic T>
    bool Matrix<T>::isAprrox(const Matrix<T> &other, double epsilon) const
    {
        if (_width != other._width || _height != other._height)
            return false;
        for (size_t i = 0; i < _width; i++)
            if (!(*this)[i].isApprox(other[i], epsilon))
                return false;
        return true;
    }

    /**
     * @brief Return the row echelon form of the matrix
     *
     * @return Matrix<T> Row echelon form of the matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::rowEchelon() const
    {
        Matrix<T> result(*this);
        size_t row = 0;
        size_t col = 0;
        while (row < _height && col < _width)
        {
            // find pivot
            size_t pivot = row;
            for (size_t i = row + 1; i < _height; i++)
                if (std::abs(result[col][i]) > std::abs(result[col][pivot]))
                    pivot = i;
            if (result[col][pivot] == 0)
            {
                col++;
                continue;
            }
            // swap rows
            if (pivot != row)
            {
                Vector tmp = result.row(pivot);
                result.setRow(pivot, result.row(row));
                result.setRow(row, tmp);
            }
            result.setRow(row, result.row(row) / result[col][row]);
            // subtract row from other rows
            for (size_t i = 0; i < _height; i++)
                if (i != row)
                    result.setRow(i, result.row(i) - result.row(row) * result[col][i]);
            row++;
            col++;
        }
        return result;
    }

    /**
     * @brief Return the determinant of the matrix
     *
     * @return T Determinant of the matrix
     */
    template <Arithmetic T>
    T Matrix<T>::determinant() const
    {
        if (!isSquare())
            throw std::invalid_argument("Matrix must be square");
        // Laplace expansion
        if (_width == 1)
            return (*this)[0][0];
        T result = 0;
        for (size_t i = 0; i < _width; i++)
            result += (*this)[i][0] * cofactor(i, 0);
        return result;
    }

    /**
     * @brief Return the inverse of the matrix
     *
     * @return Matrix<T> Inverse of the matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::inverse() const
    {
        if (!isSquare())
            throw std::invalid_argument("Matrix must be square");
        if (determinant() == 0)
            throw std::invalid_argument("Matrix must be invertible");
        Matrix<T> result(_width, _height);
        for (size_t i = 0; i < _width; i++)
            for (size_t j = 0; j < _height; j++)
                result[i][j] = cofactor(j, i);
        return result * (1 / determinant());
    }

    /**
     * @brief Return the cofactor of the matrix
     *
     * @param i Row index
     * @param j Column index
     * @return T Cofactor of the matrix
     */
    template <Arithmetic T>
    T Matrix<T>::cofactor(size_t i, size_t j) const
    {
        if (!isSquare())
            throw std::invalid_argument("Matrix must be square");
        if (_width == 1)
            return 1;
        // Laplace expansion
        Matrix<T> submatrix = getSubmatrix(i, j);
        return std::pow(-1, i + j) * submatrix.determinant();
    }

    /**
     * @brief Return the submatrix of the matrix
     *
     * @param i Row index
     * @param j Column index
     * @return Matrix<T> Submatrix of the matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::getSubmatrix(size_t i, size_t j) const
    {
        if (!isSquare())
            throw std::invalid_argument("Matrix must be square");
        Matrix<T> result(_width - 1, _height - 1);
        size_t row = 0;
        size_t col = 0;
        for (size_t k = 0; k < _width; k++)
        {
            if (k == i)
                continue;
            for (size_t l = 0; l < _height; l++)
            {
                if (l == j)
                    continue;
                result[col][row] = (*this)[k][l];
                row++;
            }
            row = 0;
            col++;
        }
        return result;
    }

    /**
     * @brief Return the rank of the matrix
     *
     * @return size_t Rank of the matrix
     */
    template <Arithmetic T>
    size_t Matrix<T>::rank() const
    {
        Matrix echelon = rowEchelon();
        size_t rank = 0;
        for (size_t i = 0; i < _height; i++)
        {
            bool isZero = true;
            for (size_t j = 0; j < _width; j++)
                if (echelon[j][i] != 0)
                    isZero = false;
            if (!isZero)
                rank++;
        }
        return rank;
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
        if (_data == other._data)
            return true;
        for (size_t i = 0; i < _width; i++)
            if ((*this)[i] != other[i])
                return false;
        return true;
    }

    /**
     * @brief Return the sum of the matrix and another matrix
     *
     * @param other Matrix to add
     * @return Matrix<T> Sum of the matrix and the other matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
    {
        if (_width != other._width || _height != other._height)
            throw std::invalid_argument("Matrices must have the same size");
        Matrix<T> result(_width, _height);
        for (size_t i = 0; i < _width; i++)
            result[i] = (*this)[i] + other[i];
        return result;
    }

    /**
     * @brief Return the difference of the matrix and another matrix
     *
     * @param other Matrix to subtract
     * @return Matrix<T> Difference of the matrix and the other matrix
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
    {
        if (_width != other._width || _height != other._height)
            throw std::invalid_argument("Matrices must have the same size");
        Matrix<T> result(_width, _height);
        for (size_t i = 0; i < _width; i++)
            result[i] = (*this)[i] - other[i];
        return result;
    }

    /**
     * @brief Add another matrix to the matrix
     *
     * @param other Matrix to add
     * @return Matrix<T>& Result of addition
     */
    template <Arithmetic T>
    Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
    {
        (*this) = (*this) + other;
        return *this;
    }

    /**
     * @brief Subtract another matrix from the matrix
     *
     * @param other Matrix to subtract
     * @return Matrix<T>& Result of subtraction
     */
    template <Arithmetic T>
    Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
    {
        (*this) = (*this) - other;
        return *this;
    }

    /**
     * @brief Multiply the matrix by a scalar
     *
     * @param scalar Scalar to multiply by
     * @return Matrix<T> Result of multiplication
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::operator*(T scalar) const
    {
        Matrix<T> result(_width, _height);
        for (size_t i = 0; i < _width; i++)
            result[i] = (*this)[i] * scalar;
        return result;
    }

    /**
     * @brief Multiply the matrix by a scalar and assign the result to the matrix
     *
     * @param scalar Scalar to multiply by
     * @return Matrix<T>& Result of multiplication
     */
    template <Arithmetic T>
    Matrix<T> &Matrix<T>::operator*=(T scalar)
    {
        (*this) = (*this) * scalar;
        return *this;
    }

    /**
     * @brief Multiply the matrix by a vector
     *
     * @param vector Vector to multiply by
     * @return Matrix<T> Result of multiplication
     */
    template <Arithmetic T>
    Vector<T> Matrix<T>::operator*(const Vector<T> &vector) const
    {
        if (_width != vector.size())
            throw std::invalid_argument("Matrix width must be equal to vector size");
        Vector<T> result(_height);
        for (size_t i = 0; i < _height; i++)
            result[i] = (*this).row(i) * vector;
        return result;
    }

    /**
     * @brief Multiply the matrix by another matrix
     *
     * @param other Matrix to multiply by
     * @return Matrix<T> Result of multiplication
     */
    template <Arithmetic T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
    {
        if (_width != other._height)
            throw std::invalid_argument("Matrix width must be equal to other matrix height");
        Matrix<T> result(other._width, _height);
        for (size_t i = 0; i < other._width; i++)
            result[i] = (*this) * other[i];
        return result;
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
        for (size_t i = 0; i < _height; i++)
        {
            for (size_t j = 0; j < _width; j++)
            {
                str += std::to_string((*this)[j][i]);
                if (j != _width - 1)
                    str += " ";
                else if (i != _height - 1)
                    str += "\n ";
            }
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
