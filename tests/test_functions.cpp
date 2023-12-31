#include <catch2/catch_test_macros.hpp>
#include <fstream>

#include "functions.hpp"
#include "Matrix.hpp"

using namespace m42;

TEST_CASE("Linear combination of vectors", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};
    Vector<int> result = linearCombination({v1, v2}, {2, 3});
    REQUIRE(result == Vector<int>({14, 19, 24}));
}

TEST_CASE("Linear combinations invalid arguments", "[Vector]")
{
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};
    Vector<int> v3{1, 2};

    SECTION("Vectors and coefficients collections must be of the same size")
    {
        REQUIRE_THROWS_AS(linearCombination({v1, v2}, {2}), std::invalid_argument);
    }

    SECTION("Vectors must be of the same size")
    {
        REQUIRE_THROWS_AS(linearCombination({v1, v3}, {2, 3}), std::invalid_argument);
    }
}

TEST_CASE("Linear interpolations for two scalars")
{
    REQUIRE(lerp(1, 2, 0) == 1);
    REQUIRE(lerp(1, 2, 1) == 2);
    REQUIRE(lerp(1, 2, 2) == 3);

    REQUIRE(lerp(0.0, 1.0, 0.0) == 0.0);
    REQUIRE(lerp(0.0, 1.0, 1.0) == 1.0);
    REQUIRE(lerp(0.0, 1.0, 0.5) == 0.5);
    REQUIRE(lerp(21.0, 42.0, 0.3) == 27.3);
}

TEST_CASE("Linear interpolations for two vectors")
{
    Vector v1{1.0, 2.0, 3.0};
    Vector v2{4.0, 5.0, 6.0};
    Vector result = lerp(v1, v2, 0.5);
    REQUIRE(result == Vector{2.5, 3.5, 4.5});

    REQUIRE(lerp(Vector{2.0, 1.0}, Vector{4.0, 2.0}, 0.3) == Vector{2.6, 1.3});
}

TEST_CASE("Linear interpolation for two matrices")
{
    Matrix m1{
        {2.0, 1.0},
        {3.0, 4.0},
    };
    Matrix m2{
        {20.0, 10.0},
        {30.0, 40.0},
    };
    REQUIRE(lerp(m1, m2, 0.5) == Matrix{
        {11.0, 5.5},
        {16.5, 22.0},
    });
}

TEST_CASE("Cosine of angle between two vectors")
{
    REQUIRE(angleCos(Vector{1.0, 0.0}, Vector{1.0, 0.0}) == 1.0);
    REQUIRE(angleCos(Vector{1.0, 0.0}, Vector{0.0, 1.0}) == 0.0);
    // compare floating point numbers with a tolerance
    REQUIRE(angleCos(Vector{-1.0, 1.0}, Vector{1.0, -1.0}) - -1.0 < 1e-6);
    REQUIRE(angleCos(Vector{2.0, 1.0}, Vector{4.0, 2.0}) - 1.0 < 1e-6);
    REQUIRE(angleCos(Vector{1.0, 2.0, 3.0}, Vector{4.0, 5.0, 6.0}) - 0.974631846 < 1e-6);

    REQUIRE(angleCos(Vector{1.0, 2.0, 3.0}, Vector{4.0, 5.0, 6.0}) == angleCos(Vector{4.0, 5.0, 6.0}, Vector{1.0, 2.0, 3.0}));
}

TEST_CASE("Cross product of two vectors")
{
    REQUIRE(crossProduct(Vector{1.0, 0.0, 0.0}, Vector{0.0, 1.0, 0.0}) == Vector{0.0, 0.0, 1.0});
    REQUIRE(crossProduct(Vector{1.0, 0.0, 0.0}, Vector{0.0, 0.0, 1.0}) == Vector{0.0, -1.0, 0.0});
    REQUIRE(crossProduct(Vector{0.0, 1.0, 0.0}, Vector{0.0, 0.0, 1.0}) == Vector{1.0, 0.0, 0.0});
    REQUIRE(crossProduct(Vector{1.0, 2.0, 3.0}, Vector{4.0, 5.0, 6.0}) == Vector{-3.0, 6.0, -3.0});
    REQUIRE(crossProduct(Vector{1.0, 2.0, 3.0}, Vector{4.0, 5.0, 6.0}) == -crossProduct(Vector{4.0, 5.0, 6.0}, Vector{1.0, 2.0, 3.0}));
    REQUIRE(crossProduct(Vector{0.0, 0.0, 1.0}, Vector{1.0, 0.0, 0.0}) == Vector{0.0, 1.0, 0.0});
    REQUIRE(crossProduct(Vector{1.0, 2.0, 3.0}, Vector{4.0, 5.0, 6.0}) == Vector{-3.0, 6.0, -3.0});
    REQUIRE(crossProduct(Vector{4.0, 2.0, -3.0}, Vector{-2.0, -5.0, 16.0}) == Vector{17.0, -58.0, -16.0});
}

TEST_CASE("Projection matrix")
{
    Matrix proj =
        makeProjectionMatrix(M_PI / 4.0f, 1.0f, 1.0f, 100.0f);
    std::ofstream file("display_macos/proj", std::ios::out | std::ios::trunc);
    for (size_t i = 0; i < proj.width(); i++)
    {
        for (size_t j = 0; j < proj.height(); j++)
        {
            file << proj[j][i];
            if (j < proj.width() - 1)
                file << ", ";
        }
        file << std::endl;
    }
    file.close();
}
