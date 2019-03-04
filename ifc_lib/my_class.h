#ifndef PYBINDBASICEXAMPLE_MY_CLASS_H
#define PYBINDBASICEXAMPLE_MY_CLASS_H

#include <string>
#include "ex_struct.h"


// Shorter for readability
//using vvi = std::vector<std::vector<int>>;
using vd = std::vector<double>;

class MyExStrLevel0 : public ex_str_level_0_t {
public:
    MyExStrLevel0(const std::string &_name,
                const int _a,
                const int _b,
                const std::vector<double> _c
    ) : name(_name)
    /*ex_str_level_0_t(a, b, c)*/
    {
        /* (assert(myObj == nullptr));
         myObj = new ex_str_level_0_t[1];*/
        myObj.a = _a;
        myObj.b = _b;
        myObj.c = _c;
    }
    MyExStrLevel0( const MyExStrLevel0 &obj){myObj=obj.myObj; name.assign(obj.name);};  // copy constructor
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
    void setVec(vd c_) {c = c_;}
    vd getVec() const {return c;}

    void setAll(const std::string &name,
                const int _a,
                const int _b,
                const std::vector<double> _c);

    MyExStrLevel0(){};
    virtual ~MyExStrLevel0(){} ;
    std::string name;
    ex_str_level_0_t myObj;// = nullptr;
};


#endif //PYBINDBASICEXAMPLE_MY_CLASS_H
