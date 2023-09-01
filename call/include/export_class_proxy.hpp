#pragma once
#include "dir_opt.hpp"
#include "export_interface.h"
#include <windows.h>

class ExportClassProxy {
public:
    ExportClassProxy() : module_(nullptr) {}
    ~ExportClassProxy() { unload(); }

    typedef ExportInterface* (*create_obj)();
    typedef void (*destroy_obj)(ExportInterface*);
    typedef void (*func_obj)();

    bool load() {
        std::string cur_path = getCurrentModPath();
        auto mod = cur_path + "\\export.dll";
        module_ = LoadLibrary(mod.c_str());
        if (module_ == NULL) {
            auto err = GetLastError();
            return false;
        } else {
            create_obj_ = (create_obj)GetProcAddress(module_, "createExportObj");
            destroy_obj_ = (destroy_obj)GetProcAddress(module_, "destroyExportObj");
            func_obj_ = (func_obj)GetProcAddress(module_, "func");
        }
        return createObject();
    }

    void func() { obj_->func(); }

private:
    void unload() {
        destroyObject();
        if (module_) FreeLibrary(module_);
    }

    bool createObject() {
        obj_ = create_obj_();
        if (obj_)
            return true;
        else
            return false;
    }

    bool destroyObject() {
        if (obj_) {
            destroy_obj_(obj_);
            obj_ = nullptr;
        }
        return true;
    }

private:
    HMODULE module_;

    ExportInterface* obj_;
    create_obj create_obj_;
    destroy_obj destroy_obj_;
    func_obj func_obj_;
};