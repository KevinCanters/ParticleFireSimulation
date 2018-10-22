#ifndef SWARM_H
#define SWARM_H
#include "Particle.h"

namespace caveofprogramming {

class Swarm {
public:
    const static int NPARTICLES = 5000;

private:
    Particle * m_pParticles;
    int lastTime;

public:
    Swarm();
    virtual ~Swarm();
    void update(int elapsed);

    const Particle * const getParticles() {return m_pParticles; };
};

} /* namespace caveofprogramming */

#endif // SWARM_H
