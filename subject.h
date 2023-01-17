#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include "observer.h"
//#include "subscriptions.h"

class Subject
{
protected:
  Observer *view;
  virtual void notifyView(bool won) = 0;

public:
  void attach(Observer *o);
};

#endif
