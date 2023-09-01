#pragma once

#include <string>
// namespace Common {

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLL_API int __stdcall add(int a, int b);
DLL_API int __stdcall sub(int a, int b);

// EXPORT_DLL void __stdcall readInfo(const std::string& file, char* version, const size_t version_size);

#ifdef __cplusplus
}
#endif

// }  // namespace Common