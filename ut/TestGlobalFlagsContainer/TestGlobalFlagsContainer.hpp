#pragma once

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <GlobalFlagsContainer.hpp>

class TestGlobalFlagsContainer : public ::testing::Test
{
protected:
    GlobalFlagsContainer globalFlagsContainer;
    std::vector<std::string> flags;
};