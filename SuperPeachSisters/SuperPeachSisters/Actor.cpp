#include "Actor.h"
#include "StudentWorld.h"

const int LEFT = 180;
const int RIGHT = 0;


// Students:  add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//do x_dist and y_dist insteadn of x_destination
void Peach::goTo(double x_destination, double y_destination)
{
    if (!getWorld()->collides(this, x_destination - getX(), y_destination - getY()))
    {
        moveTo(x_destination, y_destination);
    }
}

void Peach::doSomething() {
    int key;
    bool somethingUnderPeach = getWorld()->collides(this, 0, -SPRITE_HEIGHT/2 - 1);
    bool somethingOverPeach = getWorld()->collides(this, 0, SPRITE_HEIGHT/2 + 1);

    if (jumping && somethingOverPeach) {
        jumping = false;
        remaining_jump = 0;
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }

    if (jumping && remaining_jump > 0) {
        goTo(getX(), getY() + (SPRITE_HEIGHT / 2));
        remaining_jump--;
    }

    if (jumping && remaining_jump == 0) {
        jumping = false;
    }

    if (!jumping && !somethingUnderPeach) {
        goTo(getX(), getY() - (SPRITE_WIDTH / 2));
        cout << "Falling" << endl;
    }

    somethingUnderPeach = getWorld()->collides(this, 0, -SPRITE_HEIGHT / 2 - 1);
    somethingOverPeach = getWorld()->collides(this, 0, SPRITE_HEIGHT / 2 + 1);

    if (jumping && somethingUnderPeach) {
        jumping = false;
        remaining_jump = 0;
    }

    if (getWorld()->getKey(key)) {
        cerr << "current pos: " << getX() << ", " << getY() << endl;
        switch (key) {
        case KEY_PRESS_LEFT: {
            cerr << "pressed left" << endl;
            cerr << "moving to position: " << getX() - (SPRITE_WIDTH / 2) << ", " << getY() << endl;
            if (getDirection() == RIGHT) {
                setDirection(LEFT);
            }
            goTo(getX() - (SPRITE_WIDTH / 2), getY());
            //validMoveTo(getX() - (SPRITE_WIDTH / 2), getY());
            break;
        }
        case KEY_PRESS_RIGHT:
            cerr << "pressed right" << endl;
            cerr << "moving to position: " << getX() + (SPRITE_HEIGHT / 2) << ", " << getY() << endl;
            if (getDirection() == LEFT) {
                setDirection(RIGHT);
            }
            goTo(getX() + (SPRITE_WIDTH / 2), getY());
            //validMoveTo(getX() + (SPRITE_WIDTH / 2), getY());
            break;
        case KEY_PRESS_UP:

            if (!jumping && somethingUnderPeach) {
                remaining_jump = 8;
                jumping = true;
            }

            /*if (has_jump_power)
            {
                remaining_jump = 12;
            }
            else
            {
                remaining_jump = 8;
            }*/
            cerr << "pressed up" << endl;
            cerr << "moving to position: " << getX() << ", " << getY() + (SPRITE_HEIGHT / 2) - 1 << endl;
            cout << "Remaining jump after key press up: " << remaining_jump << endl;
            break;
        }
    }
}

void Flag::doSomething()
{
    if (getWorld()->overlappingPeach(this))
    {
        getWorld()->increaseScore(1000);
        die();
    }
}

void Goomba::doSomething()
{
    bool somethingLeft = getWorld()->collides(this, -1, 0);
    bool somethingRight = getWorld()->collides(this, 1, 0);

    if (!isAlive())
    {
        return;
    }

    if (getWorld()->overlappingPeach(this))
    {
        return;
    }

    if (somethingLeft) setDirection(RIGHT);
    else if (somethingRight) setDirection(LEFT);

    int direction = getDirection();
    if (direction == LEFT) moveTo(getX() - 1, getY());
    else if (direction == RIGHT) moveTo(getX() + 1, getY());

    
    //int direction = getDirection();
    //if (direction == LEFT)
    //{
    //    // If something exists on the left
    //    if (somethingLeft)
    //    {
    //        // Start moving towards right
    //        setDirection(RIGHT);
    //        cerr << "SWITCH TO RIGHT"<<endl;
    //    }

    //    // Otherwise, move to left
    //    else moveTo(getX()-1, getY());
    //}
    //
    //if (direction == RIGHT)
    //{
    //    if (somethingRight)
    //    {
    //        setDirection(LEFT);
    //        cerr << "SWITCH TO LEFT" << endl;
    //    }
    //    else
    //    {
    //        moveTo(getX()+1, getY());
    //    }
    //}
}