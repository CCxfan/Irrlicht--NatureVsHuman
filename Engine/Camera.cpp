#include "Camera.h"

Camera::Camera(scene::ISceneManager* smgr_p)
{
    //add a camera to the scene
    viewPos = vector2df(0,0);
    rotation = 0;
    cam = smgr_p->addCameraSceneNode(0 ,core::vector3df(-10, 10, 0), core::vector3df(0, 0, 0));
    cam->setFarValue(50000.0f);
    cam->setNearValue(0.01f);
    smgr=smgr_p;
//    Update();
    key_forward_down = false;
    key_backward_down = false;
    key_left_down = false;
    key_right_down = false;
    mouse_middle_down = false;
    zoom=1;
    zoomTarget=1;
}

Camera::~Camera()
{
    cam->drop();
}

void Camera::HandleEvent(const SEvent& event){
    switch(event.EventType)
    {
        //if it is a mouse event
    case EET_MOUSE_INPUT_EVENT:
    {
        switch(event.MouseInput.Event)
        {
            case EMIE_RMOUSE_PRESSED_DOWN:{mouse_middle_down = true; oldX = event.MouseInput.X; break;}
            case EMIE_RMOUSE_LEFT_UP:{mouse_middle_down = false; break;}
            case EMIE_MOUSE_MOVED:{if (mouse_middle_down){Rotate(((float)event.MouseInput.X - (float)oldX)/50.0f);  oldX = event.MouseInput.X; }}
            case EMIE_MOUSE_WHEEL:{Zoom(-event.MouseInput.Wheel / 9) ; break;}
        }


    }

    //if it is a keyboard event
    case EET_KEY_INPUT_EVENT:
    {
        //if a key was pressed
        switch(event.KeyInput.Key)
        {
        case KEY_KEY_W:{key_forward_down = event.KeyInput.PressedDown; break; }
        case KEY_KEY_S:{key_backward_down = event.KeyInput.PressedDown; break; }
        case KEY_KEY_A:{key_left_down = event.KeyInput.PressedDown; break; }
        case KEY_KEY_D:{key_right_down = event.KeyInput.PressedDown; break; }

        default:
            break;
        }
    }

    default:
        break;
    }

    return;
}

void Camera::Move_forward()
{
    viewPosTarget.X += speed * sin(rotation);
    viewPosTarget.Y += speed * cos(rotation);
}

void Camera::Move_backward()
{
    viewPosTarget.X -= speed * sin(rotation);
    viewPosTarget.Y -= speed * cos(rotation);
}
void Camera::Move_left()

{
    viewPosTarget.X -= speed * cos(rotation);
    viewPosTarget.Y += speed * sin(rotation);
}

void Camera::Move_right()
{
    viewPosTarget.X += speed * cos(rotation);
    viewPosTarget.Y -= speed * sin(rotation);
}

void Camera::Zoom(float value){
    zoomTarget+=value;
    if (zoomTarget>1) {zoomTarget=1;}
    if (zoomTarget<0) {zoomTarget=0;}
}

void Camera::Rotate(float angle){
    rotationTarget += angle;
}

void Camera::SetActive(){
    smgr->setActiveCamera(cam);
}

void Camera::Update(scene::ITerrainSceneNode* terrain){
    zoom += (zoomTarget-zoom)/10;
    rotation += (rotationTarget-rotation)/10;
    viewPos.X += (viewPosTarget.X-viewPos.X)/10;
    viewPos.Y += (viewPosTarget.Y-viewPos.Y)/10;


    if (key_forward_down){Move_forward();}
    if (key_backward_down){Move_backward();}
    if (key_left_down){Move_left();}
    if (key_right_down){Move_right();}

    float terrainHeight = terrain->getHeight(viewPos.X,viewPos.Y);
    if (terrainHeight<0) { terrainHeight = 0;}

    float xf = (viewPos.X-sin(rotation)*(20*zoom+20));
    float yf =(viewPos.Y-cos(rotation)*(20*zoom+20));
    float zf =59*zoom+1;

    if (zf<terrain->getHeight(xf,yf)+1) { zf = terrain->getHeight(xf,yf)+1;}

    cam->setTarget(vector3df(viewPos.X, terrainHeight * (1-zoom), viewPos.Y));
    cam->setPosition(vector3df(xf,zf,yf));
}

void Camera::SetSpeed(float speed_p){
    speed = speed_p;
}
//Camera::Zoom(float value);
//Camera::Rotate(float angle);
