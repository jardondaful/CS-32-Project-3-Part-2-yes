#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Level.h"
#include "string"
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) :GameWorld(assetPath)
{
    m_peach = nullptr;
    actors.clear();
}

int StudentWorld::init()
{
    Level current_level(assetPath());
    string file_level = "level0" + to_string(getLevel()) + ".txt";
    Level::LoadResult result = current_level.loadLevel(file_level);

    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Cannot find " << file_level << " data file" << endl;
    }
    else if (result == Level::load_fail_bad_format)
    {
        cerr << file_level << " is improperly formatted" << endl;
    }
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                Level::GridEntry ge;
                ge = current_level.getContentsOf(i, j);
                switch (ge)
                {
                case Level::empty:
                    cout << "Location " << i << ", " << j << " is empty" << endl;
                    break;
                case Level::koopa:
                    if (isValidPosition(i, j))
                    {
                        cout << "Location " << i << ", " << j << " starts with a koopa" << endl;
                    }
                    break;
                case Level::goomba:
                        m_goomba = new Goomba(this, i, j);
                        actors.push_back(m_goomba);
                        cout << "Location " << i << ", " << j << " starts with a goomba" << endl;
                    break;
                case Level::peach:
                        m_peach = new Peach(this, i, j);
                        cout << "Location " << i << ", " << j << " is where Peach starts" << endl;
                        break;
                case Level::flag:
                    if (isValidPosition(i, j))
                    {
                        m_flag = new Flag(this, i, j);
                        actors.push_back(m_flag);
                        cout << "Location " << i << ", " << j << " is where a flag is" << endl;
                    }
                    break;
                case Level::block:
                        m_block = new Block(this, i, j);
                        actors.push_back(m_block);
                        cout << "Location " << i << ", " << j << " holds a regular block" << endl;
                    break;
                case Level::star_goodie_block:
                    if (isValidPosition(i, j))
                    {
                        cout << "Location " << i << ", " << j << " has a star goodie block" << endl;
                    }
                    break;
                case Level::pipe:
                        m_pipe = new Pipe(this, i, j);
                        actors.push_back(m_pipe);
                        cout << "Location " << i << ", " << j << " holds a pipe" << endl;
                    break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_peach->doSomething();
    for (Actor* i : actors)
    {
        i->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::cleanUp()
{
    for (Actor* actor : actors)
    {
        delete actor;
    }
    actors.clear();

    delete m_peach;
    m_peach = nullptr;
}

bool StudentWorld::collides(Actor* actor1, int offset_x = 0, int offset_y = 0) {
    // Go through every actor
    for (Actor* actor2 : actors) {
        if (actor1 == actor2)
        {
            continue;
        }
        if (((actor1->getX() + offset_x) < (actor2->getX() + SPRITE_WIDTH - 1)) &&
            ((actor1->getX() + offset_x + SPRITE_WIDTH - 1) > actor2->getX()) &&
            ((actor1->getY() + offset_y) < (actor2->getY() + SPRITE_HEIGHT - 1)) &&
            ((actor1->getY() + offset_y + SPRITE_HEIGHT - 1) > actor2->getY())) 
        {
            return true;
        }
    }
    return false;
}

bool StudentWorld::isValidPosition(double x, double y)
{   // Go through every actor
    for (Actor* actor : actors)
    {
        if ((actor->getX() + SPRITE_WIDTH - 1) > actor->getX() && x < (actor->getX() + SPRITE_WIDTH - 1))
        {
            if ((actor->getY() + SPRITE_HEIGHT - 1 > actor->getY()) && actor->getY() < (actor->getY() + SPRITE_HEIGHT - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool StudentWorld::intersecting(double x1, double y1, double x2, double y2)
{
    if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH)
    {
        if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT)
        {
            return true;
        }
    }
    return false;
}


bool StudentWorld::overlapping(Actor* a, Actor* b)
{
    return intersecting(a->getX(), a->getY(), b->getX(), b->getY());
}


bool StudentWorld::overlappingPeach(Actor* a)
{
    if (m_peach->isAlive() && overlapping(a, m_peach))
    {
        return true;
    }
    return false;
}
