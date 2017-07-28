#include "config.h"

Config::Config() :
    m_freeFly(false)
{

}

bool Config::load(const std::string &filename)
{
    INIReader reader(filename);
    if(reader.parseError())
    {
        return false;
    }
    m_params.WindowSize.Height = reader.getInteger("general","height",600);
    m_params.WindowSize.Width = reader.getInteger("general","width",800);
    m_params.Fullscreen = reader.getBoolean("general","fullScreen",false);
    m_params.Vsync = reader.getBoolean("general","vSync",false);
    m_params.Stencilbuffer = reader.getInteger("general","vSync",1);
    setFreeFly( reader.getBoolean("general","freeFly",false) );
    return true;
}

