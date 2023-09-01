#include "export_proxy_base.h "
#include <windows.h>

ExportProxyBase::ExportProxyBase() : module_(nullptr) {}

ExportProxyBase::~ExportProxyBase() { unload(); }

bool ExportProxyBase::load(const std::string& file) {
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

void ExportProxyBase::unload() {
    destroyObject();
    if (module_) FreeLibrary(module_);
}

bool ExportProxyBase::createObject() {
    obj_ = create_obj_();
    if (obj_)
        return true;
    else
        return false;
}

bool ExportProxyBase::destroyObject() {
    if (obj_) {
        destroy_obj_(obj_);
        obj_ = nullptr;
    }
    return true;
}