#include "std.h"
#include "bbsys.h"
#include "bbinput.h"

void input_link(void (*rtSym)(std::string sym))
{
    rtSym("%KeyDown%key");
    rtSym("%KeyHit%key");
    rtSym("%GetKey");
    rtSym("%WaitKey");
    rtSym("FlushKeys");

    rtSym("%MouseDown%button");
    rtSym("%MouseHit%button");
    rtSym("%GetMouse");
    rtSym("%WaitMouse");
    rtSym("%MouseWait");
    rtSym("%MouseX");
    rtSym("%MouseY");
    rtSym("%MouseZ");
    rtSym("%MouseXSpeed");
    rtSym("%MouseYSpeed");
    rtSym("%MouseZSpeed");
    rtSym("FlushMouse");
    rtSym("MoveMouse%x%y");

    rtSym("%JoyType%port=0");
    rtSym("%JoyDown%button%port=0");
    rtSym("%JoyHit%button%port=0");
    rtSym("%GetJoy%port=0");
    rtSym("%WaitJoy%port=0");
    rtSym("%JoyWait%port=0");
    rtSym("#JoyX%port=0");
    rtSym("#JoyY%port=0");
    rtSym("#JoyZ%port=0");
    rtSym("#JoyU%port=0");
    rtSym("#JoyV%port=0");
    rtSym("#JoyPitch%port=0");
    rtSym("#JoyYaw%port=0");
    rtSym("#JoyRoll%port=0");
    rtSym("%JoyHat%port=0");
    rtSym("%JoyXDir%port=0");
    rtSym("%JoyYDir%port=0");
    rtSym("%JoyZDir%port=0");
    rtSym("%JoyUDir%port=0");
    rtSym("%JoyVDir%port=0");
    rtSym("FlushJoy");

    rtSym("EnableDirectInput%enable");
    rtSym("%DirectInputEnabled");
}
