#include"TE_audio.hpp"

#include<stdio.h>
#include<vector>

std::vector<MusicClip> musicClips;
std::vector<SoundClip> soundClips;

void audio_Close(){
    for(int i = 0; i < musicClips.size(); i++){
        Mix_FreeMusic(musicClips[i]);
        musicClips[i] = NULL;
    }
    musicClips.clear();

    for(int i = 0; i < soundClips.size(); i++){
        Mix_FreeChunk(soundClips[i]);
        soundClips[i] = NULL;
    }
    soundClips.clear();
}

MusicClip loadMusic(const char *path){
    MusicClip clip;
    clip = Mix_LoadMUS( path );
    if( clip == NULL )
    {
        printf( "Failed to load music: %s SDL_mixer Error: %s\n",path ,Mix_GetError() );
    }
    else{
        musicClips.push_back(clip);
    }

    return clip;
}

inline void playMusic(MusicClip clip){
    Mix_PlayMusic(clip,0);
}

SoundClip loadSound(const char *path){
    SoundClip clip;
    clip = Mix_LoadWAV( path );
    if( clip == NULL )
    {
        printf( "Failed to load sound: %s SDL_mixer Error: %s\n",path , Mix_GetError() );
    }
    else{
        soundClips.push_back(clip);
    }

    return clip;
}