#include "std.h"
#include "bbgraphics.h"

void graphics_link(void (*rtSym)(std::string sym))
{
    //gfx driver info
    rtSym("%CountGfxDrivers");
    rtSym("$GfxDriverName%driver");
    rtSym("SetGfxDriver%driver");

    //gfx mode info
    rtSym("%CountGfxModes");
    rtSym("%GfxModeExists%width%height%depth");

    rtSym("%GfxModeWidth%mode");
    rtSym("%GfxModeHeight%mode");
    rtSym("%GfxModeDepth%mode");
    rtSym("%AvailVidMem");
    rtSym("%TotalVidMem");

    rtSym("%GfxDriver3D%driver");
    rtSym("%CountGfxModes3D");
    rtSym("%GfxMode3DExists%width%height%depth");
    rtSym("%GfxMode3D%mode");
    rtSym("%Windowed3D");

    //display mode
    rtSym("Graphics%width%height%depth=0%mode=0");
    rtSym("Graphics3D%width%height%depth=0%mode=0");
    rtSym("EndGraphics");
    rtSym("%GraphicsLost");

    rtSym("SetGamma%src_red%src_green%src_blue#dest_red#dest_green#dest_blue");
    rtSym("UpdateGamma%calibrate=0");
    rtSym("#GammaRed%red");
    rtSym("#GammaGreen%green");
    rtSym("#GammaBlue%blue");

    rtSym("%FrontBuffer");
    rtSym("%BackBuffer");
    rtSym("%ScanLine");
    rtSym("VWait%frames=1");
    rtSym("Flip%vwait=1");
    rtSym("%GraphicsWidth");
    rtSym("%GraphicsHeight");
    rtSym("%GraphicsDepth");

    //buffer management
    rtSym("SetBuffer%buffer");
    rtSym("%GraphicsBuffer");
    rtSym("%LoadBuffer%buffer$bmpfile");
    rtSym("%SaveBuffer%buffer$bmpfile");
    rtSym("BufferDirty%buffer");

    //fast pixel reads/write
    rtSym("LockBuffer%buffer=0");
    rtSym("UnlockBuffer%buffer=0");
    rtSym("%ReadPixel%x%y%buffer=0");
    rtSym("WritePixel%x%y%argb%buffer=0");
    rtSym("%ReadPixelFast%x%y%buffer=0");
    rtSym("WritePixelFast%x%y%argb%buffer=0");
    rtSym("CopyPixel%src_x%src_y%src_buffer%dest_x%dest_y%dest_buffer=0");
    rtSym("CopyPixelFast%src_x%src_y%src_buffer%dest_x%dest_y%dest_buffer=0");

    //rendering
    rtSym("Origin%x%y");
    rtSym("Viewport%x%y%width%height");
    rtSym("Color%red%green%blue");
    rtSym("GetColor%x%y");
    rtSym("%ColorRed");
    rtSym("%ColorGreen");
    rtSym("%ColorBlue");
    rtSym("ClsColor%red%green%blue");
    rtSym("SetFont%font");
    rtSym("Cls");
    rtSym("Plot%x%y");
    rtSym("Rect%x%y%width%height%solid=1");
    rtSym("Oval%x%y%width%height%solid=1");
    rtSym("Line%x1%y1%x2%y2");
    rtSym("Text%x%y$text%centre_x=0%centre_y=0");
    rtSym("CopyRect%source_x%source_y%width%height%dest_x%dest_y%src_buffer=0%dest_buffer=0");

    //fonts
    rtSym("%LoadFont$fontname%height=12%bold=0%italic=0%underline=0");
    rtSym("FreeFont%font");
    rtSym("%FontWidth");
    rtSym("%FontHeight");
    rtSym("%StringWidth$string");
    rtSym("%StringHeight$string");

    //movies
    rtSym("%OpenMovie$file");
    rtSym("%DrawMovie%movie%x=0%y=0%w=-1%h=-1");
    rtSym("%MovieWidth%movie");
    rtSym("%MovieHeight%movie");
    rtSym("%MoviePlaying%movie");
    rtSym("CloseMovie%movie");

    rtSym("%LoadImage$bmpfile");
    rtSym("%LoadAnimImage$bmpfile%cellwidth%cellheight%first%count");
    rtSym("%CopyImage%image");
    rtSym("%CreateImage%width%height%frames=1");
    rtSym("FreeImage%image");
    rtSym("%SaveImage%image$bmpfile%frame=0");

    rtSym("GrabImage%image%x%y%frame=0");
    rtSym("%ImageBuffer%image%frame=0");
    rtSym("DrawImage%image%x%y%frame=0");
    rtSym("DrawBlock%image%x%y%frame=0");
    rtSym("TileImage%image%x=0%y=0%frame=0");
    rtSym("TileBlock%image%x=0%y=0%frame=0");
    rtSym("DrawImageRect%image%x%y%rect_x%rect_y%rect_width%rect_height%frame=0");
    rtSym("DrawBlockRect%image%x%y%rect_x%rect_y%rect_width%rect_height%frame=0");
    rtSym("MaskImage%image%red%green%blue");
    rtSym("HandleImage%image%x%y");
    rtSym("MidHandle%image");
    rtSym("AutoMidHandle%enable");
    rtSym("%ImageWidth%image");
    rtSym("%ImageHeight%image");
    rtSym("%ImageXHandle%image");
    rtSym("%ImageYHandle%image");

    rtSym("ScaleImage%image#xscale#yscale");
    rtSym("ResizeImage%image#width#height");
    rtSym("RotateImage%image#angle");
    rtSym("TFormImage%image#a#b#c#d");
    rtSym("TFormFilter%enable");

    rtSym("%ImagesOverlap%image1%x1%y1%image2%x2%y2");
    rtSym("%ImagesCollide%image1%x1%y1%frame1%image2%x2%y2%frame2");
    rtSym("%RectsOverlap%x1%y1%width1%height1%x2%y2%width2%height2");
    rtSym("%ImageRectOverlap%image%x%y%rect_x%rect_y%rect_width%rect_height");
    rtSym("%ImageRectCollide%image%x%y%frame%rect_x%rect_y%rect_width%rect_height");

    rtSym("Write$string");
    rtSym("Print$string=\"\"");
    rtSym("$Input$prompt=\"\"");
    rtSym("Locate%x%y");

    rtSym("ShowPointer");
    rtSym("HidePointer");
}
