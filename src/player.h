#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include <irrKlang.h>

class Player
{
public:
    Player(irr::IrrlichtDevice* device);
    ~Player();

    irr::core::vector3df ellipsoid() const;
    irr::scene::ICameraSceneNode* camera() const;
    irr::scene::IAnimatedMeshSceneNode *node() const;
    irr::scene::ISceneNode *fire() const;


    void setKeyPressed(irr::EKEY_CODE key, bool pressed);
    void setMouseButtonPressed(irr::EMOUSE_INPUT_EVENT event);
    void setPosition(irr::f32 x, irr::f32 y, irr::f32 z);
    void setRun(bool run);
    bool animationFire() const;



    void setSoundEngine(irrklang::ISoundEngine *soundEngine);

private:
    irr::scene::ICameraSceneNode* m_camera;
    irr::IrrlichtDevice* m_device;
    irr::scene::ISceneNode *m_fire;
    irr::scene::ISceneNode *pricel;
    irr::scene::IAnimatedMeshSceneNode* m_node;
    irrklang::ISoundEngine* m_soundEngine;
    irrklang::ISound* m_walkSound = nullptr;
    irrklang::ISound* m_shotSound = nullptr;
    irrklang::ISound* m_runSound = nullptr;
    bool m_animationFire;
    bool m_animationMove;

    bool m_keyA;
    bool m_keyD;
    bool m_keyS;
    bool m_keyW;
    bool m_leftButton;
    bool m_run;

    void setAnimationFire(bool val, bool hard = false);
    void setAnimationMove(bool val, bool hard = false);


};

#endif // PLAYER_H
