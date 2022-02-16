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
                    cout << "Location " << i << ", " << j << " starts with a koopa" << endl;
                    break;
                case Level::goomba:
                    cout << "Location " << i << ", " << j << " starts with a goomba" << endl;
                    break;
                case Level::peach:
                    m_peach = new Peach(this, i, j);
                    cout << "Location " << i << ", " << j << " is where Peach starts" << endl;
                    break;
                case Level::flag:
                    cout << "Location " << i << ", " << j << " is where a flag is" << endl;
                    break;
                case Level::block:
                    m_block = new Block(this, i, j);
                    actors.push_back(m_block);
                    cout << "Location " << i << ", " << j << " holds a regular block" << endl;
                    break;
                case Level::star_goodie_block:
                    cout << "Location " << i << ", " << j << " has a star goodie block" << endl;
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

bool StudentWorld::isValidPosition(double x, double y)
{
    for (Actor* actor : actors) 
    {
        if (x + SPRITE_WIDTH - 1 > actor->getX() && x < actor->getX() + SPRITE_WIDTH - 1) 
        {
            if (y + SPRITE_HEIGHT - 1 > actor->getY() && y < actor->getY() + SPRITE_HEIGHT - 1) 
            {
                return false;
            }
        }
    }
    return true;
}