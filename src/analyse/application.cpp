#include "application.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
Application::Application():m_status(0),m_cont(true)
{
SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);
}

int Application::Run()
{

 
    SDL_Event event;
        while (SDL_WaitEvent(&event))
        {

            switch(event.type)
            {
                case SDL_QUIT:
		  m_cont=false;
                break;
            }
            
            if(m_cont==false){
	     break; 
	    }
        }


    return m_status;
}

