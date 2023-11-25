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

TEST_CASE("Get matrix column and row", "[Matrix]")
{
    Matrix m{
        {1, 2, 3},
        {4, 5, 6},
    };

    REQUIRE(m[0] == Vector{1, 4});
    REQUIRE(m[1] == Vector{2, 5});
    REQUIRE(m[2] == Vector{3, 6});

    REQUIRE(m.row(0) == Vector{1, 2, 3});
    REQUIRE(m.row(1) == Vector{4, 5, 6});
}

TEST_CASE("Matrix vector multiplication", "[Matrix]")
{
    Matrix m{
        {1, 0},
        {0, 1},
    };
    Vector v{4, 2};
    REQUIRE(m * v == Vector{4, 2});

    Matrix m2{
        {2, 0},
        {0, 2},
    };
    Vector v2{4, 2};
    REQUIRE(m2 * v2 == Vector{8, 4});

    Matrix m3{
        {2, -2},
        {-2, 2},
    };
    Vector v3{4, 2};
    REQUIRE(m3 * v3 == Vector{4, -4});
}

TEST_CASE("Matrix matrix multiplication", "[Matrix]")
{
    Matrix m1{
        {1, 0},
        {0, 1},
    };
    Matrix m2{
        {1, 0},
        {0, 1},
    };
    REQUIRE(m1 * m2 == Matrix{
        {1, 0},
        {0, 1},
    });

    Matrix m3{
        {1, 0},
        {0, 1},
    };
    Matrix m4{
        {2, 1},
        {4, 2},
    };
    REQUIRE(m3 * m4 == Matrix{
        {2, 1},
        {4, 2},
    });

    Matrix m5{
        {3, -5},
        {6, 8},
    };
    Matrix m6{
        {2, 1},
        {4, 2},
    };
    REQUIRE(m5 * m6 == Matrix{
        {-14, -7},
        {44, 22},
    });
}

TEST_CASE("Trace of a matrix", "[Matrix]")
{
    Matrix m{
        {1, 0},
        {0, 1},
    };
    REQUIRE(m.trace() == 2);

    Matrix m2{
        { 2, -5, 0},
        { 4,  3, 7},
        {-2,  3, 4},
    };
    REQUIRE(m2.trace() == 9);

    Matrix m3{
        {-2, -8,  4},
        { 1, -23, 4},
        { 0,  6,  4},
    };
    REQUIRE(m3.trace() == -21);
}

TEST_CASE("Transpose matrix", "[Matrix]")
{
    Matrix m{
        {1, 2, 3},
        {4, 5, 6},
    };
    REQUIRE(m.transpose() == Matrix{
        {1, 4},
        {2, 5},
        {3, 6},
    });
}

TEST_CASE("Set row of a matrix", "[Matrix]")
{
    Matrix m{
        {1, 2, 3},
        {4, 5, 6},
    };
    m.setRow(0, Vector{7, 8, 9});
    REQUIRE(m == Matrix{
        {7, 8, 9},
        {4, 5, 6},
    });
}

TEST_CASE("Swap rows of a matrix", "[Matrix]")
{
    Matrix m{
        {1, 2, 3},
        {4, 5, 6},
    };
    Vector tmp = m.row(0);
    m.setRow(0, m.row(1));
    m.setRow(1, tmp);
    REQUIRE(m == Matrix{
        {4, 5, 6},
        {1, 2, 3},
    });
}

TEST_CASE("Row echelon form", "[Matrix]")
{
    Matrix m{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
    REQUIRE(m.rowEchelon() == Matrix{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    });

    Matrix m2{
        {1, 2},
        {3, 4},
    };
    REQUIRE(m2.rowEchelon() == Matrix{
        {1, 0},
        {0, 1},
    });

    Matrix m3{
        {1, 2},
        {2, 4},
    };
    REQUIRE(m3.rowEchelon() == Matrix{
        {1, 2},
        {0, 0},
    });

    Matrix m4{
        {8.0, 5.0, -2.0,  4.0,  28.0},
        {4.0, 2.5,  20.0, 4.0, -4.0},
        {8.0, 5.0,  1.0,  4.0,  17.0},
    };
    REQUIRE(m4.rowEchelon().isAprrox(Matrix{
        {1.0, 0.625, 0.0, 0.0, -12.1666667},
        {0.0, 0.0,   1.0, 0.0, -3.6666667},
        {0.0, 0.0,   0.0, 1.0,  29.5},
    }, 1e-7));
}

TEST_CASE("Calculate determinant of a matrix", "[Matrix]")
{
    Matrix m{
        {1, -1},
        {-1, 1},
    };
    REQUIRE(m.determinant() == 0);

    Matrix m2{
        {2, 0, 0},
        {0, 2, 0},
        {0, 0, 2},
    };
    REQUIRE(m2.determinant() == 8);

    Matrix m3{
        {8, 5, -2},
        {4, 7,  20},
        {7, 6,  1},
    };
    REQUIRE(m3.determinant() == -174);

    Matrix m4{
        {8.0,   5.0, -2.0,  4.0},
        {4.0,   2.5,  20.0, 4.0},
        {8.0,   5.0,  1.0,  4.0},
        {28.0, -4.0,  17.0, 1.0},
    };
    REQUIRE(m4.determinant() == 1032);
}

TEST_CASE("Inverse of a matrix", "[Matrix]")
{
    Matrix m{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };
    REQUIRE(m.inverse() == Matrix{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    });

    Matrix m2{
        {2.0, 0.0, 0.0},
        {0.0, 2.0, 0.0},
        {0.0, 0.0, 2.0},
    };
    REQUIRE(m2.inverse() == Matrix{
        {0.5, 0.0, 0.0},
        {0.0, 0.5, 0.0},
        {0.0, 0.0, 0.5},
    });

    Matrix m3{
        {8.0, 5.0, -2.0},
        {4.0, 7.0,  20.0},
        {7.0, 6.0,  1.0},
    };
    REQUIRE(m3.inverse().isAprrox(Matrix{
        { 0.649425287,  0.097701149, -0.655172414},
        {-0.781609195, -0.126436782,  0.965517241},
        { 0.143678161,  0.074712644, -0.206896552},
    }, 1e-9));
}

TEST_CASE("Rank of a matrix", "[Matrix]")
{
    Matrix m{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
    REQUIRE(m.rank() == 3);

    Matrix m2{
        { 1.0, 2.0, 0.0, 0.0},
        { 2.0, 4.0, 0.0, 0.0},
        {-1.0, 2.0, 1.0, 1.0},
    };
    REQUIRE(m2.rank() == 2);

    Matrix m3{
        {8.0,  5.0, -2.0},
        {4.0,  7.0,  20.0},
        {7.0,  6.0,  1.0},
        {21.0, 18.0, 7.0},
    };
    REQUIRE(m3.rank() == 3);
}
