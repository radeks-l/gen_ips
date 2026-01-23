#pragma once

#include <vector>
#include <string>

bool str2int(const std::string_view &str, int *result);

bool isOctetOk(const std::string_view &oct);

std::vector<std::string> genIPs(const std::string &input);