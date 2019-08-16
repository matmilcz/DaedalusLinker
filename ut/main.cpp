#include <gtest/gtest.h>
#include "TestGlobalFlagsContainer/TestGlobalFlagsContainer.hpp"

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}