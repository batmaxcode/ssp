#ifndef POSTPROCESSMOTIONBLUR_H
#define POSTPROCESSMOTIONBLUR_H

#include "irrlicht.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class CScreenQuadSceneNode : public scene::ISceneNode{
        scene::ISceneManager* smgr;
        core::aabbox3df aabb;                   //An axis aligned bounding box. Actually not needed.
        video::SMaterial material;              //The material used to render the Scene Node
        video::S3DVertex2TCoords vertices[4];   //The vertices of the Scene Node.
                                                //Normally we wouldn't need more
                                                //than one set of UV coordinates.
                                                //But if we are to use the builtin materials, this is necesary

        video::SColor colors1[4];

        video::SColor colors2[4];
public:
        CScreenQuadSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
        :ISceneNode(parent,mgr,id),
        smgr(mgr)
        {
            colors1[0] = video::SColor(255,224,224,224);
            colors1[1] = video::SColor(255,224,224,224);
            colors1[2] = video::SColor(255,224,224,224);
            colors1[3] = video::SColor(255,224,224,224);

            colors2[0] = video::SColor(255,32,32,32);
            colors2[1] = video::SColor(255,32,32,32);
            colors2[2] = video::SColor(255,32,32,32);
            colors2[3] = video::SColor(255,32,32,32);


            f32 shiftX,shiftY;
            core::dimension2d<u32> currentResolution;

/**Here we initialize the vertices of the screen Aligned quad*/

            currentResolution = mgr->getVideoDriver()->getScreenSize();

            aabb.reset(0,0,0);

            shiftX = 0.5/currentResolution.Width;   //This small shift is necesary to compensate the texture sampling bias
            shiftY = 0.5/currentResolution.Height;  //It avoids that our effect becomes too blurry.

            vertices[0] = video::S3DVertex2TCoords(
                        -1.0f,-1.0f,0.0f,
                        0.0f,0.0f,-1.0f,
                        video::SColor(255,255,255,255),
                        shiftX,1+shiftY,
                        shiftX,1+shiftY);

            vertices[1] = video::S3DVertex2TCoords(
                        1.0f,-1.0,0.0f,
                        0.0f,0.0f,-1.0f,
                        video::SColor(255,255,255,255),
                        1.0f+shiftX,1+shiftY,
                        1.0f+shiftX,1+shiftY);

            vertices[2] = video::S3DVertex2TCoords(
                        -1.0f,1.0,0.0f,
                        0.0f,0.0f,-1.0f,
                        video::SColor(255,255,255,255),
                        shiftX,shiftY,
                        shiftX,shiftY);

            vertices[3] = video::S3DVertex2TCoords(
                        1.0f,1.0f,0.0f,
                        0.0f,0.0f,-1.0f,
                        video::SColor(255,255,255,255),
                        1.0f+shiftX,shiftY,
                        1.0f+shiftX,shiftY);

/**Now we proceed to initialize the appropriate settings for the material we are going to use
We can alter these later, but for the time being, initializing then here will do no harm*/

            material.Lighting = false;                          //No need for lighting.
            material.MaterialType = video::EMT_LIGHTMAP_ADD;    //This will add both first and second textures :)
            material.BackfaceCulling=false;                     //not needed, but simplifies things
            setAutomaticCulling(scene::EAC_OFF);                //We don't need this scene
                                                                //node to be culled because we render it in screen space.
        }

        ~CScreenQuadSceneNode()
        {
        }

        const core::aabbox3df& getBoundingBox() const
        {
            return aabb;
        }

        void OnRegisterSceneNode()
        {
            //This method is empty because it is best for us to render this scene node manually.
            //So, it is never really rendered on its own, if we don't tell it to do so.
        }

        void render()
        {
            video::IVideoDriver* drv = getSceneManager()->getVideoDriver();
             u16 indices[] = {0,1,2,3,1,2};
             //A triangle list

            drv->setMaterial(material);

            drv->setTransform(video::ETS_PROJECTION, core::IdentityMatrix);
            drv->setTransform(video::ETS_VIEW, core::IdentityMatrix);
            drv->setTransform(video::ETS_WORLD, core::IdentityMatrix);

            drv->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);

        }

        u32 getMaterialCount()
        {
            return 1;   //There is only one material
        }

        video::SMaterial& getMaterial(irr::u32 /*i*/)
        {
            return material;//We always return the same material, so there is no need for more.
        }

        void draw(irr::video::IVideoDriver* drv, irr::video::ITexture* rtt0,
                  irr::video::ITexture* temp, int width, int  height,
                  irr::video::ITexture* mainTarget)
        {
            drv->setRenderTarget(rtt0,true,true);
                drv->draw2DImage(temp,core::rect<s32>(0,0,width,height),core::rect<s32>(0,0,width,height),
                0,colors1);//Scale the colors of the previous render
            drv->setRenderTarget(mainTarget,true,true,video::SColor(255,128,160,160));
                smgr->drawAll();//Draw the main scene
            drv->setRenderTarget(temp,true,true);
                drv->draw2DImage(mainTarget,core::rect<s32>(0,0,width,height),core::rect<s32>(0,0,width,height),
                0,colors2);//Scale the colors of the main Scene
            drv->setRenderTarget(mainTarget,true,true);
                drv->draw2DImage(temp,core::rect<s32>(0,0,width,height),core::rect<s32>(0,0,width,height));
                //Return TEMP to the mainTarget
            drv->setRenderTarget(temp,true,true);
                render();//Draw the screenquad into temp
            drv->setRenderTarget(video::ERT_FRAME_BUFFER,true,true);
                drv->draw2DImage(temp,core::position2di(0,0));//Draw the resulting image
        }

};
#endif // POSTPROCESSMOTIONBLUR_H
