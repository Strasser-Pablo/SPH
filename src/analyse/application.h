#ifndef APPLICATION_H
#define APPLICATION_H
#include "world.h"

class Application{
int m_status;
bool m_cont;
World m_world;
public:
  Application();
  int Run();
  void Draw();
  void Next();
  static Uint32 TimerFrames(Uint32 interval,void* param);
  void HandleUserEvent(SDL_Event& event);
};

#endif //APPLICATION_H