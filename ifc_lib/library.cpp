#include <cstdio>
#include <cstring>
#include <iostream>
#include "library.h"
#include "my_class.h"
#include "my_utils.h"

/*Library::Library()
{

}*/
Library::~Library()
{
    closeInterpreter();
}


extern "C"
{
    bool Library::Api(const ex_str_level_0_t *pObjIn, ex_str_level_0_t **ppObjOut)
    {
        bool retVal = false;
        // The rest depends on numpy:
        try { py::module::import("numpy"); }
        catch (...) { return retVal; }
        // A. import Py Files
        try {
            m_myPybind11Module = py::module::import("ex_module");
            m_myPyModule = py::module::import("example");
        } catch (...)
        { return retVal; }
        // call C'tr
        const auto myExampleClass = m_myPybind11Module.attr("ex_str_level_0"); //PYBIND11_EMBEDDED_MODULE(ex_module, m)
        auto myExampleInstance1 = myExampleClass(py::cast("TestObject0"), pObjIn->a, pObjIn->b, pObjIn->c);

        auto m_myPyInstance = m_myPyModule.attr("obj_user_py")(m_myPybind11Module.attr("myExampleInstance1"));

//                                               py::bind_vector<std::vector<double>>(m, "c", py::buffer_protocol());
//                py::bind_vector({std::move(pObjIn->c)}));
        //
        // retVal = BindStructToPyObj(*pObjIn);
        // B. call to Py module, and receive output Py(Bind) Object
        m_myPyInstance.attr("change_dst_val")(99, 110, 31.111);
        // copy constructor
        auto dst = m_myPyInstance.attr("dst")();
        auto myExampleInstance2 = myExampleClass(dst);
#if 0
        m_output = myExampleInstance2.cast<MyExStrLevel0>();
#else
        std::vector<double> localVec;
        list_to_vec<double>(localVec, (myExampleInstance2.attr("c")("get")).cast<py::list>());
        m_output.setAll("Output_object",py::int_(myExampleInstance2.attr("a")("get")),
                        py::int_(myExampleInstance2.attr("b")("get")), localVec) ;
#endif
        // C. assign to output pointer
        *ppObjOut = &m_output.myObj;

        std::cout << "Lib Hello, World!" << std::endl;
        return retVal;
    }
} // end of extern "C"