/*absolutely! derived classes in arrays or vectors of base classes is one of the most useful properties of polymorphism.
However, the object can't just be of the type, rather it needs to be a pointer of the the base class.
The concept of polymorphism is that a pointer of a base class can point to any class that derives from it.
here is an example i had lying around: */
#include <iostream>
#include <vector>
using namespace std;

class a
{
protected:
    int test;
public:
    virtual void SetTest(int arg) {test = arg;}
    int GetTest() {return test;}
};

class b : public a
{
public:
    void SetTest(int arg) {test = arg+1;}
};

class c : public a
{
public:
    void SetTest(int arg) {test = arg+2;}
};

int main()
{
    vector<a *> derivedClassHolder;
    derivedClassHolder.push_back(new b);
    derivedClassHolder.push_back(new c);
    derivedClassHolder.push_back(new a);
    derivedClassHolder.push_back(new c);
    derivedClassHolder.push_back(new b);

    for(int i = 0; i < (int)derivedClassHolder.size() ; i++)
    {
        derivedClassHolder[i]->SetTest(5);
    }

    for(int i = 0; i < (int) derivedClassHolder.size() ; i++)
    {
        cout << derivedClassHolder[i]->GetTest() << "  ";
    }
    return 0;
}
Edit & Run


/*the output would be 6 7 5 7 6. */

// from another example:
for(std::list<Shape*>::const_iterator p=shapes.begin(), e=shapes.end(); p!=e; ++p) {
  (*p)->draw(window);
}
