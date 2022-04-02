#include "tested_file.h"
#include <gtest/gtest.h>
 
TEST(SumRootTest, PositiveSum) { 
    ASSERT_EQ(3, sum(1, 2));
    ASSERT_EQ(4, sum(2, 2));
    ASSERT_EQ(1, sum(0, 1));
}
 
TEST(SumRootTest, NegativeSum) {
    ASSERT_EQ(-15, sum(-15,0));
    ASSERT_EQ(-2, sum(2, -4));
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}