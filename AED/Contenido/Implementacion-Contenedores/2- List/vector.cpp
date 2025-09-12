#include <iostream>
class CVector
{
public:
    CVector(int z);
    ~CVector();
    void expand(bool offset);
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    int& operator[](int i);
    void print();
private:
    int *v;
    int size, nelem;
};

CVector::CVector(int z)
{
    size = z;
    nelem = 0;
    v = new int[size];
}

CVector::~CVector()
{
    delete v;
}

void CVector::expand(bool offset)
{
    int *nv = new int[size*2];
    for (int i = 0; i < size; i++ )
        nv[i+offset] = v[i];
    delete v;
    v = nv;
    size = 2*size;
    std::cout<<"\n[exp]\n";
}

void CVector::push_back(int x)
{
    if ( nelem == size )
        expand(0);
    v[nelem++] = x;
    //v[nelem] = x; nelem++;
}

void CVector::push_front(int x)
{
    if ( nelem == size )
        expand(1);
    for (int i = nelem; i > 0 ; i-- )
        v[i] = v[i-1];
    v[0] = x;
}

void CVector::pop_back()
{
    nelem--;
}

void CVector::pop_front()
{
    nelem--;
    for (int i = 0; i < nelem; i++ )
        v[i] = v[i+1];
}

int& CVector::operator[](int i)
{
    return *(v+i);
    //return v[i];
}

void CVector::print()
{
    for (int i = 0; i < nelem; i++ )
        std::cout<<v[i]<<" ";
    std::cout<<"\n";
}

int main()
{
    CVector vec(5);
    vec.push_back(8);
    vec.push_back(6);
    vec.push_back(2);
    vec.push_back(7);
    vec.push_back(9);
    vec.push_back(4);
    vec.print();
    vec[3] = 1;
    vec.print();
}