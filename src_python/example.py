import numpy as np
import os,sys,inspect
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0,parentdir)
from ifc_lib.my_pybind import MyExStrLevel0

class ex_str_level_0_py_side():
    def __init__(self, name: str, a: int, b: int, c: dict) -> None:
        """
       From PyBind11 spec.:
       8.1 Note that a direct __init__ constructor should be called, and super() should not be used. For simple cases of
       linear inheritance, super() may work, but once you begin mixing Python and C++ multiple inheritance, things will
       all apart due to differences between Python’s MRO and C++’s mechanisms.
       :param name:
       :param a:
       :param b:

       """
        #BaseObj.__init__(self)  # Without this, undefined behavior may occur if the C++ portions are referenced.
        self._name = name
        self._a = a
        self._b = b
        self._c = c
        print('Example constructor with ', self._a, ', ', self._b)

    @property
    def a(self) -> int:
        return self._a

    @property
    def b(self) -> int:
        return self._b

    @property
    def c(self) -> dict:
        return self._c

    def geta(self) -> int:
        return self._a


class obj_user_py(MyExStrLevel0):

    def __init__(self, name: str, src: ex_str_level_0) -> None:
        """
       From PyBind11 spec.:
       8.1 Note that a direct __init__ constructor should be called, and super() should not be used. For simple cases of
       linear inheritance, super() may work, but once you begin mixing Python and C++ multiple inheritance, things will
       all apart due to differences between Python’s MRO and C++’s mechanisms.
       :param name:
       :param a:
       :param b:

       """
        BaseObj.__init__(self)  # Without this, undefined behavior may occur if the C++ portions are referenced.
        self._name = name
        self._src = src
        self._dst = src
        print('Example constructor with ', self._src)

    @property
    def src(self) -> None:
        return self._src

    @property
    def dst(self) -> None:
        return self._dst

    def change_dst_val(self, in_a: int, in_b: int, in_c: np.double) -> None:
        """
          changing destination object
          :param in_a: int
          :param in_b: int
          :param in_c: np.double
        """
        self._dst.a(in_a)
        self._dst.b(in_b)
        self._dst.c.extend(in_c)
