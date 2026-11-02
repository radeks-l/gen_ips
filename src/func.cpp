#include "func.hpp"
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
    const auto size = oct.size();
    if (size == 0 || size > 3 || '0' == oct[0])
    {
        return false;
    }

    if (size == 3)
    {
        const auto f = oct[0];
        switch (f)
        {
            case '1':
                return true;
            case '2':
            {
                const auto s = oct[1];
                if (s > '5')
                {
                    return false;
                }
                if (s == '5' && oct[2] > '5')
                {
                    return false;
                }
                return true;
            }
            default:
                return false;
        }
    }
    return true;
}

static std::string createIpStringForPos(const std::string_view &str, int pos1, int pos2, int pos3)
{
    std::string out;

    std::string_view oct1 = str.substr(0, pos1);
    std::string_view oct2 = str.substr(pos1, pos2 - pos1);
    std::string_view oct3 = str.substr(pos2, pos3 - pos2);
    std::string_view oct4 = str.substr(pos3, str.size());
    if (isOctetOk(oct1) &&
        isOctetOk(oct2) &&
        isOctetOk(oct3) &&
        isOctetOk(oct4))
    {
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

    if (input.empty() || size < 4 || size > MAX_SIZE_4_OCT || !isOnlyDigits(input))
    {
        return {};
    }

    // let optimize starting point
    const int pos_1_max = size - 9;
    const int pos_2_max = size - 6;
    const int pos_3_max = size - 3;
    const auto pos_1 = std::max(1, pos_1_max);

    std::vector<std::string> result;

    for (int i = pos_1; i < 4; i++)
    {
        const auto pos_2 = std::max(i + 1, pos_2_max);
        for (int j = pos_2; (j - i) < 4; j++)
        {
            const auto pos_3 = std::max(j + 1, pos_3_max);
            for (int k = pos_3; (k - j < 4) && (k < size); k++)
            {
                auto out = createIpStringForPos(input, i, j, k);
                if (!out.empty())
                {
                    result.push_back(std::move(out));
                }
            }
        }
    }

    return result;
}