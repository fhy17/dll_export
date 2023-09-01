#pragma once
#include "export_interface.h"
#include <windows.h>
#include <string>

class ExportProxyBase {
public:
    ExportProxyBase();
    ~ExportProxyBase();

    typedef ExportInterface* (*create_obj)();
    typedef void (*destroy_obj)(ExportInterface*);

    bool load(const std::string& file);

protected:
    void unload();

    bool createObject();

    bool destroyObject();

protected:
    HMODULE module_;

    ExportInterface* obj_;
    create_obj create_obj_;
    destroy_obj destroy_obj_;
    // func_obj func_obj_;
};