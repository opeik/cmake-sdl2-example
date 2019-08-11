#include <SDL.h>
#include <SDL2_framerate.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <cstdio>

auto main(int argc, char **argv) -> int {
    auto isRunning = true;
    auto width     = 600;
    auto height    = 400;

    auto sdl    = SDL_version{};
    auto *ttf   = TTF_Linked_Version();
    auto *image = IMG_Linked_Version();
    auto *mixer = Mix_Linked_Version();
    auto *net   = SDLNet_Linked_Version();
    SDL_GetVersion(&sdl);

    // SDL2_gfx doesn't have a version function. This is just to demonstrate
    // it's linking properly.
    auto gfx = FPSmanager{};

    printf("SDL2 version:\t\t%d.%d.%d\n"
           "SDL2 TTF version:\t%d.%d.%d\n"
           "SDL2 Image version:\t%d.%d.%d\n"
           "SDL2 Mixer version:\t%d.%d.%d\n"
           "SDL2 Net version:\t%d.%d.%d\n",
        sdl.major, sdl.minor, sdl.patch, ttf->major, ttf->minor, ttf->patch,
        image->major, image->minor, image->patch, mixer->major, mixer->minor,
        mixer->patch, net->major, net->minor, net->patch);

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    auto *window  = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 800, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    auto *context = SDL_GL_CreateContext(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (isRunning) {
        auto event = SDL_Event{};

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: isRunning = false; break;
                default: break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glRotatef(1, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex2f(0, 150);
        glColor3f(0, 1, 0);
        glVertex2f(-150, 0);
        glColor3f(0, 0, 1);
        glVertex2f(150, 0);
        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
