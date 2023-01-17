#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>

class Observer
{
public:
  virtual void update(bool won) = 0;
  virtual ~Observer() = default;
  //virtual std::string getName() const = 0;
};

#endif
