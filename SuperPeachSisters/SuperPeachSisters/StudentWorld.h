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
class Actor;

class StudentWorld : public GameWorld
{
private:
    Peach* m_peach;
    Block* m_block;
    vector<Actor*> actors;
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld();
    bool isValidPosition(double x, double y);
};

#endif