#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject
{
private:
    StudentWorld* m_world;
    bool alive;
public:
    Actor(StudentWorld* world, int imageID, double starting_x_position, double starting_y_position, int starting_direction, int depth) :GraphObject(imageID, starting_x_position, starting_y_position, starting_direction, depth), m_world(world) //how to do default stuff?
    {
        alive = true;
    };

    virtual void doSomething() = 0;
    StudentWorld* getWorld()
    {
        return m_world;
    };
    virtual bool blocksMovement() = 0;
};


class Peach : public Actor
{
private:
    void goTo(double x, double y);
    bool has_star_power;
    bool has_shoot_power;
    bool has_jump_power;
    bool is_temporairly_invisible;
    int health_points;
    int remaining_jump;
    bool jumping;
public:
    Peach(StudentWorld* world, int level_x, int level_y) :Actor(world, IID_PEACH, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 1), has_star_power(false), has_shoot_power(false), has_jump_power(false), is_temporairly_invisible(false), health_points(1), remaining_jump(0), jumping(false)
    {
    };

    virtual void doSomething();

    virtual bool blocksMovement()
    {
        return true;
    }
};

class Block : public Actor
{
public:
    Block(StudentWorld* world, double level_x, double level_y) :Actor(world, IID_BLOCK, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 2)
    {

    };
    virtual void doSomething()
    {
        return;
    }

    virtual bool blocksMovement()
    {
        return true;
    }
private:
};
#endif// ACTOR_H_
