#include "../hypocycloid.h"
#include "gtest/gtest.h"
TEST(constuct, get)
{
    CHashedTable p(4, 1, NULL);
    ASSERT_EQ(1, a.get_occupied());
    ASSERT_EQ(4, a.get_key());
}
TEST(construct, set)
{
    CHashedTable p(4, 1, NULL);
    a.get_occupied(1);
    a.get_key(4);
    ASSERT_EQ(1, a.get_occupied());
    ASSERT_EQ(4, a.get_key());
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
