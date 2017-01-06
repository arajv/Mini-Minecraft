#ifndef MYTUPLE_H
#define MYTUPLE_H
#include <tuple>


class MyTuple
{
private:
    int a[3];
public:
    MyTuple(int,int,int);
    int& operator[](unsigned int index);
    int operator[](unsigned int index) const;
    MyTuple& operator=(const MyTuple &v2);
    bool operator==(const MyTuple &v2) const;

};
//std::ostream &operator<<(std::ostream &o, const MyTuple &v);
namespace std {

  template <>
  struct hash<MyTuple>
  {
    std::size_t operator()(const MyTuple& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(k[0])
               ^ (hash<int>()(k[1]) << 1)) >> 1)
               ^ (hash<int>()(k[2]) << 1);
    }
  };

}
#endif // MYTUPLE_H
