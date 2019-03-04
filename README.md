# pybind_embedded_struct_roundtrip_example
An example project for Linux application using shared library to pass input structure at C++, pass to Python using Pybind11 and get another one from python through Pybind11 and back up to application


Currently not working, m_myPybind11Module = py::module::import("ex_module"); gets: throw error_already_set();