#ifndef COMMON_H
#define COMMON_H

#include <irrlicht.h>

class Common
{
public:
    Common();
    inline static irr::core::stringc modelsPath()
                  {return irr::core::stringc("../../media/models/");}
};

#endif // COMMON_H
