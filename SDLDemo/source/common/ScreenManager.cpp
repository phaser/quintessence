// Copyright (C) 2013 Cristian Bidea
// This file is part of TestGame.
//
//    TestGame is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    TestGame is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with TestGame.  If not, see <http://www.gnu.org/licenses/>.

#include <ScreenManager.h>
#include <LoadingScreen.h>
#include <MainMenuScreen.h>
#include <GameScreen.h>
#include <qui/log.h>

ScreenManager::ScreenManager(const qui::StandardGameEntry& game)
    : game(game)
    , state(LOAD_LOADING_SCREEN)
    , currentScreen(NULL)
    , loadingScreen(NULL)
    , nextScene(HASH("NONEXTSCENE"))
{
}

ScreenManager::~ScreenManager()
{
}

void ScreenManager::update(uint64_t dt)
{
    if (getState() == LOAD_LOADING_SCREEN)
    {
        loadingScreen = new LoadingScreen(game);
        if (!loadingScreen->init())
        {
            LOG(LERROR) << "Error on loading loading screen!";
            return;
        }
        currentScreen = loadingScreen;
        nextScene = HASH("Scene::MainMenu");
        setState(LOAD_NEXT_SCENE);
        return;
    }
    else if (getState() == LOAD_NEXT_SCENE)
    {
        if (nextScene == HASH("Scene::MainMenu"))
        {
            IGameScreen *main = new MainMenuScreen(game);
            if (!main->init())
            {
                LOG(LERROR) << "Error loading main screen!";
                return;
            }
            currentScreen = main;
            setState(SCENE_PLAY);
        }
        else if (nextScene == HASH("Scene::Game"))
        {
            IGameScreen *gameScreen = new GameScreen(this->game);
            if (!gameScreen->init())
            {
                LOG(LERROR) << "Error loading game screen!";
                return;
            }
            currentScreen = gameScreen;
            setState(SCENE_PLAY);
        }
    }

    if (getState() != LOAD_LOADING_SCREEN)
    {
        currentScreen->update(dt);
        nextScene = currentScreen->getNextScene();
        if (nextScene != HASH("NONEXTSCENE"))
        {
            setState(LOAD_NEXT_SCENE);
        }
    }
}

void ScreenManager::paint()
{
    if (getState() == LOAD_LOADING_SCREEN)
    {
        return;
    }

    currentScreen->paint();
}


ScreenManager::ScreenManagerState ScreenManager::getState() const
{
    return state;
}

void ScreenManager::setState(ScreenManagerState state)
{
    this->state = state;
    if (this->state == LOAD_NEXT_SCENE)
    {
        if (currentScreen != loadingScreen)
        {
            delete currentScreen;
            currentScreen = loadingScreen;
        }
    }
    else if (this->state == SCENE_PLAY)
    {
        nextScene = HASH("NONEXTSCENE");
    }
}

