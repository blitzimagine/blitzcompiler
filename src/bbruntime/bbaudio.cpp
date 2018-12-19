#include "std.h"
#include "bbaudio.h"

void audio_link(void (*rtSym)(std::string sym))
{
    rtSym("%LoadSound$filename");
    rtSym("FreeSound%sound");
    rtSym("LoopSound%sound");
    rtSym("SoundPitch%sound%pitch");
    rtSym("SoundVolume%sound#volume");
    rtSym("SoundPan%sound#pan");
    rtSym("%PlaySound%sound");
    rtSym("%PlayMusic$midifile");
    rtSym("%PlayCDTrack%track%mode=1");
    rtSym("StopChannel%channel");
    rtSym("PauseChannel%channel");
    rtSym("ResumeChannel%channel");
    rtSym("ChannelPitch%channel%pitch");
    rtSym("ChannelVolume%channel#volume");
    rtSym("ChannelPan%channel#pan");
    rtSym("%ChannelPlaying%channel");
    rtSym("%Load3DSound$filename");
}
