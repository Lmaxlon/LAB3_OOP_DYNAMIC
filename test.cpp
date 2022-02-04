#include "../hypocycloid.h"
#include "gtest/gtest.h"
TEST(constuct, get)
{
    Elem elem(4, 1, NULL);
    ASSERT_EQ(1, elem.get_occupied());
    ASSERT_EQ(4, elem.get_key());
}
TEST(construct, set)
{
    Elem elem(1, 1, NULL);
    elem.set_occupied(1);
    elem.set_key(4);
    ASSERT_EQ(1, elem.get_occupied());
    ASSERT_EQ(4, elem.get_key());
}

TEST(construct, get_table){
       Elem elem(1, 1, NULL);
       CHashedTable w(elem, n);
       ASSERT_EQ(1, w.elem.get_occupied()());
       ASSERT_EQ(1, w.elem.get_key());
}
TEST(construct, set_table)
{
    Elem elem(1, 1, NULL);
    CHashedTable w(elem, n);
    w.set_step(10);
    w.set_size(5);
    w.set_count(7);
    w.set_localadding(0);
    ASSERT_EQ(10, a.get_step());
    ASSERT_EQ(5, a.get_size());
    ASSERT_EQ(7, a.get_count());
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}