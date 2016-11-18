
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include <cstdlib>
#include <SDL_mixer.h>


using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *ball, *paleta1, *paleta2, *fondo, *ganar, *instrucciones, *p1, *p2;
SDL_Rect rectBall, rectPaleta1, rectPaleta2, rectFondo, rectGanar, rectInstrucciones, rectP1, rectP2;
Mix_Music *music=NULL;

int movX=1;
int vx;
int vy;
int ganador = 0;
bool inicio=true, win=false, ins=false;;
int main( int argc, char* args[] )
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    music = Mix_LoadMUS("battleThemeA.mp3");
   // Mix_PlayMusic(music, -1);
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Ball Game", 100, 100, 720/*WIDTH*/, 405/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }


    int random=0;
    random = (rand() % 2 + 1);
    /*for(int x=0;x<10;x++){
        random = (rand() % 2 + 1);
        cout<<random<<endl;}*/
    if(random==2)
    {
        vy=1;
        vx=1;
    }
    else if (random==1)
    {
        vy=-1;
        vx=-1;
    }


    //Init textures
    int w=0,h=0;

    ball = IMG_LoadTexture(renderer, "ball.png");
    SDL_QueryTexture(ball, NULL, NULL, &w, &h);
    rectBall.x = 300; rectBall.y = 200; rectBall.w = w; rectBall.h = h;

    paleta1 = IMG_LoadTexture(renderer, "paleta.png");
    SDL_QueryTexture(paleta1, NULL, NULL, &w, &h);
    rectPaleta1.x = 20; rectPaleta1.y = 100; rectPaleta1.w = w; rectPaleta1.h = h;

    paleta2 = IMG_LoadTexture(renderer, "paleta.png");
    SDL_QueryTexture(paleta2, NULL, NULL, &w, &h);
    rectPaleta2.x = 690; rectPaleta2.y = 100; rectPaleta2.w = w; rectPaleta2.h = h;

    fondo = IMG_LoadTexture(renderer, "fondo.png");
    SDL_QueryTexture(fondo, NULL, NULL, &w, &h);
    rectFondo.x = 0; rectFondo.y = 0; rectFondo.w = w; rectFondo.h = h;

    ganar = IMG_LoadTexture(renderer, "ganar.png");
    SDL_QueryTexture(ganar, NULL, NULL, &w, &h);
    rectGanar.x = 0; rectGanar.y = 0; rectGanar.w = w; rectGanar.h = h;

    instrucciones = IMG_LoadTexture(renderer, "instrucciones.png");
    SDL_QueryTexture(instrucciones, NULL, NULL, &w, &h);
    rectInstrucciones.x = 0; rectInstrucciones.y = 0; rectInstrucciones.w = w; rectInstrucciones.h = h;

    p1 = IMG_LoadTexture(renderer, "p1.png");
    SDL_QueryTexture(p1, NULL, NULL, &w, &h);
    rectP1.x = 260; rectP1.y = 177.5; rectP1.w = w; rectP1.h = h;

    p2 = IMG_LoadTexture(renderer, "p2.png");
    SDL_QueryTexture(p2, NULL, NULL, &w, &h);
    rectP2.x = 260; rectP2.y = 177.5; rectP2.w = w; rectP2.h = h;


    //Main Loop
    while(true)
    {
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_w)
                    rectPaleta1.y-=4;
                if(Event.key.keysym.sym == SDLK_s)
                    rectPaleta1.y+=4;
                if(Event.key.keysym.sym == SDLK_UP)
                    rectPaleta2.y-=4;
                if(Event.key.keysym.sym == SDLK_DOWN)
                    rectPaleta2.y+=4;
                if(Event.key.keysym.sym == SDLK_RETURN)
                {
                    inicio=false;
                    Mix_PlayMusic(music, -1);
                }
                if(Event.key.keysym.sym == SDLK_p)
                {
                    inicio=true;
                    ganador=0;
                    win=false;
                    ins=false;

                    rectBall.x = 300; rectBall.y = 200;
                    rectPaleta1.x = 20; rectPaleta1.y = 100;
                    rectPaleta2.x = 690; rectPaleta2.y = 100;
                }
                if(Event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    inicio=true;
                    ins=false;
                }
                if(Event.key.keysym.sym == SDLK_i)
                {
                    inicio=false;
                    ins=true;
                }

            }
        }
        if(inicio)
        {
            SDL_RenderCopy(renderer, fondo, NULL, &rectFondo);
        }
        if(ins)
        {
            SDL_RenderCopy(renderer, instrucciones, NULL, &rectInstrucciones);
        }
        if (win)
        {
            SDL_RenderCopy(renderer, ganar, NULL, &rectGanar);
            if(ganador==1)
                SDL_RenderCopy(renderer, p1, NULL, &rectP1);
            if(ganador==2)
                SDL_RenderCopy(renderer, p2, NULL, &rectP2);
        }
        if(!inicio&&!ins&&!win)
        {
            SDL_RenderCopy(renderer, ball, NULL, &rectBall);
            SDL_RenderCopy(renderer, paleta1, NULL, &rectPaleta1);
            SDL_RenderCopy(renderer, paleta2, NULL, &rectPaleta2);

            if(rectBall.x==0)
            {
                cout<<"Paleta 2 Gano"<<endl;
                win=true;
                ganador=2;
            }

            if(rectBall.x==SDL_GetWindowSurface(window)->w)
            {
                cout<<"Paleta 1 Gano"<<endl;
                win=true;
                ganador=1;
            }

            if((rectPaleta2.y<=rectBall.y&&rectPaleta2.y+rectPaleta2.h>=rectBall.y+rectBall.h)&&(rectPaleta2.x==rectBall.x+rectBall.w))
                vx=-1;
            if((rectPaleta2.x==rectBall.x)&&(rectPaleta2.y/2<=rectBall.y||(rectPaleta2.y+rectPaleta2.h)/2>=rectBall.y+rectBall.h))
                vy=-1;
            //else vy=1;
            if((rectPaleta1.x+rectPaleta1.w==rectBall.x)&&(rectPaleta1.y<=rectBall.y&&rectPaleta1.y+rectPaleta1.h>=rectBall.y+rectBall.h))
                vx=1;
            if((rectPaleta1.x+rectPaleta1.w==rectBall.x)&&(rectPaleta1.y/2<=rectBall.y||(rectPaleta1.y+rectPaleta1.h)/2>=rectBall.y+rectBall.h))
                vy=-1;
            //else vy=1;

            if(rectBall.y==SDL_GetWindowSurface(window)->h)
                vy=-1;
            else if(rectBall.y==0)
                vy=1;

            movX++;
            if(movX%25==0)
            {
                rectBall.x+=vx;
                rectBall.y+=vy;
            }


        }
        SDL_RenderPresent(renderer);
    }

	return 0;
}
