#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

namespace caveofprogramming {

class Screen {
public:
    const static int SCREEN_WIDTH = 800;   // Set screen width
    const static int SCREEN_HEIGHT = 600;  // Set screen height

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;

public:
    Screen();
    bool init();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    bool processEvents();
    void close();
    void boxBlur();
};

} /* namespace caveofprogramming */

#endif // SCREEN_H
