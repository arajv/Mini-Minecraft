#ifndef HASHTUPLE_H
#define HASHTUPLE_H

using namespace std;

namespace std {

    template <>
    struct hash<tuple<int,int,int>>
    {
       std::size_t operator()(const tuple<int,int,int>& k) const
       {
        using std::size_t;
        using std::hash;
        using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

        return ((hash<int>()(get<0>(k))
               ^ (hash<int>()(get<1>(k)) << 1)) >> 1)
               ^ (hash<int>()(get<2>(k)) << 1);
       }
  };

}

namespace std {

    template <>
    struct hash<tuple<int,int>>
    {
       std::size_t operator()(const tuple<int,int>& k) const
       {
        using std::size_t;
        using std::hash;
        using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

        return ((hash<int>()(get<0>(k))
                 ^ (hash<int>()(get<1>(k)) << 1)) >> 1);
       }
  };

}

#endif // HASHTUPLE_H
