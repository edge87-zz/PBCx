#include "SwitchObserver.hpp"
#include "SwitchHandler.hpp"
#include "LightController.hpp"
#include "VideoController.hpp"
#include <time.h>

class WikiMode : public SwitchObserver
{
public:
  WikiMode(SwitchHandler *handler);
  
  void resetMode();
  
  virtual void notify(int switchNumber);
  
  void run();
  
  void setLights();
  
private:
  int progress;
  
  bool reset;
    
  timespec endTimer;

};
