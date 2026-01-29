#include "func.hpp"
#include <array>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("str2int()")
{
    CHECK_FALSE(str2int("", nullptr));
    CHECK_FALSE(str2int("120d", nullptr));
    CHECK_FALSE(str2int("-120", nullptr));
    CHECK(str2int("12", nullptr));

    int result = 0;
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

TEST_CASE("254255256255 -> one octet bad")
{
    const auto out = genIPs("2552552562555");
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

TEST_CASE("255255255255 -> 255.255.255.255")
{
    const auto out = genIPs("255255255255");
    CHECK(out.size() == 1);
    CHECK_EQ(out.at(0), "255.255.255.255");
}

TEST_CASE("112233")
{
    const auto out = genIPs("112233");
    const std::vector<std::string_view> expected{
        "1.1.2.233", "1.1.22.33", "1.1.223.3",
        "1.12.2.33", "1.12.23.3",
        "1.122.3.3",
        "11.2.2.33", "11.2.23.3", "11.22.3.3",
        "112.2.3.3"};

    CHECK(out.size() == expected.size());
    int it = 0;
    for (const auto it_exp : expected)
    {
        CHECK_EQ(out.at(it++), it_exp);
    }
}

/*
112233445 ->    1.12.233.445
                1.122.33.445
                1.122.334.45
                11.2.233.445
                11.22.334.45
                11.22.334.45
            1.122.3

*/
// TEST_CASE("11011 -> 1.10.1.1")
// {
//     const auto out = genIPs("11011");
//     CHECK(out.size() == 1);
// }