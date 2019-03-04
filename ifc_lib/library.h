#ifndef LIBRARY_H
#define LIBRARY_H

#define  EXTRA_CODE 0
#if  EXTRA_CODE
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define IS_WINDOWS
#include <Windows.h> // Needed by GetModuleFileNameW
#else
#include <libgen.h> // Needed by readlink
#endif
#include <Python.h>
#ifndef IS_WINDOWS
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#endif
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <pybind11/embed.h>
#ifndef IS_WINDOWS
#pragma GCC diagnostic pop
#endif
#include "my_class.h"


namespace py = pybind11;
using namespace py::literals;

#if  EXTRA_CODE
///=============================================================================
#ifdef IS_WINDOWS
std::wstring getExecutableDir() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    const auto executableDir = std::wstring(exePath);
    const auto pos = executableDir.find_last_of('\\');
    if (pos != std::string::npos) return executableDir.substr(0, pos);
    return L"\\";
}
#else
std::wstring getExecutableDir() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        const auto path = std::string(dirname(result));
        return std::wstring(path.begin(), path.end());
    }
    return L"/";
}
#endif
#endif


class Library
{
public:
    void closeInterpreter()
    {
        py::finalize_interpreter();
    }
    static Library& getInstance()
    { // singleton design pattern
        static Library s_instance;
        // Initialize python
#if  EXTRA_CODE
        // Get executable dir and build python PATH variable
        const auto exeDir = getExecutableDir();
#ifdef IS_WINDOWS
        const auto pythonHome = exeDir + L"\\lib";
    const auto pythonPath = exeDir + L"\\lib;" + exeDir + L"\\app;";
#else
        const auto pythonHome = exeDir + L"/lib";
        const auto pythonPath = exeDir + L"/lib:" + exeDir + L"/app";
#endif
        Py_OptimizeFlag = 1;
        Py_SetProgramName(L"PythonEmbeddedExample");
        Py_SetPath(pythonPath.c_str());
        Py_SetPythonHome(pythonHome.c_str());

        std::wcout << "Python PATH set to: " << pythonPath << std::endl;
#endif
        try {
            // Operate Python interpreter
            py::initialize_interpreter();

#if  EXTRA_CODE
            // Disable build of __pycache__ folders
            py::exec(R"(
                import sys
                sys.dont_write_bytecode = True
            )");
#endif
        } catch (std::exception& e) {
            std::cerr << "Something went wrong: " << e.what() << std::endl;
            s_instance.closeInterpreter();
            exit(-1);
        }

        return s_instance;
    }
    Library()= default; //clang for trivial c'tor
    virtual ~Library();
    Library(const Library& other) = delete;
    Library& operator=(const Library& other) = delete;
    bool Api(const ex_str_level_0_t *pObjIn, ex_str_level_0_t **ppObjOut);
//private:
    ////////////////////////////////////////////////////////////////////////////
    // private constructors and destructors.
    ////////////////////////////////////////////////////////////////////////////
    py::module m_myPybind11Module;
    py::module m_myPyModule;
    //MyExStrLevel0 m_input;
    MyExStrLevel0 m_output;
};

#endif //LIBRARY_H
