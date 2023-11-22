#include <catch2/catch_test_macros.hpp>

#include "Matrix.hpp"

using namespace m42;

TEST_CASE("Matrix construction", "[Matrix]")
{
    SECTION("Empty matrix")
    {
        Matrix<int> m;
        REQUIRE(m.width() == 0);
        REQUIRE(m.height() == 0);
        REQUIRE(m.data() == nullptr);
    }

    SECTION("Matrix with specified width and height")
    {
        Matrix<int> m(3, 2);
        REQUIRE(m.width() == 3);
        REQUIRE(m.height() == 2);
        REQUIRE(m.data() != nullptr);
    }

    SECTION("Matrix construction from initializer list")
    {
        Matrix<int> m({
            1, 2, 3,
            4, 5, 6,
        }, 3, 2);
        REQUIRE(m.width() == 3);
        REQUIRE(m.height() == 2);
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 4);
        REQUIRE(m[1][0] == 2);
        REQUIRE(m[1][1] == 5);
        REQUIRE(m[2][0] == 3);
        REQUIRE(m[2][1] == 6);
    }

    SECTION("Matrix construction from initializer list with invalid size")
    {
        REQUIRE_THROWS_AS(Matrix<int>({1, 2, 3, 4, 5}, 2, 3), std::invalid_argument);
    }

    SECTION("Matrix constructed from initializer list of initializer lists")
    {
        Matrix m1{
            {1, 2, 3},
            {4, 5, 6},
        };
        Matrix m2({
            1, 2, 3,
            4, 5, 6,
        }, 3, 2);
        REQUIRE(m1 == m2);
    }

    SECTION("Matrix construction from pointer to data")
    {
        int data[]{1, 2, 3, 4, 5, 6};
        Matrix<int> m(data, 3, 2);
        REQUIRE(m.width() == 3);
        REQUIRE(m.height() == 2);
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 2);
        REQUIRE(m[1][0] == 3);
        REQUIRE(m[1][1] == 4);
        REQUIRE(m[2][0] == 5);
        REQUIRE(m[2][1] == 6);
    }
}

TEST_CASE("Matrix copy construction", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    Matrix<int> m2(m1);
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 4);
    REQUIRE(m2[1][0] == 2);
    REQUIRE(m2[1][1] == 5);
    REQUIRE(m2[2][0] == 3);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix move construction", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    Matrix<int> m2(std::move(m1));
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 4);
    REQUIRE(m2[1][0] == 2);
    REQUIRE(m2[1][1] == 5);
    REQUIRE(m2[2][0] == 3);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix assignment operator", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Matrix<int> m2({
        7, 8, 9,
        10, 11, 12,
    }, 3, 2);

    m2 = m1;
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 4);
    REQUIRE(m2[1][0] == 2);
    REQUIRE(m2[1][1] == 5);
    REQUIRE(m2[2][0] == 3);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix destruction", "[Matrix]")
{
    Matrix<int> *m = new Matrix<int>({1, 2, 3, 4, 5, 6}, 3, 2);
    REQUIRE_NOTHROW(delete m);
}

TEST_CASE("Matrix indexing", "[Matrix]")
{
    Matrix<int> m({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    SECTION("Accessing elements using operator[]")
    {
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 4);
        REQUIRE(m[1][0] == 2);
        REQUIRE(m[1][1] == 5);
        REQUIRE(m[2][0] == 3);
        REQUIRE(m[2][1] == 6);
    }

    SECTION("Modifying elements using operator[]")
    {
        m[0][0] = 7;
        m[0][1] = 8;
        m[1][0] = 9;
        m[1][1] = 10;
        m[2][0] = 11;
        m[2][1] = 12;

        REQUIRE(m[0][0] == 7);
        REQUIRE(m[0][1] == 8);
        REQUIRE(m[1][0] == 9);
        REQUIRE(m[1][1] == 10);
        REQUIRE(m[2][0] == 11);
        REQUIRE(m[2][1] == 12);
    }
}

TEST_CASE("Matrix isSquare", "[Matrix]")
{
    SECTION("Non-Square matrix")
    {
        Matrix<int> m({1, 2, 3, 4, 5, 6}, 3, 2);
        REQUIRE(m.isSquare() == false);
    }

    SECTION("Square matrix")
    {
        Matrix<int> m({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
        REQUIRE(m.isSquare() == true);
    }
}

TEST_CASE("Matrix as string", "[Matrix]")
{
    Matrix<int> m({
        1, 2,
        3, 4,
        5, 6,
    }, 2, 3);
    // column-major order
    REQUIRE(std::string(m) == "[1 2\n 3 4\n 5 6]");
}

TEST_CASE("Access vectors of the matrix", "[Matrix]")
{
    Matrix<int> m({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    int d1[]{1, 4};
    int d2[]{2, 5};
    int d3[]{3, 6};

    SECTION("Accessing vectors using operator[]")
    {
        REQUIRE(m[0] == VectorView<int>(d1, 2));
        REQUIRE(m[1] == VectorView<int>(d2, 2));
        REQUIRE(m[2] == VectorView<int>(d3, 2));
    }

}

TEST_CASE("Assign matrix vector to variable", "[Matrix]")
{
    Matrix<int> m({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Vector<int> v = m[0];

    REQUIRE(v == Vector<int>({1, 4}));
    REQUIRE(v.size() == 2);
}

TEST_CASE("Assign vector to matrix column", "[Matrix]")
{
    Matrix<int> m(3, 2);
    m[0] = Vector<int>({1, 2});
    m[1] = Vector<int>({3, 4});
    m[2] = Vector<int>({5, 6});

    REQUIRE(m == Matrix<int>({
       1, 3, 5,
       2, 4, 6,
    }, 3, 2));
    REQUIRE(std::string(m) == "[1 3 5\n 2 4 6]");
}

TEST_CASE("Matrix equality", "[Matrix]")
{
    Matrix<int> m1({1, 2, 3, 4, 5, 6}, 3, 2);
    Matrix<int> m2({1, 2, 3, 4, 5, 6}, 3, 2);
    Matrix<int> m3({7, 8, 9, 10, 11, 12}, 3, 2);

    REQUIRE(m1 == m2);
    REQUIRE(m1 != m3);
}

TEST_CASE("Copy vector from one matrix to another", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Matrix<int> m2(3, 2);

    m2[0] = m1[0];
    m2[1] = m1[1];
    m2[2] = m1[2];

    REQUIRE(m2 == Matrix<int>({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2));

    m1[0] = Vector<int>({7, 8});
    m1[1] = Vector<int>({9, 10});
    m1[2] = Vector<int>({11, 12});

    REQUIRE(m1 == Matrix<int>({
        7, 9,  11,
        8, 10, 12,
    }, 3, 2));
    REQUIRE(m2 == Matrix<int>({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2));
}

TEST_CASE("Assign vector of wrong size", "[Matrix]")
{
    Matrix<int> m(3, 2);
    REQUIRE_THROWS_AS(m[0] = Vector<int>({1, 2, 3}), std::invalid_argument);
}

TEST_CASE("Multiply matrix column by scalar", "[Matrix]")
{
    Matrix<int> m1({
        1, 3,
        2, 4,
    }, 2, 2);

    Matrix<int> m2(3, 2);

    m2[0] = m1[0] * 2;
    m2[1] = m1[1] * 3;
    m2[2] = m1[0] * 4;

    REQUIRE(m2 == Matrix<int>({
        2, 9,  4,
        4, 12, 8,
    }, 3, 2));
}

TEST_CASE("Reshape matrix into vector", "[Matrix]")
{
    Matrix<int> m({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Vector<int> v = m.reshapeIntoVector();

    REQUIRE(v == Vector<int>({1, 4, 2, 5, 3, 6}));
}

TEST_CASE("Matrix addition", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Matrix<int> m2({
        7, 8, 9,
        10, 11, 12,
    }, 3, 2);

    Matrix<int> result = m1 + m2;
    REQUIRE(result == Matrix<int>({
        8, 10, 12,
        14, 16, 18,
    }, 3, 2));
}

TEST_CASE("Matrix subtraction", "[Matrix]")
{
    Matrix<int> m1({
        7, 8, 9,
        10, 11, 12,
    }, 3, 2);
    Matrix<int> m2({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    Matrix<int> result = m1 - m2;
    REQUIRE(result == Matrix<int>({
        6, 6, 6,
        6, 6, 6,
    }, 3, 2));
}

TEST_CASE("Matrix addition assignment", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);
    Matrix<int> m2({
        7, 8, 9,
        10, 11, 12,
    }, 3, 2);

    m1 += m2;
    REQUIRE(m1 == Matrix<int>({
        8, 10, 12,
        14, 16, 18,
    }, 3, 2));
}

TEST_CASE("Matrix subtraction assignment", "[Matrix]")
{
    Matrix<int> m1({
        7, 8, 9,
        10, 11, 12,
    }, 3, 2);
    Matrix<int> m2({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    m1 -= m2;
    REQUIRE(m1 == Matrix<int>({
        6, 6, 6,
        6, 6, 6,
    }, 3, 2));
}

TEST_CASE("Multiply matrix by scalar", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    Matrix<int> result = m1 * 2;
    REQUIRE(result == Matrix<int>({
        2, 4, 6,
        8, 10, 12,
    }, 3, 2));
}

TEST_CASE("Multiplication assignment", "[Matrix]")
{
    Matrix<int> m1({
        1, 2, 3,
        4, 5, 6,
    }, 3, 2);

    m1 *= 2;
    REQUIRE(m1 == Matrix<int>({
        2, 4, 6,
        8, 10, 12,
    }, 3, 2));
}
