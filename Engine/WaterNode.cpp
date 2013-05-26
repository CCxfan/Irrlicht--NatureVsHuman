/*
Copyright (c) 2008 Nils Daumann

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "WaterNode.h"

void EnvClass_TerrainShaderCallback::OnSetConstants(video::IMaterialRendererServices *services, s32 userdata)
{
    video::IVideoDriver* driver = services->getVideoDriver();
    video::SMaterial *mat = (video::SMaterial *)userdata;

    core::matrix4 ViewProj;
    ViewProj = driver->getTransform(video::ETS_PROJECTION);
    ViewProj *= driver->getTransform(video::ETS_VIEW);
    services->setVertexShaderConstant("matViewProj", &ViewProj[0], 16);

    core::matrix4 world;
    world = driver->getTransform(video::ETS_WORLD);
    services->setVertexShaderConstant("matWorld", &world[0], 16);

    f32 time = device->getTimer()->getTime()*0.001f;
    services->setPixelShaderConstant("Time", &time, 1);

    f32 vecDistFogColor[3];
    vecDistFogColor[0] = distfogcolor->r;
    vecDistFogColor[1] = distfogcolor->g;
    vecDistFogColor[2] = distfogcolor->b;
    services->setPixelShaderConstant("vecDistFogColor",vecDistFogColor,3);
    services->setPixelShaderConstant("vecAmbient",vecDistFogColor,3);



    // set view
    core::vector3df vecViewPos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
    services->setVertexShaderConstant("vecViewPos",reinterpret_cast<f32*>(&vecViewPos), 3);

    //pass clipping information
    services->setVertexShaderConstant("ClipFac",clipfactor, 1);

}


void EnvClass_PerPixelLightShaderCallback::OnSetConstants(video::IMaterialRendererServices *services, s32 userdata)
{
    video::IVideoDriver* driver = services->getVideoDriver();
    video::SMaterial *mat = (video::SMaterial *)userdata;

    core::matrix4 ViewProj;
    ViewProj = driver->getTransform(video::ETS_PROJECTION);
    ViewProj *= driver->getTransform(video::ETS_VIEW);
    services->setVertexShaderConstant("matViewProj", &ViewProj[0], 16);

    core::matrix4 world;
    world = driver->getTransform(video::ETS_WORLD);
    services->setVertexShaderConstant("matWorld", &world[0], 16);

		f32 time = device->getTimer()->getTime()*0.001f;
		services->setVertexShaderConstant("Time", &time, 1);
		services->setPixelShaderConstant("Time", &time, 1);

    f32 vecDistFogColor[3];
    vecDistFogColor[0] = distfogcolor->r;
    vecDistFogColor[1] = distfogcolor->g;
    vecDistFogColor[2] = distfogcolor->b;
    services->setPixelShaderConstant("vecDistFogColor",vecDistFogColor,3);

    //pass clipping information
    services->setVertexShaderConstant("ClipFac",clipfactor, 1);

}

void EnvClass_WaterShaderCallback::OnSetConstants(video::IMaterialRendererServices *services, s32 userdata)
{
    video::IVideoDriver* driver = services->getVideoDriver();
    video::SMaterial *mat = (video::SMaterial *)userdata;

    core::matrix4 ViewProj;
    ViewProj = driver->getTransform(video::ETS_PROJECTION);
    ViewProj *= driver->getTransform(video::ETS_VIEW);
    services->setVertexShaderConstant("matViewProj", &ViewProj[0], 16);

    core::matrix4 world;
    world = driver->getTransform(video::ETS_WORLD);
    services->setVertexShaderConstant("matWorld", &world[0], 16);

    f32 time = device->getTimer()->getTime()*0.001f;
    services->setVertexShaderConstant("Time", &time, 1);

    f32 vecDistFogColor[3];
    vecDistFogColor[0] = distfogcolor->r;
    vecDistFogColor[1] = distfogcolor->g;
    vecDistFogColor[2] = distfogcolor->b;
    services->setPixelShaderConstant("vecDistFogColor",vecDistFogColor,3);

    // set the shininess
//    services->setPixelShaderConstant("Shininess",&mat->Shininess, 4);

    // set view
    core::vector3df vecViewPos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
    services->setVertexShaderConstant("vecViewPos",reinterpret_cast<f32*>(&vecViewPos), 3);

}

void EnvClass_SkyShaderCallback::OnSetConstants(video::IMaterialRendererServices *services, s32 userdata)
{
    video::IVideoDriver* driver = services->getVideoDriver();
    video::SMaterial *mat = (video::SMaterial *)userdata;

    core::matrix4 ViewProj;
    ViewProj = driver->getTransform(video::ETS_PROJECTION);
    ViewProj *= driver->getTransform(video::ETS_VIEW);
    services->setVertexShaderConstant("matViewProj", &ViewProj[0], 16);

    core::matrix4 world;
    world = driver->getTransform(video::ETS_WORLD);
    services->setVertexShaderConstant("matWorld", &world[0], 16);

    f32 time = device->getTimer()->getTime()*0.001f;
    //services->setVertexShaderConstant("Time", &time, 1);

    f32 vecDistFogColor[3];
    vecDistFogColor[0] = distfogcolor->r;
    vecDistFogColor[1] = distfogcolor->g;
    vecDistFogColor[2] = distfogcolor->b;
    services->setPixelShaderConstant("vecDistFogColor",vecDistFogColor,3);

    f32 vecSkyColor[3];
    vecSkyColor[0] = skycolor->r;
    vecSkyColor[1] = skycolor->g;
    vecSkyColor[2] = skycolor->b;
    services->setPixelShaderConstant("vecSkyColor",vecSkyColor,3);

}

EnvClass::EnvClass(IrrlichtDevice *device_, s32 rtres)
{
    device = device_;
    smgr = device->getSceneManager();
    driver = smgr->getVideoDriver();
    gpu = driver->getGPUProgrammingServices();

    terraincallback = new EnvClass_TerrainShaderCallback(device,&clipfactor,&tempdistfogcolor,&tempunderwaterfogcolor);
    perpixellightcallback = new EnvClass_PerPixelLightShaderCallback(device,&clipfactor,&tempdistfogcolor);
    watercallback = new EnvClass_WaterShaderCallback(device,&clipfactor,&tempdistfogcolor,&tempunderwaterfogcolor);
    skycallback = new EnvClass_SkyShaderCallback(device,&tempdistfogcolor,&tempunderwaterfogcolor,&tempskycolor);

    reflcam = smgr->addCameraSceneNode();

    reflection = driver->addRenderTargetTexture(core::dimension2d<u32>(rtres,rtres), "RTT1",irr::video::ECF_A8R8G8B8);
    refraction = driver->addRenderTargetTexture(core::dimension2d<u32>(rtres,rtres), "RTT1",irr::video::ECF_A8R8G8B8);

    waterheight = 0;

    waterscenenode = smgr->addMeshSceneNode(smgr->getMesh("Meshs/TrapezoidalGridWeighted3.b3d"));
    waterscenenode->setRotation(core::vector3df(90,0,0));
    waterscenenode->setScale(core::vector3df(160,160,160));

    video::SMaterial *material;
    material = &waterscenenode->getMaterial(0);
    material->setTexture(0,reflection);
    material->setTexture(1,refraction);
    material->setTexture(2,driver->getTexture("Textures/waterbump.png"));
    material->setTexture(3,driver->getTexture("Textures/Shore.tga"));
    material->TextureLayer[0].TextureWrapU = video::ETC_CLAMP;
    material->TextureLayer[0].TextureWrapV = video::ETC_CLAMP;
    material->TextureLayer[1].TextureWrapU = video::ETC_CLAMP;
    material->TextureLayer[1].TextureWrapV = video::ETC_CLAMP;
    material->TextureLayer[2].TextureWrapU = video::ETC_REPEAT;
    material->TextureLayer[2].TextureWrapV = video::ETC_REPEAT;
    material->TextureLayer[3].TextureWrapU = video::ETC_REPEAT;
    material->TextureLayer[3].TextureWrapV = video::ETC_REPEAT;

    material->Wireframe = false;
    material->Lighting = false;
    material->FogEnable = false;
    material->BackfaceCulling = false;
//	setAutomaticCulling(scene::EAC_OFF);

    switch(driver->getDriverType())
    {
    case video::EDT_OPENGL:
    {
        watermatid = gpu->addHighLevelShaderMaterialFromFiles
                     (
                         "Engine/OS_Shaders/OS_Water.vs",
                         "main",
                         video::EVST_VS_2_0,
                         "Engine/OS_Shaders/OS_Water.ps",
                         "main",
                         video::EPST_PS_2_0,
                         watercallback,
                         video::EMT_SOLID,
                         0//(u32)material
                     );

        skymatid = gpu->addHighLevelShaderMaterialFromFiles
                   (
                       "Engine/OS_Shaders/OS_Sky.vs",
                       "main",
                       video::EVST_VS_2_0,
                       "Engine/OS_Shaders/OS_Sky.ps",
                       "main",
                       video::EPST_PS_2_0,
                       skycallback,
                       video::EMT_SOLID,
                       0//(s32)material
                   );

        terrainmatid = gpu->addHighLevelShaderMaterialFromFiles
                       (
                           "Engine/OS_Shaders/OS_Terrain.vs",
                           "main",
                           video::EVST_VS_2_0,
                           "Engine/OS_Shaders/OS_Terrain.ps",
                           "main",
                           video::EPST_PS_2_0,
                           terraincallback,
                           video::EMT_SOLID,
                           0//(s32)material
                       );

        perpixellightmatid = gpu->addHighLevelShaderMaterialFromFiles
                             (
                                 "Engine/OS_Shaders/OS_PerPixelLit.vs",
                                 "main",
                                 video::EVST_VS_2_0,
                                 "Engine/OS_Shaders/OS_PerPixelLit.ps",
                                 "main",
                                 video::EPST_PS_2_0,
                                 perpixellightcallback,
                                 video::EMT_SOLID,
                                 0//(s32)material
                             );

        break;
    }

    case video::EDT_DIRECT3D9:
    {
        watermatid = gpu->addHighLevelShaderMaterialFromFiles
                     (
                         "Engine/OS_Shaders/OS_Water.fx",
                         "mainVS",
                         video::EVST_VS_2_0,
                         "Engine/OS_Shaders/OS_Water.fx",
                         "mainPS",
                         video::EPST_PS_2_0,
                         watercallback,
                         video::EMT_SOLID,
                         0//(s32)material
                     );

        skymatid = gpu->addHighLevelShaderMaterialFromFiles
                   (
                       "Engine/OS_Shaders/OS_Sky.fx",
                       "mainVS",
                       video::EVST_VS_2_0,
                       "Engine/OS_Shaders/OS_Sky.fx",
                       "mainPS",
                       video::EPST_PS_2_0,
                       skycallback,
                       video::EMT_SOLID,
                       0//(s32)material
                   );

        terrainmatid = gpu->addHighLevelShaderMaterialFromFiles
                       (
                           "Engine/OS_Shaders/OS_Terrain.fx",
                           "mainVS",
                           video::EVST_VS_2_0,
                           "Engine/OS_Shaders/OS_Terrain.fx",
                           "mainPS",
                           video::EPST_PS_2_0,
                           terraincallback,
                           video::EMT_SOLID,
                           0//(s32)material
                       );

        perpixellightmatid = gpu->addHighLevelShaderMaterialFromFiles
                             (
                                 "Engine/OS_Shaders/OS_PerPixelLit.fx",
                                 "mainVS",
                                 video::EVST_VS_2_0,
                                 "Engine/OS_Shaders/OS_PerPixelLit.fx",
                                 "mainPS",
                                 video::EPST_PS_2_0,
                                 perpixellightcallback,
                                 video::EMT_SOLID,
                                 0//(s32)material
                             );

        break;
    }

    default:
        break;
    }

    material->MaterialType = (video::E_MATERIAL_TYPE)watermatid;
}

EnvClass::~EnvClass()
{
    delete terraincallback;
    delete perpixellightcallback;
    delete watercallback;
    delete skycallback;

    reflection->drop();
    refraction->drop();
}

void EnvClass::update()
{
    scene::ICameraSceneNode* tempcam = smgr->getActiveCamera();
    waterscenenode->setPosition(core::vector3df(tempcam->getPosition().X,waterheight,tempcam->getPosition().Z));
    waterscenenode->setRotation(core::vector3df(0,tempcam->getRotation().Y,0));
    f32 camheight = tempcam->getPosition().Y-waterscenenode->getPosition().Y;
    f32 Scale = camheight*3;
    Scale = (Scale >= 0)?(Scale):(-Scale);
    Scale += 100;
    waterscenenode->setScale(core::vector3df(Scale,Scale,Scale));

    reflcam->setFarValue(tempcam->getFarValue());
    reflcam->setNearValue(tempcam->getNearValue());

    tempdistfogcolor = distfogcolor;
    tempunderwaterfogcolor = underwaterfogcolor;
    tempskycolor = skycolor;
    f32 daynightcolfac[2];
    f32 time = device->getTimer()->getTime()*0.001f;
    daynightcolfac[0] = cos(time*daynightcyclespeed*2.0)*0.5+0.5;
    daynightcolfac[1] = sin(time*daynightcyclespeed)*0.5+0.5;
    f32 tempcolor[3];
    tempcolor[0] = distfogcolor.r*daynightcolfac[0];
    tempcolor[1] = distfogcolor.g*daynightcolfac[1];
    tempcolor[2] = distfogcolor.b*daynightcolfac[1];
    tempdistfogcolor.set(tempcolor[0],tempcolor[1],tempcolor[2]);
    tempcolor[0] = underwaterfogcolor.r*daynightcolfac[0];
    tempcolor[1] = underwaterfogcolor.g*daynightcolfac[1];
    tempcolor[2] = underwaterfogcolor.b*daynightcolfac[1];
    tempunderwaterfogcolor.set(tempcolor[0],tempcolor[1],tempcolor[2]);
    tempcolor[0] = skycolor.r*daynightcolfac[0];
    tempcolor[1] = skycolor.g*daynightcolfac[1];
    tempcolor[2] = skycolor.b*daynightcolfac[1];
    tempskycolor.set(tempcolor[0],tempcolor[1],tempcolor[2]);

    // make me invisible
    waterscenenode->setVisible(false);

    u32 i;
    for(i = 0; i < listnorefr.size(); i++)
    {
        listnorefr[i]->setVisible(false);
    }

    clipfactor = (camheight >= 0)?(-1.0):(1.0);

    // set render target texture
    driver->setRenderTarget(refraction, true, true, video::SColor(255,0,0,255));

    // draw whole scene into render buffer
    smgr->drawAll();

    for(i = 0; i < listnorefr.size(); i++)
    {
        listnorefr[i]->setVisible(true);
    }

    // set reflection camera as active camera
    smgr->setActiveCamera(reflcam);

    reflcam->setPosition(core::vector3df(	tempcam->getPosition().X,
                                            2*waterscenenode->getPosition().Y-tempcam->getPosition().Y,
                                            tempcam->getPosition().Z));

    for(i = 0; i < listnorefl.size(); i++)
    {
        listnorefl[i]->setVisible(false);
    }

    clipfactor = (camheight >= 0)?(1.0):(-1.0);

    reflcam->setTarget(core::vector3df(tempcam->getTarget().X,-tempcam->getTarget().Y,tempcam->getTarget().Z));

    // set render target texture
    driver->setRenderTarget(reflection, true, true, video::SColor(255,0,0,255));

    // draw whole scene into render buffer
    smgr->drawAll();

    for(i = 0; i < listnorefl.size(); i++)
    {
        listnorefl[i]->setVisible(true);
    }

    clipfactor = 0.0;

    // set back old render target
    driver->setRenderTarget(0);

    // make me visible and set the user controlled camera as active one
    waterscenenode->setVisible(true);

    smgr->setActiveCamera(tempcam);
}

void EnvClass::createSky()
{
    skyscenenode = smgr->addSkyDomeSceneNode(driver->getTexture("Textures/Sun.tga"),32,32,0.5,2);
    skyscenenode->getMaterial(0).MaterialType = (video::E_MATERIAL_TYPE)skymatid;
    skyscenenode->getMaterial(0).TextureLayer[0].TextureWrapU = video::ETC_CLAMP;
    skyscenenode->getMaterial(0).TextureLayer[0].TextureWrapV = video::ETC_CLAMP;
}

void EnvClass::registerTerrain(scene::ISceneNode *node)
{
    video::SMaterial *material = &node->getMaterial(0);
    material->MaterialType = (video::E_MATERIAL_TYPE)terrainmatid;
}

void EnvClass::registerWaterplant(scene::ISceneNode *node)
{
    listnorefl.push_back(node);
    listnorefr.push_back(node);

    video::SMaterial *material = &node->getMaterial(0);
    material->MaterialType = (video::E_MATERIAL_TYPE)waterplantmatid;
    material->BackfaceCulling = false;
    material->ZBuffer = 1;
    material->ZWriteEnable = true;
}

void EnvClass::registerPerPixelLitObject(scene::ISceneNode *node)
{
    listnorefl.push_back(node);
    listnorefr.push_back(node);

    video::SMaterial *material = &node->getMaterial(0);
    material->MaterialType = (video::E_MATERIAL_TYPE)perpixellightmatid;
    material->BackfaceCulling = false;
    material->ZBuffer = 1;
    material->ZWriteEnable = true;
}

scene::ISceneNode *EnvClass::getWaterNode()
{
    return waterscenenode;
}

scene::ISceneNode *EnvClass::getSkyNode()
{
    return skyscenenode;
}

void EnvClass::setDistFogColor(f32 r, f32 g, f32 b)
{
    distfogcolor.set(r,g,b);
    tempdistfogcolor = distfogcolor;
}

void EnvClass::setUnderwaterFogColor(f32 r, f32 g, f32 b)
{
    underwaterfogcolor.set(r,g,b);
    tempunderwaterfogcolor = underwaterfogcolor;
}

void EnvClass::setSkyColor(f32 r, f32 g, f32 b)
{
    skycolor.set(r,g,b);
    tempskycolor = skycolor;
}

void EnvClass::setDayNightChange(f32 speed)
{
    daynightcyclespeed = speed;
}
