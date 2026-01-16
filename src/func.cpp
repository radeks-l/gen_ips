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

bool str2int(const std::string &str, int *result)
{
    if (str.empty())
    {
        return false;
    }

    for (const auto it : str)
    {
        if (it < '0' || it > '9')
        {
            return false;
        }
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

bool isOctetOk(const std::string &oct)
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

static std::string createIpStringForPos(const std::string &str, int pos1, int pos2, int pos3)
{
    std::string out;

    std::string tmp = str.substr(0, pos1);
    if (isOctetOk(tmp))
    {
        out = tmp + '.';
    }

    tmp = str.substr(pos1, pos2 - pos1);
    if (isOctetOk(tmp))
    {
        out += (tmp + '.');
    }

    tmp = str.substr(pos2, pos3 - pos2);
    if (isOctetOk(tmp))
    {
        out += (tmp + '.');
    }

    tmp = str.substr(pos3, str.size());
    if (isOctetOk(tmp))
    {
        out += tmp;
    }
    return out;
}

std::vector<std::string> genIPs(const std::string &input)
{
    const auto size = input.size();
    if (input.empty() || size < 4 || size > (4 * 3))
    {
        return {};
    }

    int pos_1 = 1;
    int pos_2 = 2;
    int pos_3 = 3;
    // for (int it = 0; it < str.size();)
    // {
    //     out.push_back(str.at(it));
    //     ++it;
    //     if (it == pos1 || it == pos2 || it == pos3)
    //     {
    //         out.push_back('.');
    //     }
    // }

    std::vector<std::string> result;
    std::string out = createIpStringForPos(input, pos_1, pos_2, pos_3);
    result.push_back(out);
    return result;
}