#include "mytuple.h"

MyTuple::MyTuple(int a0,int a1,int a2)
{
    a[0] = a0;  a[1] = a1; a[2] = a2;
}

int& MyTuple::operator[](unsigned int index){
    return a[index];
}

int MyTuple::operator[](unsigned int index) const{
    return a[index];
}

MyTuple& MyTuple::operator=(const MyTuple &v2){
    this->a[0] = v2[0];
    this->a[1] = v2[1];
    this->a[2] = v2[2];
    return *this;
}

bool MyTuple::operator==(const MyTuple &v2) const{
    if ((v2[0]== a[0]) && (v2[1]== a[1]) && (v2[2]== a[2]))
        {
            return true;
        }
        else
        {
            return false;
        }
}

//std::ostream &operator<<(std::ostream &o, const MyTuple &v){
//    o << "\\" << v[0] << "\\" << v[1] << "\\" << v[2] << "\\" ;
//    return o;
//}



