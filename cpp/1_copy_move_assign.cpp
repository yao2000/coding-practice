#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

void printMessage(const char * str) {
  std::cout<<str<<"\n";
}

class Vector {
  public: 
    Vector(int n);
    Vector() { printLog("default constructor"); }; 
    Vector(const Vector& v2);
    Vector(Vector&& v2);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&& );
    int& operator[](int i) const;
    ~Vector();
    int size() const { return sz; }
    void print(bool newline=true) const;
    void fill(int kind);
  private: 
    void printLog(const char *str);
    void createVector(int n);
    void deleteVector();
    int *p=nullptr;
    size_t sz =0 ;
};

Vector::Vector(int n)
{
  printLog("ordinary constructor");
  createVector(n);
}

Vector::Vector(const Vector& v2)
{
  printLog("copy constructor"); 
  createVector(v2.size());
  std::copy(v2.p, v2.p+v2.size(), p);
}

Vector::Vector(Vector&& v2) 
{
  printLog("move constructor"); // cleanup target and mvoe
  deleteVector();
  sz = v2.sz;
  p = v2.p;
  v2.sz = 0;
  v2.p = nullptr;
}

Vector::~Vector()
{
  printLog("default destructor");
  deleteVector();
}

Vector& Vector::operator=(const Vector& v2) 
{
  printLog("copy assignment"); // cleanup target and copy
  if (this!=&v2) {
    if (sz>0) {
      deleteVector();
    }
    createVector(v2.size());
    std::copy(v2.p, v2.p+sz, p);
  }
  return *this;
}

Vector& Vector::operator=(Vector&& v2) {
  printLog("move assignment"); // cleanup target and mvoe
  if (this!=&v2) {
    deleteVector();
    sz = v2.sz;
    p = v2.p;
    v2.sz = 0;
    v2.p = nullptr;
  }
  return *this;
}

void Vector::createVector(int n)
{
  sz= n;
  p = new int[sz];
}

void Vector::deleteVector()
{
  if (sz!=0) {
    delete [] p; p = nullptr;
    sz = 0;
  }
}

void Vector::print(bool newline) const
{
  if (sz ==0) {
    std::cout<<"empty vector ";
  } else {
    for (auto i=0; i<sz; ++i) {
      std::cout<<p[i]<<" ";
    }
  }
  if (newline) std::cout<<"\n";
}

void Vector::fill(int kind)
{
  switch (kind) {
    case 1: 
      for (auto i=0; i<sz; ++i) {
        p[i] = i+1;
      }
      break;
    default: 
      for (auto i=0; i<sz; ++i) {
        p[i] = kind;
      }
  }
}

void Vector::printLog(const char *str) 
{ 
  std::cout<<"Vector ("<<(void*)(this)<<"): "<<str<<"\n"; 
}

int& Vector::operator[](int i) const
{
  assert(i<sz);
  return p[i];
}

Vector VectorAdd(const Vector& v1, const Vector& v2)
{
  assert(v1.size() == v2.size());
  Vector v3(v1.size());
  for (auto i=0; i<v1.size(); ++i) {
    v3[i] = v1[i] + v2[i];
  }
  return v3;
}

int main()
{
  printMessage("hello world");

  Vector vec1(5), vec2;
  vec1.fill(1);

  printMessage("\nvec1 is assigned to vec2");
  vec2 = vec1; 
  printMessage("Now vec2 is: ");
  vec2.print();

  printMessage("\nvec3 is inited using copy constructor");
  Vector vec3(vec1);

  printMessage("\nvec1 is moved to vec4");
  Vector vec4 = std::move(vec1);
  vec1.print();
  vec4.print();

  printMessage("\nvec4 is moved to vec44");
  Vector vec44(std::move(vec4));
  vec4.print();
  vec44.print();


  printMessage("\nDeclare vec444 and move vec44 to vec444");
  Vector vec444;
  vec444 = std::move(vec44);
  vec44.print();
  vec444.print();

  printMessage("\nvec5 + vec6 = vec7");
  Vector vec5(5), vec6(5), vec7;
  vec5.fill(1); vec6.fill(5);
  vec7 = VectorAdd(vec5, vec6);
  vec5.print();
  vec6.print();
  vec7.print();

  return 0;
}
