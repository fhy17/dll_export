#pragma once
#include <windows.h>
#include <string>

template <typename T>
class ExportProxyBaseTemplate {
public:
    ExportProxyBaseTemplate() : module_(nullptr) {}
    ~ExportProxyBaseTemplate() { unload(); }

    typedef T* (*create_obj)();
    typedef void (*destroy_obj)(T*);

    bool load(const std::string& file) {
        module_ = LoadLibrary(file.c_str());
        if (module_ == NULL) {
            auto err = GetLastError();
            return false;
        } else {
            create_obj_ = (create_obj)GetProcAddress(module_, "createExportObj");
            destroy_obj_ = (destroy_obj)GetProcAddress(module_, "destroyExportObj");
        }
        return createObject();
    }

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

protected:
    HMODULE module_;

    T* obj_;
    create_obj create_obj_;
    destroy_obj destroy_obj_;
};