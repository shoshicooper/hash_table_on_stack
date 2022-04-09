#include <gtest/gtest.h>
#include "../SmallHashT.h"
#include "../SmallHashT.cpp"
#include "Tests.h"
#include <iostream>
#include <vector>

// (c) 2022 Shoshi (Sharon) Cooper.  No duplication is permitted for commercial use.  Any significant changes made must be
// stated explicitly and the original source code, if used, must be available and credited to Shoshi (Sharon) Cooper.


class TestSmallHash: public ::testing::Test {
    protected:
        using TableTypeInt = SmallHash<int, int>;
        using TableTypeIS = SmallHash<int, std::string>;
        using TableTypeSI = SmallHash<std::string, int>;

        TestSmallHash() {
            
        };
        void SetUp( ) {
        }
        void TearDown( ) { 
            // code here will be called just after the test completes
            // ok to throw exceptions from here if need be
        }

        ~TestSmallHash( )  { 
            // cleanup any pending stuff, but no exceptions allowed
        }
    public:
        template<typename T>
        static void assertInArr(T* array, T val, size_t arr_size){
            for (size_t i = 0; i < arr_size; i++){
                if (array[i] == val)
                    return;
            }
            throw AssertionError("Value not found in array");
        }
};


////////////////////////Hash Table Tests /////////////////////////////////


TEST_F(TestSmallHash, TestConstructor){
    int keys[17];
    int values[17];
    int status[17];
    TableTypeInt d(keys, values, status, 17);
    ASSERT_EQ(0, d.size());
}

TEST_F(TestSmallHash, TestConstructorInvalid){
    int keys[16];
    int values[16];
    int status[16];
    ASSERT_THROW(TableTypeInt d(keys, values, status, 16), KeyError);
}


TEST_F(TestSmallHash, TestSetItem){
    int keys[11];
    int values[11];
    int status[11];
    TableTypeInt test_HashT(keys, values, status, 11);

    test_HashT.set(5, 7);
    test_HashT.set(12, 24);
    assertInArr<int>(keys, 5, 11);
    assertInArr<int>(keys, 12, 11);
}

TEST_F(TestSmallHash, TestSetItemDiffType){
    int keys[11];
    std::string values[11];
    int status[11];
    // Try with a different type
    SmallHash<int, std::string> test_HashT2(keys, values, status, 11);
    test_HashT2.set(8, "eight");
    assertInArr<int>(keys, 8, 11);
    test_HashT2.set(12, "twelve");
    assertInArr<int>(keys, 12, 11);
}


TEST_F(TestSmallHash, TestSetItem_when_overwriting){
    int keys[11];
    std::string values[11];
    int status[11];
    TableTypeIS myHashT(keys, values, status, 11);
    myHashT.set(5, "five");
    assertInArr(keys, 5, 11);
    myHashT.set(12, "eleven");
    myHashT.set(12, "Twelve");
    myHashT.set(12, "Thirteen");
    myHashT.set(12, "twelve");
    assertInArr<int>(keys, 12, 11);
    assertInArr<std::string>(values, "twelve", 11);
    
}

TEST_F(TestSmallHash, Test_get_item){
    int keys[11];
    std::string values[11];
    int status[11];
    TableTypeIS myHashT(keys, values, status, 11);
    myHashT.set(0, "zero");
    myHashT.set(1, "one");
    myHashT.set(2, "two");
    myHashT.get(0);
    ASSERT_EQ("zero", myHashT.get(0));
    ASSERT_EQ("one", myHashT.get(1));
    ASSERT_EQ("two", myHashT.get(2));
    
    std::string k2[11];
    int v2[11];
    int s2[11];
    SmallHash<std::string, int> otherHashT(k2, v2, s2, 11);
    std::string z = "zero", o = "one", t = "two";
    otherHashT.set(z, 0);
    otherHashT.set(o, 1);
    otherHashT.set(t, 2);
    ASSERT_EQ(0, otherHashT.get("zero"));
    ASSERT_EQ(1, otherHashT.get("one"));
    ASSERT_EQ(2, otherHashT.get("two"));
}

TEST_F(TestSmallHash, Test_get_item_brackets){
    int keys[11];
    std::string values[11];
    int status[11];
    TableTypeIS myHashT(keys, values, status, 11);
    myHashT.set(0, "zero");
    myHashT.set(1, "one");
    myHashT.set(2, "two");
    Tests::assertEqual("zero", myHashT[0]);
    Tests::assertEqual("one", myHashT[1]);
    Tests::assertEqual("two", myHashT[2]);
    
    std::string k2[11];
    int v2[11];
    int s2[11];
    SmallHash<std::string, int> otherHashT(k2, v2, s2, 11);
    otherHashT.set("zero", 0);
    otherHashT.set("one", 1);
    otherHashT.set("two", 2);
    Tests::assertEqual(0, otherHashT["zero"]);
    Tests::assertEqual(1, otherHashT["one"]);
    Tests::assertEqual(2, otherHashT["two"]);
}

TEST_F(TestSmallHash, test_getitem_when_not_in_HashT){
    int values[11];
    std::string keys[11];
    int status[11];
    TableTypeSI test_HashT(keys, values, status, 11);
    test_HashT.set("zero", 0);
    test_HashT.set("one", 1);
    test_HashT.set("two", 2);
    try
    {
        int value = test_HashT["three"];
        std::cout << value;
        throw AssertionError("Three should have raised a KeyError");
    }
    catch(const std::exception& e)
    {
        ASSERT_TRUE(true);
    }
    try
    {
        int value = test_HashT["four"];
        std::cout << value;
        throw AssertionError("four should have raised a KeyError");
    }
    catch(const std::exception& e)
    {
        ASSERT_TRUE(true);
    }
    
    ASSERT_THROW(test_HashT.get("three"), KeyError);
    ASSERT_THROW(test_HashT.get("four"), KeyError);
}

TEST_F(TestSmallHash, test_brackets_again){
    int values[11];
    std::string keys[11];
    int status[11];
    TableTypeSI test_HashT(keys, values, status, 11);
    test_HashT["zero"] = 0;
    int val = test_HashT["zero"];
    Tests::assertEqual(0, val);
    test_HashT["one"] = 1;
    val = test_HashT["one"];
    Tests::assertEqual(1, val);
    test_HashT["two"] = 2;
    val = test_HashT["two"];
    Tests::assertEqual(2, val);
    
}

TEST_F(TestSmallHash, test_bigger){
    int values[17];
    std::string keys[17];
    int status[17];
    TableTypeSI test_HashT(keys, values, status, 17);
    test_HashT.set("zero", 0);
    test_HashT.set("one", 1);
    test_HashT.set("two", 2);
    test_HashT.set("three", 3);
    test_HashT.set("four", 4);
    test_HashT.set("five", 5);
    test_HashT.set("six", 6);
    test_HashT.set("seven", 7);
    test_HashT.set("eight", 8);
    Tests::assertEqual(0, test_HashT["zero"]);
    Tests::assertEqual(1, test_HashT["one"]);
    Tests::assertEqual(2, test_HashT["two"]);
    Tests::assertEqual(3, test_HashT["three"]);
    Tests::assertEqual(4, test_HashT["four"]);
    Tests::assertEqual(5, test_HashT["five"]);
    Tests::assertEqual(6, test_HashT["six"]);
    Tests::assertEqual(7, test_HashT["seven"]);
    Tests::assertEqual(8, test_HashT["eight"]);
}

TEST_F(TestSmallHash, test_making_HashTables){
    int values[37];
    int keys[37];
    int status[37];
    TableTypeInt test_HashT(keys, values, status, 37);
    int key, value;
    std::vector<std::tuple<int, int>> expected = {{39, 12}, {17, 11}, {-1, 10}, {38, 55}, {32, 80},
                         {28, 200}, {5, 10}, {6, 55}, {2, 20}, {16, 10}};
    for (size_t i = 0; i < expected.size(); i ++){
        key = std::get<0>(expected[i]);
        value = std::get<1>(expected[i]);
        test_HashT[key] = value;
        int actual = test_HashT[key];
        ASSERT_EQ(value, actual);
        ASSERT_EQ(value, test_HashT.get(key));
    }
}


TEST_F(TestSmallHash, test_del_item){
    int values[37];
    int keys[37];
    int status[37];
    TableTypeInt test_HashT(keys, values, status, 37);
    int key, value;
    std::vector<std::tuple<int, int>> expected = {{39, 12}, {17, 11}, {-1, 10}, {38, 55}, {32, 80},
                         {28, 200},  {60, 55}, {2, 20}, {16, 10}};

    for (size_t i = 0; i < expected.size(); i ++){
        key = std::get<0>(expected[i]);
        value = std::get<1>(expected[i]);
        test_HashT[key] = value;
    }
    test_HashT[5] = 10;
    
    test_HashT.discard(5);

    for (size_t i = 0; i < expected.size(); i ++){
        key = std::get<0>(expected[i]);
        value = std::get<1>(expected[i]);
        int actual = test_HashT.get(key);
        ASSERT_EQ(value, actual);
    }
    size_t exp_size = expected.size(), act_size = test_HashT.size();
    ASSERT_EQ(exp_size, act_size);
}

TEST_F(TestSmallHash, test_del_all){
    // To fix a small bug that resulted from a typo
    int keys[2111];
    std::string values[2111];
    int status[2111];
    TableTypeIS d(keys, values, status, 2111);
    for (size_t i = 0; i < 1000; i ++){
        d.set(i, std::to_string(i));
    }
    
    for (size_t i = 0; i < 500; i ++){
        d.discard(i);
    }

    for (size_t i = 500; i < 1000; i ++){
        d.discard(i);
    }
}

TEST_F(TestSmallHash, test_del_over_five_hundred_string_version){
    // To fix a small bug that resulted from a typo
    int values[2111];
    std::string keys[2111];
    int status[2111];
    TableTypeSI d(keys, values, status, 2111);
    for (size_t i = 0; i < 1000; i ++){
        d.set(std::to_string(i), i);
    }
    
    for (size_t i = 0; i < 500; i ++){
        d.discard(std::to_string(i));
    }

    for (size_t i = 500; i < 1000; i ++){
        d.discard(std::to_string(i));
    }
}

TEST_F(TestSmallHash, test_clear){
    int values[2111];
    std::string keys[2111];
    int status[2111];
    TableTypeSI d(keys, values, status, 2111);
    for (size_t i = 0; i < 1000; i ++){
        d.set(std::to_string(i), i);
    }
    d.clear();
    ASSERT_EQ(0, d.size());
    for (size_t i = 0; i < 1000; i ++){
        ASSERT_FALSE(d.contains(std::to_string(i)));
    }
}

TEST_F(TestSmallHash, test_contains){
    int values[17];
    int keys[17];
    int status[17];
    TableTypeInt d(keys, values, status, 17);
    ASSERT_FALSE(d.contains('a'));
    ASSERT_FALSE(d.contains('b'));
    ASSERT_FALSE(d.contains('c'));
    d.set('a', 1);
    d.set('b', 2);
    ASSERT_TRUE(d.contains('a'));
    ASSERT_TRUE(d.contains('b'));
    ASSERT_FALSE(d.contains('c'));
    
}

TEST_F(TestSmallHash, test_size){
    int values[17];
    int keys[17];
    int status[17];
    TableTypeInt d(keys, values, status, 17);
    ASSERT_EQ(0, d.size());
    d.set('a', 1);
    d.set('b', 2);
    ASSERT_EQ(2, d.size());
}


TEST_F(TestSmallHash, test_getitem){
    int values[17];
    int keys[17];
    int status[17];
    TableTypeInt d(keys, values, status, 17);
    d.set('a', 1);
    d.set('b', 2);
    Tests::assertEqual(1, d['a']);
    Tests::assertEqual(d['b'], 2);
    d.set('c', 3);
    d.set('a', 4);
    Tests::assertEqual(d['c'], 3);
    Tests::assertEqual(d['a'], 4);
    d.discard('b');
    Tests::assertEqual(d['c'], 3);
    Tests::assertEqual(d['a'], 4);
    ASSERT_FALSE(d.contains('b'));
    ASSERT_THROW(d.get('b'), KeyError);
    try
    {
        int actual = d['b'];
        std::cout << actual;
        throw AssertionError("KeyError was not raised");
    }
    catch(const KeyError& e)
    {
        ASSERT_TRUE(true);
    }
}
