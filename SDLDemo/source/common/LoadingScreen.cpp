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

#include <LoadingScreen.h>
#include <LoadingScene.h>
#include <qui/GLTexture.h>
#include <qui/MaterialManager.h>
#include <qui/Material.h>
#include <qui/Hash.h>
#include <qui/cpp11compat.h>
#include <qui/text/FontManager.h>
#include <qui/TextureAtlas.h>
#include <qui/LuaResourceLoadingFunctions.h>
#include <oolua.h>
#include <qui/VirtualFS.h>
#include <qui/log.h>

LoadingScreen::LoadingScreen(const qui::StandardGameEntry& game)
    : IGameScreen(game)
    , scene(new LoadingScene(game))
{
}

LoadingScreen::~LoadingScreen()
{
}

bool LoadingScreen::init()
{
    /*
    qui::ReflectionManager refMgr;
    refMgr.setTypeMappings<qui::resourceloader::TextureDescriptor>();
    refMgr.setTypeMappings<qui::resourceloader::ShaderDescriptor>();
    refMgr.setTypeMappings<qui::resourceloader::MaterialDescriptor>();
    refMgr.setTypeMappings<qui::resourceloader::FontDescriptor>();
    refMgr.setTypeMappings<qui::resourceloader::LoadList>();
    refMgr.setTypeMappings<qui::resourceloader::AtlasDescriptor>();
    refMgr.setClassMappings(qui::resourceloader::mappings, qui::resourceloader::NUM_MAPS);
    qui::resourceloader::Loader loader;
    qui::resourceloader::LoadList *list = loader.loadList("assets/resource_list.xml");
    loader.loadResources(list);
    delete list;
    */
    
    OOLUA::Script s;
    LuaResourceLoadingFunctions* lrlf = new LuaResourceLoadingFunctions;
    qui::VirtualFS fs;
    cpp0x::shared_ptr<char> script_text = fs.getFileContentsAsText("assets/resource_list.lua");
    s.run_chunk(script_text.get());
    s.register_class<LuaResourceLoadingFunctions>(lrlf);
    bool result = s.call("resources", lrlf);
    if (!result)
    {
        LOG(LERROR) << "assets/resource_list.lua script execution failed"
                    << "\n" << OOLUA::get_last_error(s.get_ptr());
    }
    delete lrlf;
    return scene->init();
}

void LoadingScreen::update(uint64_t /* dt */)
{
}

void LoadingScreen::paint()
{
    scene->render();
}

