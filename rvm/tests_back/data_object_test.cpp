#include "DO/fake_data_object.h"
#include <gtest/gtest.h>

/* @1 - Test set function 
        @1.1 - Test id
*/







/* @1 Test Set function  */
/*      @1.1 Test id */
TEST(DataObjectTest, set_id0_Seted0) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 0;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id1_Seted1) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 1;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id2_Seted2) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 2;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id3_Seted3) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 3;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id4_Seted4) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 4;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id5_Seted5) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 5;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id6_Seted6) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 6;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id7_Seted7) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 7;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id8_Seted8) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 8;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id9_Seted9) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 9;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id10_Seted10) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 10;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id11_Seted11) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 11;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id12_Seted12) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 12;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id13_Seted13) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 13;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id14_Seted14) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 14;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id15_Seted15) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 15;

    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id16_Seted16) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 16;
    
    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id17_Seted17) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 17;
    
    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id18_Seted18) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 18;
    
    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id19_Seted19) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 19;
    
    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}

TEST(DataObjectTest, set_id20_Seted20) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 20;
    
    fakeDO.set(id, 1, 0);

    ASSERT_EQ(id, fakeDO.id);
}


/* ... */

TEST(DataObjectTest, set_id255_Seted255) {
    rvm::FakeDataObject fakeDO;
    uint8_t id = 256;
    
    fakeDO.set(id, 1, 0);
    id = 0;

    ASSERT_EQ(id, fakeDO.id);
}
/*      @1.1 and Test id */
