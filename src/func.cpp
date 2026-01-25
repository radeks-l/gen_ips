#include "func.hpp"
#include <cstdint>
#include <iostream>

template <int number, int pow>
struct Power
{
    static const long int value = number * Power<number, pow - 1>::value;
};

template <int number>
struct Power<number, 0>
{
    static const long int value = 1;
};

static constexpr int MAX_NEXT_MULT = (Power<2, 31>::value - 1) / 10;

static inline bool isOnlyDigits(const std::string_view &str)
{
    for (const auto it : str)
    {
        if (it < '0' || it > '9')
        {
            return false;
        }
    }
    return true;
}

bool str2int(const std::string_view &str, int *result)
{
    if (str.empty())
    {
        return false;
    }

    if (!isOnlyDigits(str))
    {
        return false;
    }

    int d = 0;
    int mult = 1;
    int it = 0;
    const int size = str.size();
    while (size > it)
    {
        const int current = str[(size - 1) - it] - '0';
        const int val = current * mult + d;
        // overflow
        if (val < d)
        {
            return false;
        }
        mult *= 10;
        ++it;
        d = val;
    }

    if (result)
    {
        *result = d;
    }

    return true;
}

bool isOctetOk(const std::string_view &oct)
{
    // std::cout << "isOctetOk(" << oct << ")" << std::endl;
    const auto size = oct.size();
    if (size == 0 || size > 3 || '0' == oct.at(0))
    {
        return false;
    }

    int value = 0;
    if (!str2int(oct, &value))
    {
        return false;
    }

    return value <= 255;
}

static std::string createIpStringForPos(const std::string_view &str, int pos1, int pos2, int pos3)
{
    std::string out;

    if (!isOnlyDigits(str))
    {
        return out;
    }

    // std::cout << "createIpStringForPos(" << pos1 << ", " << pos2 << ", " << pos3 << ")" << std::endl;
    std::string_view oct1 = str.substr(0, pos1);
    std::string_view oct2 = str.substr(pos1, pos2 - pos1);
    std::string_view oct3 = str.substr(pos2, pos3 - pos2);
    std::string_view oct4 = str.substr(pos3, str.size());
    if (isOctetOk(oct1) &&
        isOctetOk(oct2) &&
        isOctetOk(oct3) &&
        isOctetOk(oct4))
    {
        std::string out;

        out.reserve(str.size() + 3);
        out = oct1;
        out += '.';
        out += oct2;
        out += '.';
        out += oct3;
        out += '.';
        out += oct4;

        return out;
    }

    return out;
}

std::vector<std::string> genIPs(const std::string &input)
{
    const auto size = input.size();
    constexpr auto MAX_SIZE_4_OCT = 4 * 3;
    std::vector<std::string> result;

    if (input.empty() || size < 4 || size > MAX_SIZE_4_OCT)
    {
        return result;
    }

    int pos_1 = 1;
    int pos_2 = 2;
    int pos_3 = 3;

    for (pos_1 = 1; pos_1 < pos_2; pos_1++)
    {
        for (pos_2 = pos_1 + 1; pos_2 < pos_3; pos_2++)
        {
            for (pos_3 = pos_2 + 1; pos_3 < size; pos_3++)
            {
                auto out = createIpStringForPos(input, pos_1, pos_2, pos_3);
                if (!out.empty())
                {
                    // std::cout << "PUSH: " << out << std::endl;
                    result.push_back(std::move(out));
                }
            }
        }
    }

    return result;
}