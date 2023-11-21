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
        Matrix<int> m({1, 2, 3, 4, 5, 6}, 3, 2);
        REQUIRE(m.width() == 3);
        REQUIRE(m.height() == 2);
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 2);
        REQUIRE(m[1][0] == 3);
        REQUIRE(m[1][1] == 4);
        REQUIRE(m[2][0] == 5);
        REQUIRE(m[2][1] == 6);
    }

    SECTION("Matrix construction from initializer list with invalid size")
    {
        REQUIRE_THROWS_AS(Matrix<int>({1, 2, 3, 4, 5}, 2, 3), std::invalid_argument);
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
    Matrix<int> m1({1, 2, 3, 4, 5, 6}, 3, 2);

    Matrix<int> m2(m1);
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 2);
    REQUIRE(m2[1][0] == 3);
    REQUIRE(m2[1][1] == 4);
    REQUIRE(m2[2][0] == 5);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix move construction", "[Matrix]")
{
    Matrix<int> m1({1, 2, 3, 4, 5, 6}, 3, 2);

    Matrix<int> m2(std::move(m1));
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 2);
    REQUIRE(m2[1][0] == 3);
    REQUIRE(m2[1][1] == 4);
    REQUIRE(m2[2][0] == 5);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix assignment operator", "[Matrix]")
{
    Matrix<int> m1({1, 2, 3, 4, 5, 6}, 3, 2);
    Matrix<int> m2({7, 8, 9, 10, 11, 12}, 3, 2);

    m2 = m1;
    REQUIRE(m2.width() == 3);
    REQUIRE(m2.height() == 2);
    REQUIRE(m2[0][0] == 1);
    REQUIRE(m2[0][1] == 2);
    REQUIRE(m2[1][0] == 3);
    REQUIRE(m2[1][1] == 4);
    REQUIRE(m2[2][0] == 5);
    REQUIRE(m2[2][1] == 6);
}

TEST_CASE("Matrix destruction", "[Matrix]")
{
    Matrix<int> *m = new Matrix<int>({1, 2, 3, 4, 5, 6}, 3, 2);
    REQUIRE_NOTHROW(delete m);
}

TEST_CASE("Matrix indexing", "[Matrix]")
{
    Matrix<int> m({1, 2, 3, 4, 5, 6}, 3, 2);

    SECTION("Accessing elements using operator[]")
    {
        REQUIRE(m[0][0] == 1);
        REQUIRE(m[0][1] == 2);
        REQUIRE(m[1][0] == 3);
        REQUIRE(m[1][1] == 4);
        REQUIRE(m[2][0] == 5);
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
    Matrix<int> m({1, 2, 3, 4, 5, 6}, 2, 3);
    // column-major order
    REQUIRE(std::string(m) == "[1 3 5\n 2 4 6]");
}

TEST_CASE("Access vectors of the matrix", "[Matrix]")
{
    int d1[]{1, 2};
    int d2[]{3, 4};
    int d3[]{5, 6};
    Matrix<int> m({1, 2, 3, 4, 5, 6}, 3, 2);

    SECTION("Accessing vectors using operator[]")
    {
        REQUIRE(m[0] == VectorView<int>(d1, 2));
        REQUIRE(m[1] == VectorView<int>(d2, 2));
        REQUIRE(m[2] == VectorView<int>(d3, 2));
    }

}