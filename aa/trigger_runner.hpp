// trigger_runner.hpp
#pragma once

#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>

inline int runTrigger(const std::string& input,
                      const std::map<std::string, std::function<int()>>& triggers) {
    if (input.empty() || input[0] != '@') {
        std::cerr << "Error: trigger must start with '@'\n";
        return -1;
    }

    // strip '@' and replace '.' with '_'
    std::string key = input.substr(1);
    std::replace(key.begin(), key.end(), '.', '_');

    auto it = triggers.find(key);
    if (it == triggers.end()) {
        std::cerr << "Error: unknown trigger '" << key << "'\n";
        return -1;
    }

    return it->second();
}
