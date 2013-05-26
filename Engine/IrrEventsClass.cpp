#include "IrrEventsClass.h"

IrrEvents::IrrEvents()
{
    on_key_esc = NULL;
    key_esc = false;

    on_key_f6 = NULL;
    key_f6 = false;

}

bool IrrEvents::OnEvent(const SEvent& event)
{
    switch(event.EventType)
    {
        //if it is a mouse event
    case EET_MOUSE_INPUT_EVENT:
    {
        switch(event.MouseInput.Event)
        {
        }
    }

    //if it is a keyboard event
    case EET_KEY_INPUT_EVENT:
    {
        //if a key was pressed
        switch(event.KeyInput.Key)
        {
        case KEY_ESCAPE:
        {
            if(on_key_esc != NULL && key_esc == false)
                on_key_esc();
            key_esc = true;
            break;
        }
        case KEY_F6:
        {
            if(on_key_f6 != NULL && key_f6 == false)
                on_key_f6();
            key_f6 = true;
            break;
        }
        }
    }

    }

    cam->HandleEvent(event);

    return true;
}
