#include "gamepark.h"
#include "myeventreceiver.h"
#include "config/inireader.h"
#include "RealisticWater.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

GamePark::GamePark() :
    m_checkLodCounter(0)
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

int GamePark::initWorld()
{
    initTerrain();
    initWater();
    initForest();
    initRoads();
    initCurb();
    initPlanes();
    initSkybox();
    initLight();
    initTestObj();
    return 0;
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
//    m_player->setPosition(29160,535*2,50440); // озера
//    m_player->setPosition(59160,1035*2,58440); // берег у реки
    m_player->setPosition(59160,1035*2,20440); // берег у залива
}

int GamePark::initWater()
{
    // создаение залива
//    const f32 width = 37120.0f;
//    const f32 height = 75120.0f;
//    RealisticWaterSceneNode* water = new RealisticWaterSceneNode(smgr(), width, height);
//    smgr()->getRootSceneNode()->addChild(water);
//    water->setPosition(core::vector3df(52160,35*2,34840));
//    water->setWaterColor(video::SColorf(0,0.5,0.5));
//    water->setWaveHeight(0.3f);
//    water->setWindForce(10.0f);

    // создание озер
    scene::IAnimatedMesh* mesh = smgr()->addHillPlaneMesh( "myHill",
        core::dimension2d<f32>(200,460),
        core::dimension2d<u32>(60,60), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(60,60));
    scene::ISceneNode* waternode = nullptr;
    waternode = smgr()->addWaterSurfaceSceneNode(mesh->getMesh(0), 6.0f, 300.0f, 100.0f);
    waternode->setPosition(core::vector3df(35860,105*2,45900));
    waternode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    waternode->setMaterialTexture(0, driver()->getTexture("../../media/dirty2.jpg"));
    waternode->setMaterialTexture(1, driver()->getTexture("../../media/water_dirty.jpg"));

    waternode->getMaterial(0).getTextureMatrix(0).setTextureScale(0.5, 1);
    waternode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;
    //waternode->getMaterial(1).getTextureMatrix(1).setTextureScale(length/2, 1);
    //waternode->getMaterial(1).TextureLayer->TextureWrapU = video::ETC_REPEAT;

    waternode->setMaterialType(video::EMT_REFLECTION_2_LAYER);

    mesh->drop();
    //---------------------------------------------

    mesh = smgr()->addHillPlaneMesh( "myHill2",
        core::dimension2d<f32>(400,300),
        core::dimension2d<u32>(43,40), 0, 0,
        core::dimension2d<f32>(0,0),
        core::dimension2d<f32>(60,60));
    waternode = nullptr;
    waternode = smgr()->addWaterSurfaceSceneNode(mesh->getMesh(0), 6.0f, 300.0f, 100.0f);
    waternode->setPosition(core::vector3df(51060,105*2,29800));
    waternode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    waternode->setMaterialTexture(0, driver()->getTexture("../../media/dirty2.jpg"));
    waternode->setMaterialTexture(1, driver()->getTexture("../../media/water_dirty.jpg"));

    waternode->getMaterial(0).getTextureMatrix(0).setTextureScale(1, 1);
    waternode->getMaterial(0).TextureLayer->TextureWrapU = video::ETC_REPEAT;

    waternode->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    m_movableNode = (scene::IAnimatedMeshSceneNode*)waternode;
    mesh->drop();

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

int GamePark::initTestObj()
{
    core::vector3df pos = core::vector3df(9860,205*2,56040);
    scene::IAnimatedMesh* mesh = smgr()->getMesh("../../media/models/croco.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IAnimatedMeshSceneNode* node = smgr()->addAnimatedMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(75.0f,75.0f,75.0f));
        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(pos);
        //node->addShadowVolumeSceneNode();
       // node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
        node->setMaterialTexture( 0, driver()->getTexture("../../media/rock.jpg") );


        node->getMaterial(0).Shininess = 1.0f;
        node->getMaterial(0).SpecularColor.set(255,0,0,0);
        node->getMaterial(0).AmbientColor.set(255,0,0,0);
        node->getMaterial(0).DiffuseColor.set(255,0,0,0);
        node->getMaterial(0).EmissiveColor.set(0,0,0,0);


        node->setMaterialTexture(1, driver()->getTexture("../../media/rock.jpg"));
        node->setMaterialType(video::EMT_DETAIL_MAP);


        mesh->drop();
    }
    return 0;
}

int GamePark::initForest()
{
    core::vector3df pos[m_forestSize];
    pos[0] = core::vector3df(20000,260*2,59360);
    pos[1] = core::vector3df(43630,260*2,49760);
    pos[2] = core::vector3df(15060,260*2,33010);
    pos[3] = core::vector3df(15060,260*2,33010);
    core::vector3df scale = core::vector3df(70.0f,70.0f,70.0f);

    for(int i=0;i<m_forestSize;i++)
    {
        core::stringc postfix = core::stringc(i+1)+".b3d";
        core::stringc postfixLow = core::stringc(i+1)+"_low.b3d";
        scene::IMesh* mesh = smgr()->getMesh(core::stringc("../../media/models/forest_")+
                                             postfix);
        if (!mesh)
        {
            m_device->drop();
            return 1;
        }
        scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
        if (node)
        {
            node->setScale(scale);
            node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
            node->setPosition(pos[i]);
            node->setRotation(core::vector3df(0,180,0));
            node->setMaterialTexture( 0, driver()->getTexture("../../media/tree.jpg") );
            node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        }
//        setCollision(node, m_player);
        m_forest[i] = node;

        mesh = smgr()->getMesh(core::stringc("../../media/models/forest_")+
                               postfixLow);
        if (!mesh)
        {
            m_device->drop();
            return 1;
        }
        node = smgr()->addMeshSceneNode( mesh );
        if (node)
        {
            node->setScale(scale);
            node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
            node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
            node->setPosition(pos[i]);
            node->setRotation(core::vector3df(0,180,0));
            node->setMaterialTexture( 0, driver()->getTexture("../../media/tree_spherical_1_2.png") );

        }
        mesh->drop();
    }


    //-----------------------------------------
//    pos =
//    scale = core::vector3df(70.0f,70.0f,70.0f);
//    mesh = smgr()->getMesh("../../media/models/forest_2.b3d");
//    if (!mesh)
//    {
//        m_device->drop();
//        return 1;
//    }
//    node = smgr()->addMeshSceneNode( mesh );
//    if (node)
//    {
//        node->setScale(scale);
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//        node->setPosition(pos);
//        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialTexture( 0, driver()->getTexture("../../media/tree.jpg") );
//        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
//    }
//    setCollision(node, m_player);
//    m_forest[1] = node;

//    mesh = smgr()->getMesh("../../media/models/forest_2_low.b3d");
//    if (!mesh)
//    {
//        m_device->drop();
//        return 1;
//    }
//    node = smgr()->addMeshSceneNode( mesh );
//    if (node)
//    {
//        node->setScale(scale);
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//        node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
//        node->setPosition(pos);
//        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialTexture( 0, driver()->getTexture("../../media/tree_spherical_1_2.png") );

//    }
//    mesh->drop();
    return 0;
}

int GamePark::initRoads()
{
    scene::IMesh* mesh = smgr()->getMesh("../../media/models/road.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(123.4f,123.4f,123.4f));
        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(9730*2,150*2,26555*2));
        //node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
        node->setMaterialTexture( 0, driver()->getTexture("../../media/asphalt.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200,200);
        //node->setMaterialType(video::EMT_DETAIL_MAP);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

    }
    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initCurb()
{
    scene::IMesh* mesh = smgr()->getMesh("../../media/models/curb.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(123.4f,123.4f,123.4f));
        node->setRotation(core::vector3df(0,180,0));
//        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(9730*2,150*2,26555*2));
        //node->addShadowVolumeSceneNode(0,-1,false,5000.0f);
        node->setMaterialTexture( 0, driver()->getTexture("../../media/curb2.jpg") );
//        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;
        node->getMaterial(0).getTextureMatrix(0).setTextureScale(40,40);
        node->getMaterial(1).getTextureMatrix(0).setTextureScale(40,40);
        node->getMaterial(2).getTextureMatrix(0).setTextureScale(40,40);
        //node->setMaterialType(video::EMT_DETAIL_MAP);
        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

//        node->getMaterial(0).getTextureMatrix(0).setTextureScale(200, 200);

    }
    setCollision(node,m_player);
    mesh->drop();
    return 0;
}

int GamePark::initPlanes()
{
    scene::IMesh* mesh = smgr()->getMesh("../../media/models/main_plane.b3d");
    if (!mesh)
    {
        m_device->drop();
        return 1;
    }
    scene::IMeshSceneNode* node = smgr()->addMeshSceneNode( mesh );
    if (node)
    {
        node->setScale(core::vector3df(45.0f,45.0f,45.0f));
        node->setRotation(core::vector3df(0,90,0));
        if(!shadows)
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
        node->setPosition(core::vector3df(7950*2,150*2,29850*2));
        node->setMaterialTexture( 0, driver()->getTexture("../../media/plita-daleko.png") );
        node->setMaterialTexture( 1, driver()->getTexture("../../media/plita-2.jpg") );
        node->getMaterial(0).TextureLayer[0].AnisotropicFilter = 16;

        node->setMaterialType(video::EMT_DETAIL_MAP);

        node->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);

    }
    setCollision(node,m_player);
    return 0;
}

void GamePark::setCollision(scene::IAnimatedMeshSceneNode *node, Player *player)
{
    scene::ITriangleSelector* selector = smgr()->createOctreeTriangleSelector(node->getMesh(),node,128);
    node->setTriangleSelector(selector);
    scene::ISceneNodeAnimator* anim = smgr()->createCollisionResponseAnimator(
    selector,
    player->camera(),player->ellipsoid(),
    core::vector3df(0,0,0),core::vector3df(0,60,0));
    selector->drop();
    player->camera()->addAnimator(anim);
    anim->drop();
}

void GamePark::setCollision(scene::IMeshSceneNode *node, Player *player)
{
    scene::ITriangleSelector* selector = smgr()->createOctreeTriangleSelector(node->getMesh(),node,128);
    node->setTriangleSelector(selector);
    scene::ISceneNodeAnimator* anim = smgr()->createCollisionResponseAnimator(
    selector,
    player->camera(),player->ellipsoid(),
    core::vector3df(0,0,0),core::vector3df(0,60,0));
    selector->drop();
    player->camera()->addAnimator(anim);
    anim->drop();
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

scene::IAnimatedMeshSceneNode *GamePark::movableNode() const
{
    return m_movableNode;
}

void GamePark::forestLOD(core::vector3df pos)
{
    int frame = 12;

    if(m_checkLodCounter == frame)
    {
        float dist;
        for(int i=0;i<m_forestSize;i++)
        {
            dist = m_forest[i]->getPosition().getDistanceFrom(pos);
            if(dist < 25000 && !m_forest[i]->isVisible()){
                m_forest[i]->setVisible(true);
            }
            else if(dist > 25000 && m_forest[i]->isVisible()){
                m_forest[i]->setVisible(false);
            }
        }
    }
    //-----------------------------------
    if(m_checkLodCounter < frame)
    {
        m_checkLodCounter++;
    }
    else
    {
        m_checkLodCounter = 0;
    }

}


int GamePark::run()
{

    /*
    That's it, draw everything.
    */

//    int lastFPS = -1;

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
//    video::SMaterial material;




    while(m_device->run())
    if (m_device->isWindowActive())
    {
        driver()->beginScene(true, true, 0 );

//        forestLOD(m_player->camera()->getPosition());

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




        if(selectedSceneNode && m_player->animationFire())
        {
            bill->setPosition(intersection);
            m_movableNode = (scene::IAnimatedMeshSceneNode*)selectedSceneNode;
//            log( selectedSceneNode->getName() );
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
//        if (lastFPS != fps)
        if(m_checkLodCounter == 12)
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

//            m_device->setWindowCaption(str.c_str());
//            lastFPS = fps;

            updateEnvironment(str);
        }

    }

    m_device->drop();

    return 0;
}


