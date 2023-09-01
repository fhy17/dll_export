#include "export_impl.h"
#include <iostream>

ExportImpl::ExportImpl() {}

ExportImpl::~ExportImpl() {
    // std::cout << "release ok" << std::endl;
}

void ExportImpl::func() {
    // do something...
    std::cout << __FUNCTION__ << std::endl;
    return;
}

// void ExportImpl::release() { delete this; }

int ExportImpl::add(int x, int y) { return x + y; }