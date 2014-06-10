function resources(loader)
    shader_textured = loader.shader("qui::Q2D::textured"
                           , "assets/textured_no_color.vsh"
                           , "assets/textured_no_color.fsh")
    shader_color = loader.shader("qui::Q2D::color"
                        , "assets/color.vsh"
                        , "assets/color.fsh")
    
    loader.atlas("assets/game_props.xml")

    mainfont = loader.texture("assets/testfont.png")
    background = loader.texture("assets/loading/background_loading.png")
    watertile = loader.texture("assets/water_tile.png")

    loader.material("Loading::Background", shader_textured, background)
    loader.material("qui::Q2D::color", shader_color, 0)
    loader.material("Game::MainFont", shader_textured, mainfont)
    loader.material("Game::WaterTile", shader_textured, watertile)

    loader.font("MainFont", "assets/testfont.fnt", "Game::MainFont")
end
