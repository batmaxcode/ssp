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
    inline bool freeFly() const {return m_freeFly;}
    inline irr::SIrrlichtCreationParameters params() const {return m_params;}
    // setters
    inline void setFreeFly(bool freeFly) {m_freeFly = freeFly;}

private:
    irr::SIrrlichtCreationParameters m_params;
    bool m_freeFly;
};

#endif // CONFIG_H
