#ifndef SWITCHOBSERVER_HPP
#define SWITCHOBSERVER_HPP

class SwitchObserver
{
public:
  virtual void notify(int switchNumber) = 0;
};

#endif //SWITCHOBSERVER_HPP
