#include <qui/LuaResourceLoadingFunctions.h>
#include <qui/TextureManager.h>
#include <qui/ShaderManager.h>
#include <qui/MaterialManager.h>
#include <qui/text/FontManager.h>
#include <qui/text/Font.h>
#include <qui/Material.h>
#include <qui/TextureAtlas.h>
#include <qui/log.h>

EXPORT_OOLUA_FUNCTIONS_5_NON_CONST(LuaResourceLoadingFunctions
                                 , texture
                                 , shader 
                                 , atlas
                                 , material
                                 , font)
EXPORT_OOLUA_FUNCTIONS_0_CONST(LuaResourceLoadingFunctions)

unsigned int LuaResourceLoadingFunctions::texture(const char* texture)
{
    qui::TextureManager tm;
    if (!tm.loadTexture(texture))
    {
        LOG(LERROR) << "Failed to load texture: " << texture;
        return 0xFFFFFFFF;
    }
    return qui::Hash(texture).value;
}

unsigned int LuaResourceLoadingFunctions::shader(const char* name, const char* vertex, const char* fragment)
{
    qui::ShaderManager sm;
    unsigned int shaderId = qui::Hash(name).value;
    bool result = sm.loadShader(shaderId
                              , vertex
                              , fragment);
    if (!result)
    {
        LOG(LERROR) << "Shader "
                    << name
                    << "["
                    << vertex
                    << "]["
                    << fragment
                    << "] didn't load!";
    }

    return shaderId;
}

bool LuaResourceLoadingFunctions::atlas(const char* filename)
{
    qui::TextureAtlas *atlas = new qui::TextureAtlas(filename);
    atlas->loadModules();
    atlas->createMaterials(HASH("qui::Q2D::textured"));
    delete atlas;
    return true;
}

bool LuaResourceLoadingFunctions::material(const char* name, unsigned int shader, unsigned int texture)
{
    qui::TextureManager tm;
    qui::MaterialManager mm;
    qui::ShaderManager sm;
    cpp0x::shared_ptr<qui::Material> material(new qui::Material());
    cpp0x::shared_ptr<qui::GLShader> loaded_shader = sm.getShader(shader);
    if (loaded_shader.get() != nullptr)
    {
        material->setShader(loaded_shader);
    }
    cpp0x::shared_ptr<qui::GLTexture> loaded_texture = tm.getTexture(texture);
    if (loaded_texture.get() != nullptr)
    {
        material->setTexture(loaded_texture);
    }
    mm.addMaterial(name, material);
    return true;
}

bool LuaResourceLoadingFunctions::font(const char* name, const char* filename, const char* material)
{
    unsigned int fontId = HASH(name);
    qui::text::FontManager fm;
    fm.loadFont(fontId, filename);
    fm.getFont(fontId)->setMaterial(material);
    return true;
}

