#include <irrlicht.h>
#include "Engine\IrrEventsClass.h"
#include "Engine\DebugDisplayClass.h"
#include "Engine\WaterNode.h"
#include "Engine\Camera.h"
#include "Engine\Terrain.h"

using namespace irr;

IrrlichtDevice *device;
DebugDisplayClass *debugdisplay;
EnvClass *environment;
Camera* cam;

void Quit()
{
    device->closeDevice();
}

void Screenshot()
{
    debugdisplay->takeScreenshot();
}

void Move_cam_forward(){
    cam->Move_forward();
}

void Move_cam_left(){
    cam->Move_left();
}

void Move_cam_backward(){
    cam->Move_backward();
}

void Move_cam_right(){
    cam->Move_right();
}


int main()
{
    IrrEvents EventReceiver;
    EventReceiver.on_key_esc = Quit;
    EventReceiver.on_key_f6 = Screenshot;

    //initialize Irrlicht
    SIrrlichtCreationParameters initparas;
    initparas.AntiAlias = 32;
    initparas.DriverType = video::EDT_DIRECT3D9;
    initparas.EventReceiver = &EventReceiver;
    initparas.Fullscreen = true;
    initparas.Bits = 32;
    initparas.Stencilbuffer = true;
    initparas.Vsync = false;
    initparas.WindowSize = core::dimension2d< s32 >(1920,1080);
    initparas.HighPrecisionFPU = true;
    initparas.WindowId = 0;

    device = createDeviceEx(initparas);
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    device->setWindowCaption(L"Nature Vs Human");


    debugdisplay = new DebugDisplayClass(device);
    //srand(device->getTimer()->getTime());

    //add a camera to the scene
    /*scene::ICameraSceneNode *fpscam = smgr->addCameraSceneNodeFPS(0,100,0.1);
    fpscam->setFarValue(50000.0f);
    fpscam->setNearValue(0.01f);*/
    cam = new Camera(smgr);
    cam->SetSpeed(0.8f);

    EventReceiver.cam = cam;
    device->getCursorControl()->setVisible(false);
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    Terrain* terrain = new Terrain(smgr, driver);


    //create the watersurface
    environment = new EnvClass(device,512);
    environment->setDistFogColor(0.85,0.95,1.0);
    environment->setSkyColor(0.4,0.6,1.0);
    environment->setDayNightChange(0.3);

    environment->createSky();
    environment->registerTerrain(terrain->getTerrainNode());


    cam->SetActive();


//the main loop
    while(device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(255,150,180,255));

            cam->Update(terrain->getTerrainNode());
            environment->update();

			smgr->drawAll();
            guienv->drawAll();
            driver->endScene();

            debugdisplay->updateDebugDisplay();
        }
    }

    delete debugdisplay;

    //drop the irrlicht device
    device->drop();

    delete environment;

    return 0;

}


