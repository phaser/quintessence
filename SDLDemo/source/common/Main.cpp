#include <qui/StandardGameEntry.h>

class SDLGame : public qui::StandardGameEntry
{
    SDLGame();
    void init();
    void update(uint64_t dt);
    void paint();
    void cleanup();
    void onSystemEvent(qui::SystemEvent event);
};

SDLGame::SDLGame()
    : StandardGameEntry()
{
}

void SDLGame::init()
{
}

void SDLGame::update(uint64_t dt)
{
}

void SDLGame::paint()
{
}

void SDLGame::cleanup()
{
}

void SDLGame::onSystemEvent(qui::SystemEvent event)
{
}
