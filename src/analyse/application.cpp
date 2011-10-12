#include "application.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int N=10;
const int EVENT_FRAME_TIMER=1;
Application::Application():m_status(0),m_cont(true),m_look_x(0),m_look_y(0),m_look_z(0),m_cam_x(5),m_cam_y(0),m_cam_z(0),m_vert_x(0),m_vert_y(1),m_vert_z(0)
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
    SDL_AddTimer(500, TimerFrames, this);
    Draw();

    while (SDL_WaitEvent(&event))
    {

        switch (event.type)
        {
        case SDL_QUIT:
            m_cont=false;
            break;
        case  SDL_USEREVENT:
            HandleUserEvent(event);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                Next();
                break;
            case SDLK_UP:
	      m_look_y+=0.5;
	      cout<<"look y "<<m_look_y<<endl;
	      Draw();
	      break;
	    case SDLK_DOWN:
	         m_look_y-=0.5;
		     cout<<"look y "<<m_look_y<<endl;
	      Draw();
	      break;
	    case SDLK_LEFT:
	         m_look_z+=0.5;
		     cout<<"look z "<<m_look_z<<endl;
	      Draw();
	      break;
	    case SDLK_RIGHT:
	         m_look_z-=0.5;
		     cout<<"look z "<<m_look_z<<endl;
	      Draw();
	      break;
	    case SDLK_w:
	      m_cam_x+=0.5;
	      cout<<"cam x "<<m_cam_x<<endl;
	        Draw();
	      break;
	    case SDLK_s:
	      m_cam_x-=0.5;
	      cout<<"cam x "<<m_cam_x<<endl;
	        Draw();
	      break;
	    case SDLK_a:
	      m_cam_z+=0.5;
	       cout<<"cam z "<<m_cam_z<<endl;
	         Draw();
	       break;
	    case SDLK_d:
	      m_cam_z-=0.5;
	       cout<<"cam z "<<m_cam_z<<endl;
	         Draw();
	       break;
	      case SDLK_q:
	      m_cam_y-=0.5;
	       cout<<"cam y "<<m_cam_y<<endl;
	         Draw();
	       break;
	       case SDLK_e:
	      m_cam_y+=0.5;
	       cout<<"cam y "<<m_cam_y<<endl;
	         Draw();
	       break;
	      
            }
        }

        if (m_cont==false) {
            break;
        }
    }


    return m_status;
}

void Application::Draw()
{
    glClearColor(1, 1, 1, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(m_cam_x,m_cam_y,m_cam_z,m_look_x,m_look_y,m_look_z,m_vert_x,m_vert_y,m_vert_z);
    GLUquadric* param;
    param = gluNewQuadric();
    m_world.Draw(param);
    gluDeleteQuadric(param);
    glFlush();
    SDL_GL_SwapBuffers();
    cout<<"finish"<<endl;
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
  for(int i=0;i<N;i++){
    m_world.Next();
  }
	    
    Draw();
}

void Application::HandleUserEvent(SDL_Event& event)
{
    switch (event.user.code) {
    case EVENT_FRAME_TIMER:
        Next();
        break;
    }
}
