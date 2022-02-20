#ifndef STUDENT_WORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>

using namespace std;

class Peach;
class Block;
class Pipe;
class Flag;
class Mario;
class Flower;
class Mushroom;
class Star;
class Piranha_Fireball;
class Peach_Fireball;
class Shell;
class Goomba;
class Koopa;
class Piranha;
class Actor;

class StudentWorld : public GameWorld
{
private:
    Peach* m_peach;
    Block* m_block;
    Pipe* m_pipe;
    Flag* m_flag;
    Mario* m_mario;
    Flower* m_flower;
    Mushroom* m_mushroom;
    Star* m_star;
    Piranha_Fireball* m_piranha_fireball;
    Peach_Fireball* m_peach_fireball;
    Shell* m_shell;
    Goomba* m_goomba;
    Koopa* m_koopa;
    Piranha* m_pirahna;
    vector<Actor*> actors;

    bool m_level_completed;
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();

    virtual int init();
    virtual int move();
    virtual void cleanUp();


    bool intersecting(double x1, double y1, double x2, double y2);
    bool collides(Actor* actor1, int offset_x, int offset_y);
    bool overlapping(Actor* a, Actor* b);
    bool overlappingPeach(Actor* a);

    void addPeachFireball(double x, double y);

    void levelCompleted()
    {
        m_level_completed = true;
    }
};

#endif