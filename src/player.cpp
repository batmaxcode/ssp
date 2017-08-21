#include "player.h"
#include <iostream>

using namespace irr;
using namespace irrklang;

Player::Player(IrrlichtDevice* device) :
    m_device(device),
    m_animationFire(false),
    m_animationMove(false),
    m_keyA(false),
    m_keyD(false),
    m_keyS(false),
    m_keyW(false),
    m_leftButton(false),
    m_run(false)
{
    SKeyMap keyMap[9];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_UP;
    keyMap[1].Action = EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = KEY_KEY_W;

    keyMap[2].Action = EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = KEY_DOWN;
    keyMap[3].Action = EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = KEY_KEY_S;

    keyMap[4].Action = EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = KEY_LEFT;
    keyMap[5].Action = EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = KEY_KEY_A;

    keyMap[6].Action = EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = KEY_RIGHT;
    keyMap[7].Action = EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = KEY_KEY_D;

    keyMap[8].Action = EKA_JUMP_UP;
    keyMap[8].KeyCode = KEY_KEY_J;


    // camera
    // 1.2 move speed
    // 3.2 fast move
    m_camera = m_device->getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, 1.2f, -1, keyMap, 9, false, 3.f);
    m_camera->setPosition(core::vector3df(10700*2,5085*2,27600*2)); // light
    m_camera->setTarget(core::vector3df(4897*2,343*2,17800*2));
    m_camera->setFarValue(42000.0f);

    // ---- fire -----

    m_fire = m_device->getSceneManager()->addBillboardSceneNode(camera(), core::dimension2d<f32>(200, 200));
    m_fire->setPosition(core::vector3df(0,0,150));
    m_fire->setMaterialFlag(video::EMF_LIGHTING, false);
    m_fire->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    m_fire->setMaterialTexture(0, m_device->getVideoDriver()->getTexture("../../media/textures/particlewhite.bmp"));
    m_fire->setVisible(false);

    // --------------

    // ---- pricel -----

    pricel = m_device->getSceneManager()->addBillboardSceneNode(camera(), core::dimension2d<f32>(1, 1));
    pricel->setPosition(core::vector3df(0,0,10));
    pricel->setMaterialFlag(video::EMF_LIGHTING, false);
    pricel->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    pricel->setMaterialTexture(0, m_device->getVideoDriver()->getTexture("../../media/textures/pricel.bmp"));

    // --------------






    scene::IAnimatedMesh* mesh = m_device->getSceneManager()->getMesh("../../media/models/ak12.x");
    if (!mesh)
    {
        m_device->drop();
    }
    m_node = m_device->getSceneManager()->addAnimatedMeshSceneNode(mesh,camera() );
    if (m_node)
    {
        //animnode->setScale(core::vector3df(30.0f,30.0f,30.0f));
        m_node->setScale(core::vector3df(30.0f,30.0f,30.0f));
//        if(shadows)
            m_node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        m_node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        //node->setPosition(core::vector3df(27,-40,20));
        m_node->setPosition(core::vector3df(15,-92,68));
        //animnode->setPosition(core::vector3df(9170,610*2,60540));
        m_node->setRotation(core::vector3df(0,180,0));
        //node->addShadowVolumeSceneNode();
        m_node->setMaterialTexture( 0, m_device->getVideoDriver()->getTexture("../../media/textures/ak12.png") );
        m_node->setAnimationSpeed(10.f);
        m_node->setFrameLoop(0,0);

    }


}

irr::core::vector3df Player::ellipsoid() const
{
    return core::vector3df(250,350,250);
}

irr::scene::ICameraSceneNode* Player::camera() const
{
    return m_camera;
}

irr::scene::IAnimatedMeshSceneNode *Player::node() const
{
    return m_node;
}

irr::scene::ISceneNode *Player::fire() const
{
    return m_fire;
}

void Player::setAnimationFire(bool val, bool hard)
{
    if(m_animationFire != val || hard == true)
    {
        m_animationFire = val;
        if(val == true)
        {
            m_node->setFrameLoop(30,50);
            m_node->setAnimationSpeed(120);
            m_node->setLoopMode(true);
            if(m_shotSound == nullptr)
            {
                m_shotSound = m_soundEngine->play2D("../../media/sounds/shots.ogg", true ,false, true);
            }
        }
        else if(m_animationMove == true)
        {
            setAnimationMove(true, true);
            if(m_shotSound != nullptr)
            {
                m_shotSound->stop();
                m_shotSound->drop();
                m_shotSound = nullptr;
            }
        }
        else
        {
            m_node->setFrameLoop(0,0);
            m_node->setLoopMode(false);
            if(m_shotSound != nullptr)
            {
                m_shotSound->stop();
                m_shotSound->drop();
                m_shotSound = nullptr;
            }
        }
    }
}

void Player::setAnimationMove(bool val, bool hard)
{
    if(m_animationMove != val || hard == true)
    {
        m_animationMove = val;
        if(m_animationFire == true)
        {
            return;
        }
        if(val == true)
        {
            m_node->setFrameLoop(10,30);
            m_node->setAnimationSpeed(35);
            m_node->setLoopMode(true);
            if(m_walkSound == nullptr)
            {
                m_walkSound = m_soundEngine->play2D("../../media/sounds/walk.ogg", true, false, true);
            }
        }
        else
        {
            m_node->setFrameLoop(0,0);
            m_node->setLoopMode(false);
            if(m_walkSound != nullptr)
            {
                m_walkSound->stop();
                m_walkSound->drop();
                m_walkSound = nullptr;
            }
        }
    }
}

void Player::setMouseButtonPressed(EMOUSE_INPUT_EVENT event)
{
    switch(event)
    {
    case EMIE_LMOUSE_PRESSED_DOWN:
        m_leftButton = true;
        break;
    case EMIE_LMOUSE_LEFT_UP:
        m_leftButton = false;
        break;
    default:
        // We won't use the wheel
        break;
    }
    setAnimationFire(m_leftButton);

}

void Player::setPosition(f32 x, f32 y, f32 z)
{
    camera()->setPosition(core::vector3df(x,y,z));
}

void Player::setRun(bool run)
{
    if(m_run != run)
    {
        m_run = run;
        f32 speed = 1.2;
        if(run == true)
        {
            speed = 3.2;
        }
        core::list<scene::ISceneNodeAnimator*>::ConstIterator anims = camera()->getAnimators().begin();
        scene::ISceneNodeAnimatorCameraFPS *anim=(scene::ISceneNodeAnimatorCameraFPS*)*anims;
        anim->setMoveSpeed(speed);
//        anim->drop();
    }
}

bool Player::animationFire() const
{
    return m_animationFire;
}

void Player::setSoundEngine(irrklang::ISoundEngine *soundEngine)
{
    m_soundEngine = soundEngine;
}

void Player::setKeyPressed(EKEY_CODE key, bool pressed)
{
    switch (key) {
    case KEY_KEY_A :
        m_keyA = pressed;
        break;
    case KEY_KEY_D :
        m_keyD = pressed;
        break;
    case KEY_KEY_S :
        m_keyS = pressed;
        break;
    case KEY_KEY_W :
        m_keyW = pressed;
        break;
    default:
        break;
    }
    setAnimationMove(m_keyA == true || m_keyD == true ||
                     m_keyS == true || m_keyW == true);
}



