#include "myeventreceiver.h"
#include "gamepark.h"


MyEventReceiver::MyEventReceiver(GamePark *gamePark) :
    m_gamePark(gamePark)
{
}

bool MyEventReceiver::OnEvent(const SEvent &event)
{
    scene::IAnimatedMeshSceneNode* animnode = m_gamePark->player()->node();
    io::IReadFile *heightmap = m_gamePark->heightmap;
    IrrlichtDevice* device = m_gamePark->device();
    scene::ITerrainSceneNode* terrain = m_gamePark->terrain;
    video::IVideoDriver* driver = m_gamePark->driver();
    scene::ISceneNode* moveNode = m_gamePark->movableNode();

    int moveDist = 10;
    f32 scaleCoef = 0.2f;


    if (event.EventType == irr::EET_KEY_INPUT_EVENT )
    {
        if(event.KeyInput.Key==KEY_KEY_W || event.KeyInput.Key==KEY_KEY_A ||
           event.KeyInput.Key==KEY_KEY_S || event.KeyInput.Key==KEY_KEY_D )
        {
            m_gamePark->player()->setKeyPressed(event.KeyInput.Key,
                                                event.KeyInput.PressedDown);


        }
        if(event.KeyInput.Key==160)
        {
            m_gamePark->player()->setRun( !event.KeyInput.Shift );
        }



        switch (event.KeyInput.Key)
        {
        case irr::KEY_KEY_Q: // switch wire frame mode
            if(event.KeyInput.PressedDown == false)
            {
                m_gamePark->switchTerrainMaterial(video::EMF_WIREFRAME);
            }
            return true;
        case irr::KEY_KEY_P: // switch wire frame mode
            if(event.KeyInput.PressedDown == false)
            {
                m_gamePark->switchTerrainMaterial(video::EMF_POINTCLOUD);
            }
            return true;
        case irr::KEY_KEY_E: // toggle detail map
            if(event.KeyInput.PressedDown == false)
            {
                m_gamePark->switchTerrainDetailMap();
            }
            return true;
        case irr::KEY_KEY_R: // toggle skies
            if(event.KeyInput.PressedDown == false)
            {
                m_gamePark->switchSkybox();
            }
            return true;
        case irr::KEY_ESCAPE:
            m_gamePark->exit();
            return true;
        case irr::KEY_KEY_K:
            //exit_usl = true;
            animnode->setFrameLoop(0,60);
            animnode->setLoopMode(false);
            return true;
        case irr::KEY_KEY_O: // switch wire frame mode
            //usl_exit = true;
            heightmap = device->getFileSystem()->createAndOpenFile("../../media/park-ter-5.png");
            terrain->loadHeightMap(heightmap,video::SColor( 255, 255, 255, 255 ),3);
            //if(!shadows)
            terrain->setMaterialFlag(video::EMF_LIGHTING, false);

            terrain->setMaterialTexture(0,
                    driver->getTexture("../../media/park-textura-5.png"));
            terrain->setMaterialTexture(1,
                    driver->getTexture("../../media/grass_dirty.jpg"));

            terrain->setMaterialType(video::EMT_DETAIL_MAP);

            terrain->scaleTexture(1.0f, 390.0f);
            return true;
        case irr::KEY_KEY_Y:
            moveNode->setPosition(core::vector3df(moveNode->getPosition().X+moveDist,
                                                  moveNode->getPosition().Y,
                                                  moveNode->getPosition().Z));
            std::cout << moveNode->getPosition().X << " " <<
                         moveNode->getPosition().Y << " " <<
                         moveNode->getPosition().Z << std::endl << std::flush;
            return true;
        case irr::KEY_KEY_H:
            moveNode->setPosition(core::vector3df(moveNode->getPosition().X-moveDist,
                                                  moveNode->getPosition().Y,
                                                  moveNode->getPosition().Z));
            std::cout << moveNode->getPosition().X << " " <<
                         moveNode->getPosition().Y << " " <<
                         moveNode->getPosition().Z << std::endl << std::flush;
            return true;
        case irr::KEY_KEY_G:
            moveNode->setPosition(core::vector3df(moveNode->getPosition().X,
                                                  moveNode->getPosition().Y,
                                                  moveNode->getPosition().Z+moveDist));
            std::cout << moveNode->getPosition().X << " " <<
                         moveNode->getPosition().Y << " " <<
                         moveNode->getPosition().Z << std::endl << std::flush;
            return true;
        case irr::KEY_KEY_J:
            moveNode->setPosition(core::vector3df(moveNode->getPosition().X,
                                                  moveNode->getPosition().Y,
                                                  moveNode->getPosition().Z-moveDist));
            std::cout << moveNode->getPosition().X << " " <<
                         moveNode->getPosition().Y << " " <<
                         moveNode->getPosition().Z << std::endl << std::flush;
            return true;
        case irr::KEY_PLUS:
            moveNode->setScale(core::vector3df(moveNode->getScale().X + scaleCoef,
                                               moveNode->getScale().Y + scaleCoef,
                                               moveNode->getScale().Z + scaleCoef));
            std::cout << moveNode->getScale().X << " " <<
                         moveNode->getScale().Y << " " <<
                         moveNode->getScale().Z << std::endl << std::flush;
            return true;
        case irr::KEY_MINUS:
            moveNode->setScale(core::vector3df(moveNode->getScale().X - scaleCoef,
                                               moveNode->getScale().Y - scaleCoef,
                                               moveNode->getScale().Z - scaleCoef));
            std::cout << moveNode->getScale().X << " " <<
                         moveNode->getScale().Y << " " <<
                         moveNode->getScale().Z << std::endl << std::flush;
            return true;

        default:
            break;
        }
    }

    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        m_gamePark->player()->setMouseButtonPressed(event.MouseInput.Event);
    }

    return false;
}
