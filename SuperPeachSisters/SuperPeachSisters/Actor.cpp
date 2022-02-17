#include "Actor.h"
#include "StudentWorld.h"

const int LEFT = 180;
const int RIGHT = 0;


// Students:  add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Peach::goTo(double x_destination, double y_destination)
{
    if (getWorld()->isValidPosition(x_destination, y_destination))
    {
        moveTo(x_destination, y_destination);
    }
}

void Peach::doSomething() {
    int key;
    bool somethingUnderPeach = !getWorld()->isValidPosition(getX(), getY() - (SPRITE_WIDTH / 2) - 1);
    bool somethingOverPeach = !getWorld()->isValidPosition(getX(), getY() + (SPRITE_WIDTH / 2) - 1);

    if (jumping && somethingOverPeach) {
        jumping = false;
        remaining_jump = 0;
    }

    if (jumping && remaining_jump > 0) {
        goTo(getX(), getY() + (SPRITE_WIDTH / 2));
        remaining_jump--;
    }

    if (jumping && remaining_jump == 0) {
        jumping = false;
    }

    if (!jumping && !somethingUnderPeach) {
        goTo(getX(), getY() - (SPRITE_WIDTH / 2));
        cout << "Falling" << endl;
    }

    somethingUnderPeach = !getWorld()->isValidPosition(getX(), getY() - (SPRITE_WIDTH / 2) - 1);
    somethingOverPeach = !getWorld()->isValidPosition(getX(), getY() + (SPRITE_WIDTH / 2) - 1);


    if (jumping && somethingUnderPeach) {
        jumping = false;
        remaining_jump = 0;
    }

    if (getWorld()->getKey(key)) {
        cerr << "current pos: " << getX() << ", " << getY() << endl;
        switch (key) {
        case KEY_PRESS_LEFT:
            cerr << "pressed left" << endl;
            cerr << "moving to position: " << getX() - (SPRITE_WIDTH / 2) << ", " << getY() << endl;
            if (getDirection() == RIGHT) {
                setDirection(LEFT);
            }
            goTo(getX() - (SPRITE_WIDTH / 2), getY());
            //validMoveTo(getX() - (SPRITE_WIDTH / 2), getY());
            break;
        case KEY_PRESS_RIGHT:
            cerr << "pressed right" << endl;
            cerr << "moving to position: " << getX() + (SPRITE_WIDTH / 2) << ", " << getY() << endl;
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
            cerr << "moving to position: " << getX() << ", " << getY() + (SPRITE_WIDTH / 2) - 1 << endl;
            cout << "Remaining jump after key press up: " << remaining_jump << endl;

            break;
        }
    }
}