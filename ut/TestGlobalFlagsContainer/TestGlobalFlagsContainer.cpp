#include "TestGlobalFlagsContainer.hpp"

TEST_F(TestGlobalFlagsContainer, shouldCreateObjectWithNoFlagsSet)
{
    EXPECT_EQ(globalFlagsContainer.commentsRemovalFlag, false);
    EXPECT_EQ(globalFlagsContainer.recursiveSearchFlag, false);
}

TEST_F(TestGlobalFlagsContainer, shouldSetCommentsRemovalFlag)
{
    flags.push_back("--removeComments");
    globalFlagsContainer.setFlags(flags);
    EXPECT_EQ(globalFlagsContainer.commentsRemovalFlag, true);
}

TEST_F(TestGlobalFlagsContainer, shouldSetRecursiveSearchFlag)
{
    flags.push_back("--recursiveSearch");
    globalFlagsContainer.setFlags(flags);
    EXPECT_EQ(globalFlagsContainer.recursiveSearchFlag, true);
}

TEST_F(TestGlobalFlagsContainer, shouldSetNothingWhenCannotRecognizeFlag)
{
    flags.push_back("--fakeFlag");
    EXPECT_EQ(globalFlagsContainer.commentsRemovalFlag, false);
    EXPECT_EQ(globalFlagsContainer.recursiveSearchFlag, false);
}