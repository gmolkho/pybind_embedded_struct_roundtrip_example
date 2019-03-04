#include "my_pybind.h"
#include "my_class.h"

PYBIND11_EMBEDDED_MODULE(ex_module, m) {
    m.doc() = "pybind11 embedded example"; // optional module docstring

    //py::class_<BaseClass>(m, "BaseClass").def(py::init<>());
    py::class_<MyExStrLevel0, ex_str_level_0_t> ex_str_level_0(m, "MyExStrLevel0"/*, py::dynamic_attr()*/);
    ex_str_level_0
            .def (py::init<const std::string &, int, int, std::vector<double> >())
            .def_readwrite ("name", &MyExStrLevel0::name)
            .def_readwrite ("a", &MyExStrLevel0::a)
            .def_readwrite ("b", &MyExStrLevel0::b)
            .def_readwrite ("c", &MyExStrLevel0::c)
            .def_property("c", &MyExStrLevel0::getVec, &MyExStrLevel0::setVec);
}
