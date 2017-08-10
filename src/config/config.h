#ifndef CONFIG_H
#define CONFIG_H

#include "config/inireader.h"
#include <irrlicht.h>

class Config
{
public:
    Config();
    bool load(const std::string& filename);
    // getters
    inline bool fog() const {return m_fog;}
    inline bool freeFly() const {return m_freeFly;}
    inline irr::SIrrlichtCreationParameters params() const {return m_params;}
    // setters
    inline void setFog(bool fog) {m_fog = fog;}
    inline void setFreeFly(bool freeFly) {m_freeFly = freeFly;}

private:
    irr::SIrrlichtCreationParameters m_params;
    bool m_freeFly;
    bool m_fog;
};

#endif // CONFIG_H
