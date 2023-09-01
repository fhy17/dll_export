#include "export_interface.h"
#include "export_impl.h"

DLL_API ExportInterface* _stdcall createExportObj() {
    ExportInterface* instance = new ExportImpl();
    return instance;
}

DLL_API void _stdcall destroyExportObj(ExportInterface* export_interface) {
    // export_interface->release();  // ExportInterface的析构函数不为虚函数时，不能直接delete export_interface
    delete export_interface;
}
