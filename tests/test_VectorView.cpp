#include <catch2/catch_test_macros.hpp>

#include "VectorView.hpp"

using namespace m42;

TEST_CASE("VectorView size and data", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(int);

    VectorView<int> vectorView(data, size);

    REQUIRE(vectorView.size() == size);
    REQUIRE(vectorView.data() == data);
}

TEST_CASE("VectorView element access", "[VectorView]")
{
    double data[]{1.1, 2.2, 3.3, 4.4, 5.5};
    size_t size = sizeof(data) / sizeof(double);

    VectorView<double> vectorView(data, size);

    for (size_t i = 0; i < size; i++)
    {
        REQUIRE(vectorView[i] == data[i]);
    }

    REQUIRE_THROWS_AS(vectorView[size], std::out_of_range);
}

TEST_CASE("VectorView string representation", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(int);

    VectorView<int> vectorView(data, size);

    REQUIRE(std::string(vectorView) == "[1 2 3 4 5]");
}

TEST_CASE("Modify vector elements", "[VectorView]")
{
    size_t data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(size_t);

    VectorView<size_t> vectorView(data, size);

    for (size_t i = 0; i < size; i++)
    {
        vectorView[i] = i;
    }

    for (size_t i = 0; i < size; i++)
    {
        REQUIRE(vectorView[i] == i);
        REQUIRE(data[i] == i);
    }
}

TEST_CASE("VectorView equality", "[VectorView]")
{
    int data1[]{1, 2, 3, 4, 5};
    int data2[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data1) / sizeof(int);

    VectorView<int> vectorView1(data1, size);
    VectorView<int> vectorView2(data2, size);

    REQUIRE(vectorView1 == vectorView2);
}

TEST_CASE("Reshape vector into matrix", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5, 6};
    size_t size = sizeof(data) / sizeof(int);
    VectorView<int> vectorView(data, size);

    REQUIRE(vectorView.reshape() == Matrix<int>{
        {1, 2, 3, 4, 5, 6},
    });
}

TEST_CASE("Const vector view", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(int);

    const VectorView<int> vectorView(data, size);

    REQUIRE(vectorView.size() == size);
    REQUIRE(vectorView.data() == data);

    for (size_t i = 0; i < size; i++)
    {
        REQUIRE(vectorView[i] == data[i]);
    }
}

TEST_CASE("VectorView addition", "[VectorView]")
{
    int data1[]{1, 2, 3};
    int data2[]{4, 5, 6};

    VectorView<int> v1(data1, 3);
    VectorView<int> v2(data2, 3);

    Vector<int> result = v1 + v2;

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == 5);
    REQUIRE(result[1] == 7);
    REQUIRE(result[2] == 9);
}

TEST_CASE("VectorView subtraction", "[VectorView]")
{
    int data1[]{4, 5, 6};
    int data2[]{1, 2, 3};

    VectorView<int> v1(data1, 3);
    VectorView<int> v2(data2, 3);

    Vector<int> result = v1 - v2;

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == 3);
    REQUIRE(result[1] == 3);
    REQUIRE(result[2] == 3);
}

TEST_CASE("VectorView addition assignment", "[VectorView]")
{
    int data1[]{1, 2, 3};
    int data2[]{4, 5, 6};

    VectorView<int> v1(data1, 3);
    VectorView<int> v2(data2, 3);

    v1 += v2;

    REQUIRE(v1.size() == 3);
    REQUIRE(v1[0] == 5);
    REQUIRE(v1[1] == 7);
    REQUIRE(v1[2] == 9);
}

TEST_CASE("VectorView subtraction assignment", "[VectorView]")
{
    int data1[]{4, 5, 6};
    int data2[]{1, 2, 3};

    VectorView<int> v1(data1, 3);
    VectorView<int> v2(data2, 3);

    v1 -= v2;

    REQUIRE(v1.size() == 3);
    REQUIRE(v1[0] == 3);
    REQUIRE(v1[1] == 3);
    REQUIRE(v1[2] == 3);
}

TEST_CASE("Multiply by scalar", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(int);

    VectorView<int> vectorView(data, size);

    Vector<int> result = vectorView * 2;

    REQUIRE(result.size() == size);
    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 4);
    REQUIRE(result[2] == 6);
    REQUIRE(result[3] == 8);
    REQUIRE(result[4] == 10);
}

TEST_CASE("Multiplication assignment", "[VectorView]")
{
    int data[]{1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(int);

    VectorView<int> vectorView(data, size);

    vectorView *= 2;

    REQUIRE(vectorView.size() == size);
    REQUIRE(vectorView[0] == 2);
    REQUIRE(vectorView[1] == 4);
    REQUIRE(vectorView[2] == 6);
    REQUIRE(vectorView[3] == 8);
    REQUIRE(vectorView[4] == 10);
}
