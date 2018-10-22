#ifndef PARTICLE_H
#define PARTICLE_H

namespace caveofprogramming {

class Particle {
public:
    double m_x;
    double m_y;

private:
    double m_speed;
    double m_direction;

public:
    Particle();
    void update(int interval);

private:
    void init();
};

} /* namespace caveofprogramming */

#endif // PARTICLE_H
