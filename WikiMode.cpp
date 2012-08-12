#include "WikiMode.hpp"
#include "PlayerMonitor.hpp"

namespace
{
  const int WikiModeBeginning = 27;
}

WikiMode::WikiMode(SwitchHandler *handler)
{  
  handler->registerObserver(16, this);
  resetMode();
}

void WikiMode::resetMode()
{
  progress = 0;
  LightController::SetStrobe(WikiModeBeginning, 4);
  reset = false;
}

void WikiMode::notify(int SwitchNumber)
{
  PlayerMonitor::instance()->incrementScore(100);
  if(progress <= 4 && reset != true)
  {
    progress++;
  }   
  if(progress == 4 && reset != true)
  {
    //mode complete
    reset = true;
    PlayerMonitor::instance()->incrementScore(10000);
    clock_gettime(CLOCK_MONOTONIC, &endTimer);	
    endTimer.tv_sec += 5;
  }
  setLights();
}

void WikiMode::setLights()
{
  if(progress == 1)
  {
    LightController::Set(WikiModeBeginning, 0, Solid);
  }
  for(int i = 0; i <= progress; i++)
  {
    LightController::Set(WikiModeBeginning + 4 - i, 7, Solid);
  }
  if(!reset)
  {
    LightController::Set(WikiModeBeginning + 4 - (progress + 1), 0, Blink);
  }
}

void WikiMode::run()
{
  timespec tempTime;
  clock_gettime(CLOCK_MONOTONIC, &tempTime);	
  if(reset == true)
  {
    if(tempTime.tv_sec > endTimer.tv_sec)
    {
      resetMode();
    }
  }  
}
