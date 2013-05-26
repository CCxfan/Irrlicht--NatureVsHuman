#ifndef TERRAIN_H
#define TERRAIN_H

#include <irrlicht.h>

using namespace irr;
class Terrain
{
    public:
        Terrain(scene::ISceneManager* smgr, video::IVideoDriver* driver);
        virtual ~Terrain();
        scene::ITerrainSceneNode* getTerrainNode();
    protected:
    private:
         scene::ITerrainSceneNode* terrain;
};

#endif // TERRAIN_H
