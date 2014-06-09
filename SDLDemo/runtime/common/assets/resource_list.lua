function resources(loader)
    shader_textured = shader("qui::Q2D::textured"
                           , "assets/textured_no_color.vsh"
                           , "assets/textured_no_color.fsh")
    shader_color = shader("qui::Q2D::color"
                        , "assets/color.vsh"
                        , "assets/color.fsh")
    
    atlas("assets/game_props.xml")

    mainfont = texture("assets/testfont.png")
    background = texture("assets/loading/background_loading.png")
    watertile = texture("assets/water_tile.png")

    material("Loading::Background", shader_textured, background)
    material("qui::Q2D::color", shader_color, 0)
    material("Game::MainFont", shader_textured, mainfont)
    material("Game::WaterTile", shader_textured, watertile)

    font("MainFont", "assets/testfont.fnt", "Game::MainFont")
end
