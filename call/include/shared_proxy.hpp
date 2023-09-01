#pragma once
#include <windows.h>
#include <string>

class SharedProxy {
public:
    SharedProxy() : module_(nullptr) {}
    ~SharedProxy() { unload(); }

    typedef int (*add_func)(int x, int y);
    typedef int (*sub_func)(int x, int y);

    bool load(const std::string& file) {
        module_ = LoadLibrary(file.c_str());
        if (module_ == NULL) {
            auto err = GetLastError();
            return false;
        } else {
            add_fo_ = (add_func)GetProcAddress(module_, "add");
            sub_fo_ = (sub_func)GetProcAddress(module_, "sub");
        }
        return true;
    }
    void unload() {
        if (module_) FreeLibrary(module_);
    }

    int add(int x, int y) { return add_fo_(x, y); }
    int sub(int x, int y) { return sub_fo_(x, y); }

private:
    HMODULE module_;

    add_func add_fo_;
    sub_func sub_fo_;
};