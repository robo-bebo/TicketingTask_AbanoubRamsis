#include <gtest/gtest.h>

// Main function for running tests
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv); // global ::testing from GTest
    return RUN_ALL_TESTS();
}