#include <gtest/gtest.h>
#include <cmath>

extern "C" {
#include "factory.h"
}

static const double PI = 3.14159265358979323846;

TEST(FactoryC, CircleArea) {
    Shape *s = create_circle(1.0);
    ASSERT_NEAR(PI * 1.0 * 1.0, shape_area(s), 1e-6);
    shape_destroy(s);
}

TEST(FactoryC, SquareArea) {
    Shape *s = create_square(2.0);
    ASSERT_NEAR(4.0, shape_area(s), 1e-6);
    shape_destroy(s);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
