#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <iterator>
#include <unordered_map>

namespace gdp {
namespace config {

struct IsSpace: std::unary_function<int, bool> {
    bool operator()(int ch) const {
        return (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t');
    }
};

class GConfig {
 public:
    int Read(const std::string& config) {
        std::ifstream infile { config };

        int line_num = 0;
        std::string line, seg;
        while (std::getline(infile, line)) {
            line_num++;
            text_.push_back(line);

            line = Trim(line);
            if (line.empty()) {
                // empty
            } else if (line[0] == '#' || line[0] == ';') {
                // is comment
            } else if (line.size() >= 3
                    && line.front() == '[' && line.back() == ']') {
                seg = line.substr(1, line.size() - 2);
                seg = Trim(seg);
            } else {
                auto pos = line.find_first_of('=');
                std::string key = Trim(seg + "." + line.substr(0, pos));
                std::string value = Trim(line.substr(pos + 1));
                configs_[key] = pos == std::string::npos ? std::string():value;
            }
        }
        return 0;
    }

    std::string GetString(const char * key, const std::string & def = "") {
        auto rst = configs_.find(key);
        if (rst != configs_.end()) {
            return rst->second;
        }
        return def;
    }

    bool GetBool(const std::string& key, bool def = false) {
        auto rst = configs_.find(key);
        if (rst != configs_.end()) {
            std::vector<std::string> true_vals = {"yes", "1", "true"};
            for (auto& val : true_vals) {
                int ret = ToLower(rst->second).compare(val);
                if (ret == 0) {
                    return true;
                }
            }
        }
        return def;
    }

    int GetInt(const std::string& key, int def = 0) {
        auto rst = configs_.find(key);
        if (rst != configs_.end()) {
            return atoi(rst->second.c_str());
        }
        return def;
    }

    float GetFloat(const std::string& key, float def = 0.0) {
        auto rst = configs_.find(key);
        if (rst != configs_.end()) {
            return atof(rst->second.c_str());
        }
        return def;
    }

 private:
    // trim from start
    std::string LeftTrim(const std::string& s) {
        std::string r = s;
        r.erase(r.begin(), std::find_if(
                    r.begin(), r.end(), std::not1(IsSpace())));
        return r;
    }

    // trim from end
    std::string RightTrim(const std::string& s) {
        std::string r = s;
        r.erase(
                std::find_if(
                    r.rbegin(), r.rend(), std::not1(IsSpace()))
                .base(), r.end());
        return r;
    }

    // trim from both ends
    std::string Trim(const std::string &s) {
        return RightTrim(LeftTrim(s));
    }

    std::string ToLower(const std::string& s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(), ::tolower);
        return r;
    }

 private:
    std::vector<std::string> text_;
    typedef std::unordered_map<std::string, std::string> HashMap;
    HashMap configs_;
};

}  // namespace config
}  // namespace gdp

