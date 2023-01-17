#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include <iostream>
using namespace std;

void Subject::attach(Observer *o)
{
    view = o;
}
