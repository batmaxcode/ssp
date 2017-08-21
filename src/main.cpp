#include "gamepark.h"

/*
The start of the main function starts like in most other example. We ask the
user for the desired renderer and start it up. This time with the advanced
parameter handling.
*/
int main()
{
    GamePark gamePark;
    return gamePark.run();
}

/*
Now you know how to use terrain in Irrlicht.
**/


//#include <irrlicht.h>
//#include <time.h>

//using namespace irr;
//using namespace core;
//using namespace video;

//dimension2di posMouse;

//class MyShaderCallBack : public IShaderConstantSetCallBack
//{
//public:

//    virtual void OnSetConstants(IMaterialRendererServices* services, s32 userData)
//    {
//        IVideoDriver* driver = services->getVideoDriver();
//        f32 resolution[2] = {driver->getScreenSize().Width,
//                                driver->getScreenSize().Height};
//                        //driver->get
//        // Получаем время
//        f32 tm = clock() / 10000;
//        //s32 texture = 0;
//        f32 array[2] = {posMouse.Width, posMouse.Height};
//#if (IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR == 8)
//        services->setVertexShaderConstant("time", &tm, 1);
//        services->setVertexShaderConstant("resolution", resolution, 2);
//        services->setVertexShaderConstant("mouse", array, 2);
//#elif (IRRLICHT_VERSION_MAJOR == 1 && IRRLICHT_VERSION_MINOR == 9)
//        // Пока не реализовывал
//#endif
//    }

//};


//int main()
//{
//    // Ну, тут и коментрировать нечего ))
//    IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2du(800, 600));
//    IVideoDriver* driver = device->getVideoDriver();
//    // Кошмар! Мы не используем менеджер сцены...
//    // ISceneManager* smgr = device->getSceneManager();

//    // Путь к файлам
//    io::path vert = "../../shaders/test/vert.glsl"; // Вершинный шейдер
//    io::path frag = "../../shaders/test/frag.glsl"; // Фрагментный шейдер

//    // Создание нового шейдерного материала
//    video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
//    s32 newMaterialType = 0;
//    if (gpu)
//    {
//        MyShaderCallBack* mc = new MyShaderCallBack();
//            newMaterialType = gpu->addHighLevelShaderMaterialFromFiles(vert, frag, mc);
//        mc->drop();
//    }

//    SMaterial material;
//        material.MaterialType = (E_MATERIAL_TYPE)newMaterialType;
//        material.Lighting = false;

//    // Устанавливаем текущий материал
//    driver->setMaterial(material);


//    // Создаём квадрат
//    scene::SMeshBuffer mb;
//    mb.Indices.set_used(6);
//        mb.Indices[0] = 0;
//        mb.Indices[1] = 1;
//        mb.Indices[2] = 2;
//        mb.Indices[3] = 0;
//        mb.Indices[4] = 2;
//        mb.Indices[5] = 3;

//    mb.Vertices.set_used (4);
//        mb.Vertices[0].Pos.set (-1.f, -1.f, 1.f);
//        mb.Vertices[0].TCoords.set(0.0f, 0.0f);

//        mb.Vertices[1].Pos.set (-1.f, 1.f, 1.f);
//        mb.Vertices[1].TCoords.set(0.0f, 1.0f);

//        mb.Vertices[2].Pos.set (1.f, 1.f, 1.f);
//        mb.Vertices[2].TCoords.set(1.0f, 1.0f);

//        mb.Vertices[3].Pos.set (1.f, -1.f, 1.f);
//        mb.Vertices[3].TCoords.set(1.0f, 0.0f);

//    // Главный цикл
//    while(device->run())
//        if (device->isWindowActive())
//        {
//            posMouse = device->getCursorControl()->getPosition();
//            driver->beginScene();
//                driver->drawMeshBuffer(&mb);
//            driver->endScene();
//        }

//    device->drop();
//    return 0;
//}















///**Simple postprocessing example, Blur / HDR-bloom postprocessing effect
//By Santiago A. Navascues using the Irrlicht Engine
//*/

///**What is "postprocessing"?
//The post processing is a routine done after the main processing of the scene,
//when the main scene has been already rendered.Normally, we would end here,
//but with postprocessing things work different. The first and main diference
//between the normal rendering and a postprocessed scene is that the main
//rendering isn't done to the back buffer, but to a rendering target texture.
//(RTT for short)

//Then, this texture is used as the input for another rendering, using an
//screenaligned quad that will serve us to re-render the scene. This
//screen aligned quad has a material that mixes, blurs, decolorize...
//In one word, process the input RTT in which our main scene is rendered
//This material uses to be written in a shader file. And gives us as output
//a "postprocessed" scene, if this scene is rendered to an RTT again, the
//postprocessing can be repeated, and the postprocessing routines can then
//be chained.

//To avoid diferences between DirectX and OPEN GL, i will make a simple
//postprocessing system that won't rely on any shaders. But all the Postpro-
//cessing routines out there use the same basic system, that is, render to a
//texture, and use that texture to render a screen aligned quad. The good
//thing is that this can go to platforms which doesn't support shaders,
//but that support irrlicht completely ;)

//WARNING!: this code requires NPOT textures!

//Also, i will make use of some tricks to simplify stuff, but the meat of it
//is there
//*/

///**
//What this example covers:
//-The Creation of a custom Scene Node, the ScreenQuad
//-The usage of the 2D drawing routines to create an effect.
//-The creation of simple effects using the materials
//-Rendering to a texture
//-The Rendering on demand of an ISceneNode
//*/

//#include <iostream>
//#include <irrlicht.h>
//#include "postprocessmotionblur.h"

//#define _WIDTH_ 1024
//#define _HEIGHT_ 768

//using namespace irr;
//using namespace std;


///**Class CScreenQuadSceneNode:
//Our screen aligned quad. When this quad is rendered, it simply covers the
//screen with its texture, and uses its material to render the effect

//Any Scene node out there needs, at least, all the abstract methods of the
//ISceneNode interface implemented in order to be useful.

//These methods are 5, besides the appropriate constructors and destructors:

//The "on register for rendering" method,
//The "render" method,
//The "material count request" return method,
//The "material request" method,
//And the "AABB request" method.
//*/



///**Once we are done setting up the new Scene Node, it is time to start the engine*/

//int main()
//{
//    video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;

//    SIrrlichtCreationParameters prm;

//    prm.DriverType = driverType;
//    prm.Bits = 32;
//    prm.WindowSize = core::dimension2du(_WIDTH_,_HEIGHT_);
//    //prm.Fullscreen = true;

//    IrrlichtDevice* dev = createDeviceEx(prm);

//    if(!dev)
//    {
//        return 0;
//    }

//    scene::ISceneManager* smgr = dev->getSceneManager();
//    video::IVideoDriver* drv = dev->getVideoDriver();

//    if(!drv->queryFeature(video::EVDF_RENDER_TO_TARGET))
//    {
//        cout<<"This driver doesn't support Multitextures!!!."<<endl<<"Multitexturing is required"<<endl;
//        return 0;
//    }
//    if(!drv->queryFeature(video::EVDF_RENDER_TO_TARGET))
//    {
//        cout<<"This driver doesn't support the render to textures!!."<<endl<<
//              "Rendering to textures is required"<<endl;
//        return 0;
//    }
//    if(!drv->queryFeature(video::EVDF_TEXTURE_NPOT))
//    {
//        cout<<"This driver doesn't support Non power of two textures!."<<endl<<
//              "This sample works only with support for Non power of two rendering textures"<<endl;
//        return 0;
//    }

//    drv->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,true);
//    drv->setFog(video::SColor(255,226,177,141),video::EFT_FOG_LINEAR,100,1000,0.01);

///**Important stuff, Rendering textures setup.*/
//    video::ITexture* mainTarget = drv->addRenderTargetTexture(prm.WindowSize,"mainTarget");
//    video::ITexture* rtt0;
//    video::ITexture* temp;

////These colors are needed to modify the colors of the RTT in order for them to mix adequately
////Using a shader, the mix is done within the shader code, but we are using just the
////fixed pipeline this time, so, we need some extra stuff. Normally, postprocessing is not
////this extended.
//    rtt0 = drv->addRenderTargetTexture(prm.WindowSize,"rtt0");
//    temp = drv->addRenderTargetTexture(prm.WindowSize,"temp");//Mantiene temporalmente un resultado.

//    CScreenQuadSceneNode* screenQuad = new CScreenQuadSceneNode(smgr->getRootSceneNode(),smgr,10);
//    screenQuad->getMaterial(0).setTexture(0,mainTarget);
//    screenQuad->getMaterial(0).setTexture(1,rtt0);

//    smgr->addCameraSceneNodeFPS();


//    // SKYBOX===============================================================
//    drv->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
//    irr::scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
//        drv->getTexture("../../media/irrlicht2_up.jpg"),
//        drv->getTexture("../../media/irrlicht2_dn.jpg"),
//        drv->getTexture("../../media/irrlicht2_lf.jpg"),
//        drv->getTexture("../../media/irrlicht2_rt.jpg"),
//        drv->getTexture("../../media/irrlicht2_ft.jpg"),
//        drv->getTexture("../../media/irrlicht2_bk.jpg"));
//    skybox->setVisible(true);
//    drv->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
//    //=======================================================================





//    int lastFPS = -1;

//    while(dev->run())
//    {
//        drv->beginScene();

//        screenQuad->draw(drv, rtt0, temp, _WIDTH_, _HEIGHT_, mainTarget);






//        drv->endScene();

//        int fps = drv->getFPS();
//        if (lastFPS != fps)
//        {
//            core::stringw str = L"Postproduction Example - Irrlicht Engine [";
//            str += drv->getName();
//            str += "] FPS:";
//            str += fps;
//            dev->setWindowCaption(str.c_str());
//            lastFPS = fps;
//        }

//    }

//    return 0;
//}
