#include "application.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int EVENT_FRAME_TIMER=1;
Application::Application():m_status(0),m_cont(true)
{
SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,0.1,1000);
    glEnable(GL_DEPTH_TEST);
}

int Application::Run()
{

    SDL_Event event;
      SDL_AddTimer(100, TimerFrames, this);
    Draw();
   
        while (SDL_WaitEvent(&event))
        {

            switch(event.type)
            {
                case SDL_QUIT:
		  m_cont=false;
                break;
		case  SDL_USEREVENT:
		HandleUserEvent(event);
		  break;
            }
            
            if(m_cont==false){
	     break; 
	    }
        }


    return m_status;
}

void Application::Draw()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3ub(0, 0, 255);
    glClearColor(1, 1, 1, 1);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(10,1,1,1,1,1,0,1,0);
	     GLUquadric* param;
 param = gluNewQuadric();
 m_world.Draw(param);
 gluDeleteQuadric(param);
 glFlush();
    SDL_GL_SwapBuffers();
}

Uint32 Application::TimerFrames(Uint32 interval, void* param)
{
 SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = EVENT_FRAME_TIMER;
    event.user.data1 = 0;
    event.user.data2 = 0;
      SDL_PushEvent(&event);
return interval;
}

void Application::Next()
{
m_world.Next();
Draw();
}

void Application::HandleUserEvent(SDL_Event& event)
{
switch(event.user.code){
  case EVENT_FRAME_TIMER:
    Next();
    break;
}
}
