#include "Screen.h"

namespace caveofprogramming {

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {

}

bool Screen::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) { // Initializes SDL library -- Returns 0 on success or a negative error code on failure
        return false;
    }

    m_window = SDL_CreateWindow("Particle Fire Explosion", SDL_WINDOWPOS_UNDEFINED, // Create a window
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(m_window == NULL) { // Check if window was created -- NULL on failure
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); // Create a 2D rendering context for a window
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, // Create a texture for a rendering context
                                  SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    if(m_renderer == NULL) { // Check if renderer was made
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    if(m_texture == NULL) { // Check if texture was made
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT]; // Make a buffer that stores the texture
    m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

    memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32)); // Set block of memory to a value (clear from junk)
    memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

    return true;
}

void Screen::boxBlur() {
    Uint32 *temp = m_buffer1;
    m_buffer1 = m_buffer2;
    m_buffer2 = temp;

    for(int y=0; y < SCREEN_HEIGHT; y++) {
        for(int x=0; x < SCREEN_WIDTH; x++) {

            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            for(int row=-1;row <=1; row++) {
                for(int col=-1; col<=1; col++) {

                    int currentX = x + col;
                    int currentY = y + row;

                    if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                        Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }

            Uint8 red = redTotal/9;
            Uint8 green = greenTotal/9;
            Uint8 blue = blueTotal/9;

            setPixel(x, y, red, green, blue);
        }
    }
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32)); // Update texture rectangle with new pixel data
    SDL_RenderClear(m_renderer); // Clear the entire screen to a selected color
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); // Copy (a portion of) the texture to the current rendering target
    SDL_RenderPresent(m_renderer); // Update the screen with new renderer
}

bool Screen::processEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {     // Poll currently pending events
        if(event.type == SDL_QUIT) {
            return false;
        }
    }

    return true;
}

void Screen::close() {
    delete [] m_buffer1;              // Remove buffer from memory
    delete [] m_buffer2;              // Remove buffer from memory
    SDL_DestroyRenderer(m_renderer);  // Remove renderer from memory
    SDL_DestroyTexture(m_texture);    // Remove texture from memory
    SDL_DestroyWindow(m_window);      // Remove window from memory
    SDL_Quit();                       // Clean up all initialized subsystems
}

} /* namespace caveofprogramming */
