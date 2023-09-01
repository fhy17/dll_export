#pragma once

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class ExportInterface {
public:
    virtual ~ExportInterface() {}
    virtual void func() = 0;
    // virtual void release() = 0;
    virtual int add(int, int) = 0;
};

extern "C" DLL_API ExportInterface* _stdcall createExportObj();
extern "C" DLL_API void _stdcall destroyExportObj(ExportInterface* export_interface);
