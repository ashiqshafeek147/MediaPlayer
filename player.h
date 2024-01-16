#ifndef _PLAYER_H
#define _PLAYER_H
#include "track.h"
#include "threadcntrl.h"
extern int sec;
struct Curr_Player
{
    struct Track_Info trackinfo[5];
    int currentTrackID;
    int currentTrackDuration;
    int totalTrackNum;
};
void makePlaylist(struct Curr_Player *currplayer);
void playTrack(struct Curr_Player *currplayer,int currentTrackID);
void pauseTrack(struct Curr_Player *currplayer);
void nextTrack(struct Curr_Player *currplayer);
void previousTrack(struct Curr_Player *currplayer);
void shufflePlaylist(struct Curr_Player *currplayer);
void printPlaylist(struct Curr_Player *currplayer);
void repeatTrack();
#endif
