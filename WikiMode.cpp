#include "WikiMode.hpp"

namespace
{
  const int WikiModeBeginning = 27;
}

WikiMode::WikiMode(SwitchHandler *handler, VideoController *pnt)
{  
  handler->registerObserver(16, this);
  resetMode();

  Video = pnt;

}

void WikiMode::resetMode()
{
  progress = 0;
  LightController::SetStrobe(WikiModeBeginning, 4);
  reset = false;
}

void WikiMode::notify(int SwitchNumber)
{
  if(progress <= 4 && reset != true)
  {
    progress++;
  }   
  if(progress == 4)
  {
    //mode complete
    reset = true;
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

    // Seg faults hard. Tries to flip the screen and render to it while others are. bad move.
    //Video->Play("lac.mp4");
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
