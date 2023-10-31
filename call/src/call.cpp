#include <iostream>
#include "dir_opt.h"
#include "dll_proxy.h"
#include "shared_proxy.hpp"
// #include "export_class_proxy.hpp"
#include "export_proxy.h"
#include "export_interface.h"

int main() {
    auto curr_path = getCurrentModPath();
    auto file = curr_path + "\\export.dll";
    {
        // Use DllProxy to call dll directly
        // std::string file = "export.dll";
        DllProxyPtr dll_proxy = std::make_shared<DllProxy>(file);
        {
            using type = int(int, int);
            int x = 8;
            int y = 1;
            std::cout << x << " + " << y << " = " << dll_proxy->call<type>("add", x, y) << std::endl;
        }

        // {
        //     using read_info_type = void(const std::string&, char*, const size_t);
        //     char version[256];
        //     dll_proxy->call<read_info_type>("readInfo", file, version, sizeof(version));
        //     std::cout << file << ": " << version << std::endl;
        // }
    }
    {
        // Use SharedProxy to call dll
        std::shared_ptr<SharedProxy> dll_proxy = std::make_shared<SharedProxy>();
        if (!dll_proxy->load(file))
            std::cout << "load dll err" << std::endl;
        else {
            int x = 8;
            int y = 1;
            std::cout << x << " - " << y << " = " << dll_proxy->sub(x, y) << std::endl;
            std::cout << x << " + " << y << " = " << dll_proxy->add(x, y) << std::endl;
        }
    }
    {
        // Use DllProxy to call dll directly
        // std::string file = "export.dll";
        DllProxyPtr dll_proxy = std::make_shared<DllProxy>(file);
        {
            using create_obj_type = ExportInterface*();
            using destroy_obj_type = void(ExportInterface*);
            auto obj = dll_proxy->call<create_obj_type>("createExportObj");
            obj->func();
            dll_proxy->call<destroy_obj_type>("destroyExportObj", obj);
        }
    }
    // {
    //     std::shared_ptr<ExportClassProxy> dll_proxy = std::make_shared<ExportClassProxy>();
    //     if (!dll_proxy->load()) {
    //         std::cout << "load dll err" << std::endl;
    //     } else {
    //         dll_proxy->func();
    //     }
    // }

#ifdef BASE_TEMPLATE
    {
        std::shared_ptr<ExportProxy<ExportInterface>> dll_proxy = std::make_shared<ExportProxy<ExportInterface>>();
        if (!dll_proxy->load(file)) {
            std::cout << "load dll err" << std::endl;
        } else {
            dll_proxy->func();
        }
    }
#else
    {
        std::shared_ptr<ExportProxy> dll_proxy = std::make_shared<ExportProxy>();
        if (!dll_proxy->load(file)) {
            std::cout << "load dll err" << std::endl;
        } else {
            dll_proxy->func();
        }
    }
#endif

    return 0;
}