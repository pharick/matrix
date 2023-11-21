#include <catch2/catch_test_macros.hpp>

#include "Vector.hpp"

using namespace m42;

TEST_CASE("Vector construction from initializer list", "[Vector]")
{
    SECTION("Empty initializer list")
    {
        Vector<int> v{};
        REQUIRE(v.size() == 0);
        REQUIRE(v.data() == nullptr);
    }

    SECTION("Non-empty initializer list")
    {
        Vector<int> v{1, 2, 3};
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }
}

TEST_CASE("Vector construction from pointer to data", "[Vector]")
{
    int data[]{1, 2, 3};

    SECTION("Construction with valid size")
    {
        Vector<int> v(data, 3);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }

    SECTION("Construction with zero size")
    {
        Vector<int> v(data, 0);
        REQUIRE(v.size() == 0);
    }
}

TEST_CASE("Vector copy construction", "[Vector]")
{
    Vector<int> v1{1, 2, 3};

    Vector<int> v2(v1);
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}

TEST_CASE("Vector move construction", "[Vector]")
{
    Vector<int> v1{1, 2, 3};

    Vector<int> v2(std::move(v1));
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}

TEST_CASE("Vector assignment operator", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};

    v2 = v1;
    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}

TEST_CASE("Vector destruction", "[Vector]")
{
    Vector<int> *v = new Vector{1, 2, 3};
    REQUIRE_NOTHROW(delete v);
}

TEST_CASE("Modify copy of vector", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2 = v1;

    SECTION("Check copy")
    {
        REQUIRE(v2[0] == 1);
        REQUIRE(v2[1] == 2);
        REQUIRE(v2[2] == 3);
    }

    SECTION("Modify copy")
    {
        v2[0] = 4;
        v2[1] = 5;
        v2[2] = 6;

        REQUIRE(v1[0] == 1);
        REQUIRE(v1[1] == 2);
        REQUIRE(v1[2] == 3);
        REQUIRE(v2[0] == 4);
        REQUIRE(v2[1] == 5);
        REQUIRE(v2[2] == 6);
    }
}

TEST_CASE("Vector as string", "[Vector]")
{
    Vector<int> v{1, 2, 3};
    REQUIRE(std::string(v) == "[1 2 3]");
}

TEST_CASE("Vector equality", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{1, 2, 3};
    Vector<int> v3{4, 5, 6};

    REQUIRE(v1 == v2);
    REQUIRE(v1 != v3);
}

TEST_CASE("Reshape vector into matrix", "[Vector]")
{
    Vector<int> v{1, 2, 3, 4, 5, 6};
    Matrix<int> m = v.reshapeIntoMatrix(3, 2);

    REQUIRE(m.width() == 3);
    REQUIRE(m.height() == 2);
    REQUIRE(m == Matrix<int>({
        1, 3, 5,
        2, 4, 6,
    }, 3, 2));
}

TEST_CASE("Vector addition", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};

    Vector<int> result = v1 + v2;
    REQUIRE(result == Vector<int>({5, 7, 9}));
}

TEST_CASE("Vector subtraction", "[Vector]")
{
    Vector<int> v1{4, 5, 6};
    Vector<int> v2{1, 2, 3};

    Vector<int> result = v1 - v2;
    REQUIRE(result == Vector<int>({3, 3, 3}));
}

TEST_CASE("Vector addition assignment", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};

    v1 += v2;
    REQUIRE(v1 == Vector<int>({5, 7, 9}));
}

TEST_CASE("Vector subtraction assignment", "[Vector]")
{
    Vector<int> v1{4, 5, 6};
    Vector<int> v2{1, 2, 3};

    v1 -= v2;
    REQUIRE(v1 == Vector<int>({3, 3, 3}));
}

TEST_CASE("Multiply by scalar", "[Vector]")
{
    Vector<int> v{1, 2, 3};
    Vector<int> result = v * 2;
    REQUIRE(result == Vector<int>({2, 4, 6}));
}

TEST_CASE("Multiplication assignment", "[Vector]")
{
    Vector<int> v{1, 2, 3};
    v *= 2;
    REQUIRE(v == Vector<int>({2, 4, 6}));
}
