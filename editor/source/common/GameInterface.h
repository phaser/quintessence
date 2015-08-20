#ifndef EDITOR_SOURCE_COMMON_GAMEINTERFACE_H_
#define EDITOR_SOURCE_COMMON_GAMEINTERFACE_H_
typedef void (*gameInit_t)();
typedef void (*gameUpdate_t)(uint64_t);
typedef void (*gamePaint_t)();
typedef void (*gameExit_t)();
typedef void (*gameSetWindowSize_t)(uint16_t, uint16_t);

#define GAME_INIT               "gameInit"
#define GAME_UPDATE             "gameUpdate"
#define GAME_PAINT              "gamePaint"
#define GAME_EXIT               "gameExit"
#define GAME_SET_WINDOW_SIZE    "gameSetWindowSize"

class GameInterface
{
public:
    gameInit_t gameInit;
    gameUpdate_t gameUpdate;
    gamePaint_t gamePaint;
    gameExit_t gameExit;
    gameSetWindowSize_t gameSetWindowSize;
    GameInterface()
    {
        gameInit = nullptr;
        gameUpdate = nullptr;
        gamePaint = nullptr;
        gameExit = nullptr;
        gameSetWindowSize = nullptr;
    }
};
#endif  // EDITOR_SOURCE_COMMON_GAMEINTERFACE_H_
