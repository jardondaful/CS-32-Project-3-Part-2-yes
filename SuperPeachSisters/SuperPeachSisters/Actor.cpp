#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include "string"
#include <vector>

// Students:  add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
// TODO: x_dist and y_dist instead of x_destination
void Peach::goTo(double x_destination, double y_destination)
{
    if (!getWorld()->collides(this, x_destination - getX(), y_destination - getY()))
    {
        moveTo(x_destination, y_destination);
    }
}

//this is quite incomplete
void Peach::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    //give Peach 150 ticks if she touches the star power somehow
    if (has_star_power)
    {
        is_temporairly_invincible = true;
    }

    //2) and 3) checking for invinciblity
    if (remaining_invincibility_ticks <= 0)
    {
        has_star_power = false;
        is_temporairly_invincible = false;
    }

    if (is_temporairly_invincible)
    {
        remaining_invincibility_ticks--;
    }

    //TODO: #4) each gains temporary invincibility if she overlaps with an emey while she has Jump power or Fire power
    if (ticks_to_recharge_before_next_fire > 0)
    {
        ticks_to_recharge_before_next_fire--;
    }

    if (ticks_to_recharge_before_next_fire == 0)
    {
        can_fire = true;
    }

    //5) chekcing if she currently overlaps with any other gaming object and make bonk
    //Also 7) checkign if not actively jumping during the current tick

    bool somethingUnderPeach = getWorld()->collides(this, 0, -SPRITE_HEIGHT / 2 - 1);
    bool somethingOverPeach = getWorld()->collides(this, 0, SPRITE_HEIGHT / 2 + 1);
    bool somethingLeftOfPeach = getWorld()->collides(this, -SPRITE_WIDTH / 2 - 1, 0);
    bool somethingRightOfPeach = getWorld()->collides(this, SPRITE_WIDTH / 2 + 1, 0);

    if (jumping && somethingOverPeach) {
        jumping = false;
        remaining_jump = 0;
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }

    if (jumping && remaining_jump > 0) {
        goTo(getX(), getY() + (SPRITE_HEIGHT / 2));
        remaining_jump--;
    }

    if (jumping && remaining_jump == 0)
    {
        jumping = false;
    }

    if (!jumping && !somethingUnderPeach)
    {
        goTo(getX(), getY() - (SPRITE_WIDTH / 2));
    }

    somethingUnderPeach = getWorld()->collides(this, 0, -SPRITE_HEIGHT / 2 - 1);
    somethingOverPeach = getWorld()->collides(this, 0, SPRITE_HEIGHT / 2 + 1);

    if (jumping && somethingUnderPeach)
    {
        jumping = false;
        remaining_jump = 0;
    }

    //6) Making Peach move
    int key;

    if (getWorld()->getKey(key))
    {
        cerr << "current pos: " << getX() << ", " << getY() << endl;
        switch (key)
        {
        case KEY_PRESS_LEFT:
        {

            if (getDirection() == 0)
            {
                setDirection(180);
                peach_direction = 180;
            }
            goTo(getX() - (SPRITE_WIDTH / 2), getY());
            break;
        }
        case KEY_PRESS_RIGHT:

            if (getDirection() == 180) {
                setDirection(0);
                peach_direction = 0;
            }
            goTo(getX() + (SPRITE_WIDTH / 2), getY());
            break;
        case KEY_PRESS_UP:

            if (!jumping && somethingUnderPeach)
            {
                if (has_jump_power)
                {
                    remaining_jump = 12;
                }
                else
                {
                    remaining_jump = 8;
                }
                jumping = true;
            }

            //making jumping sound effect

            if (jumping && somethingUnderPeach)
            {
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }

            cout << "Remaining jump after key press up: " << remaining_jump << endl;
            break;

            //coding the shoot power thingy for #9
        case KEY_PRESS_SPACE:
            if (!has_shoot_power)
            {
                break;
            }
            if (ticks_to_recharge_before_next_fire > 0)
            {
                break;
            }
            else
            {

                //why no fireball show up?
                can_fire = true;
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                ticks_to_recharge_before_next_fire = 8;
                if (this->getDirection() == 180)
                {
                    //isValidPosition?
                    getWorld()->addPeachFireball(this->getX() - 4, this->getY());
                    //cerr<<"Fireball" << endl;
                }
                else if (this->getDirection() == 0)
                {
                    getWorld()->addPeachFireball(this->getX() + 4, this->getY());
                    //cerr<<"Fireball" << endl;
                }
                else
                {

                }
                break;
            }
        }
    }
}


void Flag::doSomething()
{
    if (getWorld()->overlappingPeach(this))
    {
        getWorld()->increaseScore(1000);
        die();
        getWorld()->advanceToNextLevel();
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

    if (somethingLeft) setDirection(0);
    else if (somethingRight) setDirection(180);

    int direction = getDirection();
    if (direction == 180) moveTo(getX() - 1, getY());
    else if (direction == 0) moveTo(getX() + 1, getY());
}

//goes horizontal sometimes in air do not know why
void Peach_Fireball::doSomething()
{
    //how to let object know that it was damaged?
    if (getWorld()->overlappingDamageableObject(this, getX(), getY()) && !getWorld()->overlappingPeach(this))
    {
        die();
        damaged();
        return;
    }
    else
    {
        // If there is a valid position underneath the fireball
        // It can hop downwards
        if (getWorld()->isValidPosition(getX(), getY() - 2, this))
        {
            moveTo(getX(), getY() - 2);
        }
        //checking direction parts b) and c)

        if (m_direction == 180)
        {
            if (!getWorld()->isValidPosition(getX() - 2, getY(), this))
            {
                die();
                return;
            }
            else
            {
                moveTo(getX() - 2, getY());
            }
        }
        else if (m_direction == 0)
        {
            if (!getWorld()->isValidPosition(getX() + 2, getY(), this))
            {
                die();
                return;
            }
            else
            {
                moveTo(getX() + 2, getY());
            }
        }
    }
}
