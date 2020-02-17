#ifndef TEAUDIO_H_
#define TEAUDIO_H_

#include"SDL_mixer.h"

typedef Mix_Music *MusicClip;
typedef Mix_Chunk *SoundClip;

class AudioManager{//Not sure if it is good idea
private:

public:
};

MusicClip loadMusic(const char *path);
inline void playMusic(MusicClip clip);
inline void resumeMusic(MusicClip clip);
inline void pauseMusic(MusicClip clip);


SoundClip loadSound(const char *path);

void audio_Close();
#endif