#ifndef APPLICATION_H
#define APPLICATION_H
#include "world.h"

class Application{
int m_status;
bool m_cont;
World m_world;
double m_look_x;
double m_look_y;
double m_look_z;
double m_cam_x;
double m_cam_y;
double m_cam_z;
double m_vert_x;
double m_vert_y;
double m_vert_z;
public:
  Application();
  int Run();
  void Draw();
  void Next();
  static Uint32 TimerFrames(Uint32 interval,void* param);
  void HandleUserEvent(SDL_Event& event);
};

#endif //APPLICATION_H