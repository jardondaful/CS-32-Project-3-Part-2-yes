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
    Actor(StudentWorld* world, int imageID, double starting_x_position, double starting_y_position, int starting_direction, int depth) :GraphObject(imageID, starting_x_position, starting_y_position, starting_direction, depth)
    {
        m_world = world;
        alive = true;
    };

    virtual void doSomething() = 0;
    StudentWorld* getWorld()
    {
        return m_world;
    };
    virtual bool blocksMovement() = 0;

    virtual void die()
    {
        alive = false;
        return;
    }
    virtual bool isAlive()
    {
        return alive;
    }

    virtual bool isDamageable()
    {
        return true;
    }

    virtual bool damaged()
    {
        return true;
    }
};

class Peach : public Actor
{
private:
    void goTo(double x, double y);

    bool has_star_power;
    bool has_shoot_power;
    bool has_jump_power;
    bool is_temporairly_invincible;
    bool can_fire;

    int health_points;
    int remaining_jump;
    int remaining_invincibility_ticks;
    int lives;
    int ticks_to_recharge_before_next_fire;

    bool jumping;
    int peach_direction;
public:
    Peach(StudentWorld* world, int level_x, int level_y) :Actor(world, IID_PEACH, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 0)
    {
        has_star_power = false;
        has_shoot_power = false;
        has_jump_power = false;
        is_temporairly_invincible = false;
        can_fire = false;

        health_points = 1;
        remaining_jump = 0;
        remaining_invincibility_ticks = 0;
        lives = 3;
        ticks_to_recharge_before_next_fire = 0;

        jumping = false;

    };

    virtual void doSomething();

    bool hasStarPower() 
    { 
        return has_star_power; 
    };

    bool hasShootPower() 
    { 
        return has_shoot_power; 
    };

    bool hasJumpPower() 
    { 
        return has_jump_power; 
    };


    virtual bool blocksMovement() 
    {
        return true; 
    };
};

class Block : public Actor
{
public:
    Block(StudentWorld* world, int level_x, int level_y) : Actor(world, IID_BLOCK, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 2)
    {
    };
    virtual void doSomething()
    {
        return;
    };

    virtual bool blocksMovement()
    {
        return true;
    };

    virtual bool isDamageable()
    {
        return false;
    };
private:
};

class Pipe : public Actor
{
private:
public:
    Pipe(StudentWorld* world, int level_x, int level_y) : Actor(world, IID_PIPE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 2)
    {

    };
    virtual void doSomething()
    {
        return;
    };
    virtual bool blocksMovement()
    {
        return true;
    };

    virtual bool isDamageable()
    {
        return false;
    };
};

class Flag : public Actor
{
private:

public:
    Flag(StudentWorld* world, double level_x, double level_y) : Actor(world, IID_FLAG, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 2)
    {

    };

    virtual void doSomething();

    virtual bool blocksMovement()
    {
        return false;
    };

    virtual bool isDamageable()
    {
        return false;
    };
};

class Mario : public Actor
{
    Mario(StudentWorld* world, int level_x, int level_y) : Actor(world, IID_MARIO, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 1)
    {
        
    };

    virtual void doSomething();

    virtual bool blocksMovement()
    {
        return true;
    };
};
class Goomba : public Actor
{
private:

public:
    Goomba(StudentWorld* world, double level_x, double level_y) : Actor(world, IID_GOOMBA, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, 0, 0)
    {
        
    };

    virtual void doSomething();

    virtual bool blocksMovement()
    {
        return false;
    };
};

class Peach_Fireball : public Actor
{
    private:
    private:
        int m_direction;
    public:
        //TODO: set peach_fireball's direction to peach's direction. how tf do i do that
        Peach_Fireball(StudentWorld* world, double level_x, double level_y, int direction) : Actor(world, IID_PEACH_FIRE, level_x, level_y, 0, 1)
        {
            m_direction = direction;
        };


        virtual void doSomething();

        virtual bool blocksMovement()
        {
            return false;
        };

        virtual bool isDamageable()
        {
            return false;
        }
};
#endif//ACTOR_H_