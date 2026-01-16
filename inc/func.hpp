#pragma once

#include <vector>
#include <string>

bool str2int(const std::string &str, int *result);

bool isOctetOk(const std::string &oct);

std::vector<std::string> genIPs(const std::string &input);