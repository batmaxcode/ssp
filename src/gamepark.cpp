#include "gamepark.h"
#include "myeventreceiver.h"
#include "config/inireader.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

GamePark::GamePark()
{
    m_config.load("../../config/config.ini");

    initDriver();
    /*
     * Для начала добавим базовые элементы на сцену: окружение пользователя с текстом подсказок,
     * мир, игрока (камеру от первого лица)
    */
    initEnvironment();
    initPlayer();
    initWorld();
    initReceiver();
}

GamePark::~GamePark()
{
    delete receiver;
    delete m_player;
}

void GamePark::exit()
{
    usl_exit = true;
}

int GamePark::initDriver()
{
    // создаем device c настройками взятыми из файла конифгурации,
    // при необходимости можно добавить больше параметров, проверьте
    // irr::SIrrlichtCreationParameters
    irr::SIrrlichtCreationParameters params = m_config.params();
    params.DriverType = irr::video::EDT_OPENGL;
    m_device = createDeviceEx(params);

    if (m_device == 0)
    {
        // не удалось создать device
        return 1;
    }

    // custom
    smgr()->setShadowColor(irr::video::SColor(150,0,0,0));		//shadow
    smgr()->setAmbientLight(video::SColorf(0.45,0.45,0.45,0.7)); // shadow color
    driver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
    m_device->getCursorControl()->setVisible(false);


    return 0;
}

void GamePark::initEnvironment()
{
    int y = m_config.params().WindowSize.Height;
    // устанавливаем шрифт
    env()->getSkin()->setFont(env()->getFont("../../media/fontlucida.png"));
    // добавляем вспомогательный текст
    m_controlText = env()->addStaticText(L"Use W,A,S,D to move\n"
                                         "Press 'Q' to change wireframe mode\n"
                                         "Press 'E' to toggle detail map\n"
                                         "Press 'R' to toggle skybox/skydome",
                                         core::rect<s32>(10,y-135,250,y-60),
                                         true, true, 0, -1, true);

    m_fpsText = env()->addStaticText(L"",
                                     core::rect<s32>(10,y-55,250,y-20),
                                     true, true, 0, -1, true);
}

void GamePark::initPlayer()
{
    m_player = new Player(device());
    smgr()->setActiveCamera(m_player->camera());

    m_player->setPosition(9160,535*2,58440);
}

int GamePark::initWorld()
{
    initTerrain();
    initSkybox();
    initLight();
    return 0;
}

int GamePark::initTerrain()
{
    // добавление ландшафта
    terrain = smgr()->addTerrainSceneNode(
                    "../../media/park-ter-5.png",
                    0,					// parent node
                    -1,					// node id
                    core::vector3df(0.f, 0.f, 0.f),		// position
                    core::vector3df(0.f, 0.f, 0.f),		// rotation
                    core::vector3df(60.0f, 3.0f, 60.0f),	// scale
                    video::SColor ( 255, 255, 255, 255 ),	// vertexColor
                    6,					// maxLOD
                    scene::ETPS_17,				// patchSize
                    3					// smoothFactor
                    );
    terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0,
             driver()->getTexture("../../media/park-textura-5.png"));
    terrain->setMaterialTexture(1,
             driver()->getTexture("../../media/grass_dirty.jpg"));
    terrain->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
    terrain->scaleTexture(1.0f, 390.0f);

    if(m_config.freeFly() == false)
    {
        // создаем trangle selector для ландшафта
        scene::ITriangleSelector* selector
            = smgr()->createTerrainTriangleSelector(terrain, 0);
        terrain->setTriangleSelector(selector);

        // создаем аниматор столкновений с селектором и прикрепляем его к игроку
        scene::ISceneNodeAnimator* anim = smgr()->createCollisionResponseAnimator(
            selector, m_player->camera(), m_player->ellipsoid(),
            core::vector3df(0,-10,0),
            core::vector3df(0,90,0));
        selector->drop();
        m_player->camera()->addAnimator(anim);
        anim->drop();
    }

    /* Если вам нужен доступ к данным ландшафта, вы также можете сделать это
     *  напрямую с помощью следующего фрагмента кода.
    */
    scene::CDynamicMeshBuffer* buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
    terrain->getMeshBufferForLOD(*buffer, 0);
    //video::S3DVertex2TCoords* data = (video::S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
    // Работайте с данными или получите IndexBuffer с аналогичным вызовом.
    buffer->drop(); // При завершении снова сбрасываем буфер

    return 0;
}

int GamePark::initSkybox()
{
    /*
     * Чтобы пользователь мог переключаться между обычным и каркасным режимами,
     * мы создаем экземпляр приемника событий сверху и позволяем Irrlicht знать
     * об этом. Кроме того, мы добавляем skybox, который мы уже использовали
     * во многих примерах Irrlicht, и skydome, который показан взаимоисключающим
     *  с skybox, нажав «S».
    */

    // создание skybox и skydome
    driver()->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    skybox=smgr()->addSkyBoxSceneNode(
        driver()->getTexture("../../media/irrlicht2_up.jpg"),
        driver()->getTexture("../../media/irrlicht2_dn.jpg"),
        driver()->getTexture("../../media/irrlicht2_lf.jpg"),
        driver()->getTexture("../../media/irrlicht2_rt.jpg"),
        driver()->getTexture("../../media/irrlicht2_ft.jpg"),
        driver()->getTexture("../../media/irrlicht2_bk.jpg"));
    skydome=smgr()->addSkyDomeSceneNode(driver()->getTexture("../../media/skydome.jpg"),
                                        16,8,0.95f,2.0f);
    skybox->setVisible(true);
    skydome->setVisible(false);

    driver()->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    return 0;
}

int GamePark::initLight()
{
    // Добавляем свет, чтобы невыбранные ноды не были полностью черными.
    scene::ILightSceneNode * light = smgr()->addLightSceneNode(0, core::vector3df(10700*2,2585*2,32600*2),
        video::SColorf(0.8f,0.8f,0.8f,1.0f), 20000.0f);
    light->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    light->setID(ID_IsNotPickable);
    return 0;
}

int GamePark::initReceiver()
{
    // создаем event receiver
    receiver = new MyEventReceiver(this);
    m_device->setEventReceiver(receiver);
    return 0;
}

void GamePark::switchTerrainMaterial(video::E_MATERIAL_FLAG material)
{
    switch (material) {
        case video::EMF_WIREFRAME:
            terrain->setMaterialFlag(video::EMF_WIREFRAME, !terrain->getMaterial(0).Wireframe);
            terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
        break;
        case video::EMF_POINTCLOUD:
            terrain->setMaterialFlag(video::EMF_POINTCLOUD, !terrain->getMaterial(0).PointCloud);
            terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
        break;
        default:
        break;
    }
}

void GamePark::switchTerrainDetailMap()
{
    video::E_MATERIAL_TYPE materialType = video::EMT_SOLID;
    if(terrain->getMaterial(0).MaterialType == video::EMT_SOLID)
    {
        materialType = video::EMT_DETAIL_MAP;
    }
    terrain->getMaterial(0).MaterialType = materialType;
}

void GamePark::switchSkybox()
{
    skybox->setVisible(!skybox->isVisible());
    skydome->setVisible(!skydome->isVisible());
}

void GamePark::updateEnvironment(const core::stringw& str)
{
    m_fpsText->setText(str.c_str());
}

Player *GamePark::player() const
{
    return m_player;
}


int GamePark::run()
{






    /*
    That's it, draw everything.
    */

    int lastFPS = -1;

    scene::IBillboardSceneNode * bill;
    // Добавляем билборд, который будет подсвечивать место
    // пересечения луча и объекта в который он уперся
    bill = smgr()->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver()->getTexture("../../media/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d< f32 >(20.0f, 20.0f));
    // дадим билборду ID для объектов которые не реагируют на столкновения.
    bill->setID(ID_IsNotPickable);
    scene::ISceneCollisionManager*  collMan;
    video::SMaterial material;




    while(m_device->run())
    if (m_device->isWindowActive())
    {
        driver()->beginScene(true, true, 0 );

        smgr()->drawAll();
        env()->drawAll();




        collMan = smgr()->getSceneCollisionManager();

        core::line3d<f32> ray;
        ray.start = m_player->camera()->getPosition();
        ray.end = ray.start + (m_player->camera()->getTarget() - ray.start).normalize() * 100000.0f;

        // переменная под хранение точки пересещения
        core::vector3df intersection;
        // переменная под хранение треугольника с которым пересекся луч
        core::triangle3df hitTriangle;

        scene::ISceneNode * selectedSceneNode =
        collMan->getSceneNodeAndCollisionPointFromRay(
        ray,
        intersection, // точка столкновения
        hitTriangle, // полигон(треугольник) в котором
        // точка столкновения
        IDFlag_IsPickable, // определять столкновения только для
        //нод с идентификатором IDFlag_IsPickable
        0); // проверять относительно всей
        // сцены (оставляем значение по умолчанию)

        // Если луч столкнулся с чем нибудь,
        // перемещаем указку(билборд) в точку столкновения
        // и рисуем треугольник в котором она находится




        if(selectedSceneNode && isFire)
        {
            bill->setPosition(intersection);

            log( selectedSceneNode->getName() );
            //usl_slow_exit = false;

            // мы должны сбросить трансформации перед отрисовкой.
            //driver->setTransform(video::ETS_WORLD, core::matrix4());
            //driver->setMaterial(material);
            //driver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));
        }

        // ---------




        if(usl_exit)break;

        if(m_player->node()->getFrameNr() > 31 && m_player->node()->getFrameNr() < 35) m_player->fire()->setVisible(true);
        if(m_player->node()->getFrameNr() > 35 || m_player->node()->getFrameNr() < 30) m_player->fire()->setVisible(false);


        driver()->endScene();

        // display frames per second in window title
        int fps = driver()->getFPS();
        int count = driver()->getPrimitiveCountDrawn();
        if (lastFPS != fps)
        {
            core::stringw str = L"Driver [";
            str += driver()->getName();
            str += "] FPS:";
            str += fps;
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
            str += " Height: ";
            str += terrain->getHeight(m_player->camera()->getAbsolutePosition().X,
                    m_player->camera()->getAbsolutePosition().Z);
            str += " Triangle: ";
            str += count;

            m_device->setWindowCaption(str.c_str());
            lastFPS = fps;

            updateEnvironment(str);
        }

    }

    m_device->drop();

    return 0;
}


