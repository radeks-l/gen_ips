#include "func.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("str2int()")
{
    int result = 0;
    CHECK_FALSE(str2int("", nullptr));
    CHECK_FALSE(str2int("120d", nullptr));
    CHECK_FALSE(str2int("-120", nullptr));
    CHECK(str2int("12", nullptr));

    CHECK(str2int("1", &result));
    CHECK_EQ(1, result);

    CHECK(str2int("01", &result));
    CHECK_EQ(1, result);

    CHECK(str2int("32", &result));
    CHECK_EQ(32, result);

    CHECK(str2int("123", &result));
    CHECK_EQ(123, result);

    CHECK(str2int("2147483647", &result));
    CHECK_EQ(2147483647, result);

    CHECK_FALSE(str2int("2147483648", nullptr));
}

TEST_CASE("isOctetOk() returns OK")
{
    CHECK(isOctetOk("1"));
    CHECK(isOctetOk("111"));
    CHECK(isOctetOk("255"));
}

TEST_CASE("isOctetOk() return NOK")
{
    CHECK_FALSE(isOctetOk(""));
    CHECK_FALSE(isOctetOk("01"));
    CHECK_FALSE(isOctetOk("1111"));
    CHECK_FALSE(isOctetOk("256"));
    CHECK_FALSE(isOctetOk("311"));
}

TEST_CASE("Empty input -> empty output")
{
    const auto out = genIPs("");
    CHECK(out.empty());
}

TEST_CASE("111 -> to small, empty")
{
    const auto out = genIPs("111");
    CHECK(out.empty());
}

TEST_CASE("2552552552551 -> to big, empty")
{
    const auto out = genIPs("2552552552551");
    CHECK(out.empty());
}

TEST_CASE("1234 -> 1.2.3.4")
{
    const auto out = genIPs("1234");
    CHECK(out.size() == 1);
    CHECK_EQ(out.at(0), "1.2.3.4");
}

TEST_CASE("11110 -> 1.1.1.10")
{
    const auto out = genIPs("11110");
    CHECK(out.size() == 1);
    CHECK_EQ(out.at(0), "1.1.1.10");
}

TEST_CASE("111100 -> 1.1.1.100")
{
    const auto out = genIPs("111100");
    CHECK(out.size() == 1);
    CHECK_EQ(out.at(0), "1.1.1.100");
}

// TEST_CASE("22222 -> 2.2.2.22, 2.2.22.2")
// {
//     const auto out = genIPs("22222");
//     CHECK(out.size() == 2);
//     CHECK_EQ(out.at(0), "2.2.2.22");
//     CHECK_EQ(out.at(1), "2.2.22.2");
// }


/*
1111 -> 1.1.1.1
11223344 -> 1.1.2.23344
            1.1.22.3344
            1.1.223.344
            1.1.2233.44
            1.1.22334.4
            1.12.2.3344
            1.12.23.344
            1.12.233.44
            1.122.3

*/
// TEST_CASE("11011 -> 1.10.1.1")
// {
//     const auto out = genIPs("11011");
//     CHECK(out.size() == 1);
// }