#ifndef CAMERA_H
#define CAMERA_H

#include <irrlicht.h>
#include <vector>
#include <iostream>
#include <irrlicht.h>
#include <math.h>
#include <stddef.h>

using namespace irr;
using namespace core;

class Camera
{
    public:
        Camera(scene::ISceneManager* smgr_p);
        virtual ~Camera();
        void SetSpeed(float speed_p);
        void HandleEvent(const SEvent& event);
        void Move_forward();
        void Move_backward();
        void Move_left();
        void Move_right();
        void Zoom(float value);
        void Rotate(float angle);
        void SetActive();
        void Update(scene::ITerrainSceneNode* terrain);
    protected:
    private:
        scene::ICameraSceneNode *cam;
        scene::ISceneNode *cam_node;
        float speed;
        scene::ISceneManager* smgr;
        vector2df viewPosTarget;
        vector2df viewPos;
        float zoom;
        float zoomTarget;
        float rotation;
        float rotationTarget;
        bool key_forward_down;
        bool key_backward_down;
        bool key_left_down;
        bool key_right_down;
        bool mouse_middle_down;
        int oldX, oldY, oldWheel;
};

#endif
