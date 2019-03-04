#ifndef PYBINDBASICEXAMPLE_MY_UTILS_H
#define PYBINDBASICEXAMPLE_MY_UTILS_H

#include "my_pybind.h"

template <typename T>
void list_to_vec(std::vector<T>& vec, pybind11::list l)
{
    py::detail::list_iterator it = l.begin();

    for (auto item : l)
    {
        T val = (*item).cast<T>();
        vec.push_back(val);
    }

    return;
}

#endif //PYBINDBASICEXAMPLE_MY_UTILS_H
