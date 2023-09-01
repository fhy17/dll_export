#include "dir_opt.h"
#include <windows.h>

std::string getCurrentModPath() {
    char path[MAX_PATH] = {};
    GetModuleFileNameA(0, path, MAX_PATH);
    std::string tmp_path = path;

    auto pos = tmp_path.rfind("\\");
    if (pos != tmp_path.npos) {
        return std::move(tmp_path.substr(0, pos));
    }

    return std::string("");
}