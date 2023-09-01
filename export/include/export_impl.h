#pragma once
#include "export_interface.h"
#include <string>

class ExportImpl : public ExportInterface {
public:
    ExportImpl();
    ~ExportImpl();
    void func() override;
    // void release() override;
    int add(int x, int y) override;

private:
    // std::string str_;
};