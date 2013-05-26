#include "Terrain.h"

Terrain::Terrain(scene::ISceneManager* smgr, video::IVideoDriver* driver)
{
    //setup Terrain
    terrain = smgr->addTerrainSceneNode(
        "Textures/terrain-heightmap3.png",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(-100,-73,-100),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(0.3,0.3,0.3),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        10                   // smoothFactor
    );

    terrain->setMaterialTexture(0, driver->getTexture("Textures/Sand.JPG"));
    terrain->setMaterialTexture(1, driver->getTexture("Textures/caustics.bmp"));
    terrain->setMaterialTexture(2, driver->getTexture("Textures/Grass.JPG"));;
}

Terrain::~Terrain()
{
    terrain->drop();
}

scene::ITerrainSceneNode* Terrain::getTerrainNode(){
    return terrain;
}
