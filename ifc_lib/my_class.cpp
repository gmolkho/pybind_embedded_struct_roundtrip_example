#include "my_pybind.h"
#include "my_class.h"

void MyExStrLevel0::setAll(const std::string &name_,
                         const int _a,
                         const int _b,
                         const std::vector<double> _c)
{
    this->name.assign(name_);
    this->myObj.a = _a;
    this->myObj.b = _b;
    //this->myObj.c = _c;
}
