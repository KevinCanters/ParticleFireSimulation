#include <iostream>
#include <SDL.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace caveofprogramming;

int main(int argv, char** args) {   // Needs these arguments to work.

    srand(time(NULL));

    Screen screen;

    if(screen.init() == false) {
        cout << "Error initializing SDL." << endl;
    }

    Swarm swarm;

    while(true) {
        // Update particles

        // Draw particles
        int elapsed = SDL_GetTicks();

        swarm.update(elapsed);

        unsigned char green = (1 + sin(elapsed * 0.001)) * 128;
        unsigned char red = (1 + sin(elapsed * 0.002 - 1)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.003)) * 128;

        const Particle * const pParticles = swarm.getParticles();
        for(int i=0; i<Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];

            // Change x/y-coords at same rate + centralize (0,0) them
            int x = particle.m_x * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_WIDTH / 2;
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        // Draw the screen
        screen.update();

        // Check for messages/events
        if(screen.processEvents() == false) {
            break;
        }
    }

    screen.close();

    // Sleep(2000);

    return 0;
}
