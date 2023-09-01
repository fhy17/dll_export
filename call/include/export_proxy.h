#pragma once
#ifdef BASE_TEMPLATE
#include "export_proxy_base_template.hpp"
#else
#include "export_proxy_base.h"
#endif
#ifdef BASE_TEMPLATE
template <typename T>
class ExportProxy : public ExportProxyBaseTemplate<T> {
public:
    using ExportProxyBaseTemplate<T>::ExportProxyBaseTemplate;  // 继承构造函数
#else
class ExportProxy : public ExportProxyBase {
#endif
public:
    ExportProxy() {}
    ~ExportProxy() {}
    void func() { obj_->func(); }
};