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

#ifndef _ENVNODE_H_
#define _ENVNODE_H_

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace irr;

class EnvClass_TerrainShaderCallback : public video::IShaderConstantSetCallBack
{
public:
    EnvClass_TerrainShaderCallback(IrrlichtDevice *device_, f32 *clipfactor_,
                                   video::SColorf *distfogcolor_, video::SColorf *underwaterfogcolor_):
        device(device_), clipfactor(clipfactor_), distfogcolor(distfogcolor_),
        underwaterfogcolor(underwaterfogcolor_) {}

    void OnSetConstants(video::IMaterialRendererServices *services, s32 userdata);

private:
    IrrlichtDevice *device;
    f32 *clipfactor;
    video::SColorf *distfogcolor;
    video::SColorf *underwaterfogcolor;
};

class EnvClass_PerPixelLightShaderCallback : public video::IShaderConstantSetCallBack
{
public:
    EnvClass_PerPixelLightShaderCallback(IrrlichtDevice *device_, f32 *clipfactor_,
                                         video::SColorf *distfogcolor_):
        device(device_), clipfactor(clipfactor_), distfogcolor(distfogcolor_) {}

    void OnSetConstants(video::IMaterialRendererServices *services, s32 userdata);

private:
    IrrlichtDevice *device;
    f32 *clipfactor;
    video::SColorf *distfogcolor;
};

class EnvClass_WaterShaderCallback : public video::IShaderConstantSetCallBack
{
public:
    EnvClass_WaterShaderCallback(IrrlichtDevice *device_, f32 *clipfactor_,
                                 video::SColorf *distfogcolor_, video::SColorf *underwaterfogcolor_):
        device(device_), clipfactor(clipfactor_), distfogcolor(distfogcolor_),
        underwaterfogcolor(underwaterfogcolor_) {}

    void OnSetConstants(video::IMaterialRendererServices *services, s32 userdata);

private:
    IrrlichtDevice *device;
    f32 *clipfactor;
    video::SColorf *distfogcolor;
    video::SColorf *underwaterfogcolor;
};

class EnvClass_SkyShaderCallback : public video::IShaderConstantSetCallBack
{
public:
    EnvClass_SkyShaderCallback(IrrlichtDevice *device_, video::SColorf *distfogcolor_,
                               video::SColorf *underwaterfogcolor_, video::SColorf *skycolor_):
        device(device_), distfogcolor(distfogcolor_), underwaterfogcolor(underwaterfogcolor_),
        skycolor(skycolor_) {}

    void OnSetConstants(video::IMaterialRendererServices *services, s32 userdata);

private:
    IrrlichtDevice *device;
    video::SColorf *distfogcolor;
    video::SColorf *underwaterfogcolor;
    video::SColorf *skycolor;
};

/**
 * \brief Custom scene node for a water surface
 */
class EnvClass
{
public:

    /**
    * \brief Constructor
    */
    EnvClass(IrrlichtDevice *device_, s32 rtres = 256);

    /**
    * \brief Destructor
    */
    ~EnvClass();

    void update();

    void createSky();
    void registerTerrain(scene::ISceneNode *node);
    void registerWaterplant(scene::ISceneNode *node);
    void registerPerPixelLitObject(scene::ISceneNode *node);

    scene::ISceneNode *getWaterNode();
    scene::ISceneNode *getSkyNode();

    void setDistFogColor(f32 r, f32 g, f32 b);
    void setUnderwaterFogColor(f32 r, f32 g, f32 b);
    void setSkyColor(f32 r, f32 g, f32 b);

    void setDayNightChange(f32 speed);


private:
    video::SColorf distfogcolor;
    video::SColorf underwaterfogcolor;
    video::SColorf skycolor;

    video::SColorf tempdistfogcolor;
    video::SColorf tempunderwaterfogcolor;
    video::SColorf tempskycolor;

    scene::ISceneNode *waterscenenode;
    scene::ISceneNode *skyscenenode;

    IrrlichtDevice *device;
    video::IVideoDriver *driver;
    scene::ISceneManager *smgr;
    video::IGPUProgrammingServices *gpu;

    s32 watermatid;
    s32 skymatid;
    s32 terrainmatid;
    s32 waterplantmatid;
    s32 perpixellightmatid;

    f32 clipfactor;
    f32 waterheight;
    f32 daynightcyclespeed;

    EnvClass_TerrainShaderCallback *terraincallback;
    EnvClass_PerPixelLightShaderCallback *perpixellightcallback;
    EnvClass_WaterShaderCallback *watercallback;
    EnvClass_SkyShaderCallback *skycallback;

    std::vector<scene::ISceneNode*> listnorefl;
    std::vector<scene::ISceneNode*> listnorefr;

    video::ITexture *reflection;
    video::ITexture *refraction;
    scene::ICameraSceneNode* reflcam;
};
#endif
