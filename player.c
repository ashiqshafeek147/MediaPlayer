#include <stdio.h>
#include <cjson/cJSON.h>
#include "player.h"
#include <string.h>
#include <stdlib.h>

// void makePlaylist(struct Curr_Player *currplayer)
// {
//     setTrackID(&currplayer->trackinfo[0], 1);
//     setTrackName(&currplayer->trackinfo[0], "Song 1");
//     setTrackDuration(&currplayer->trackinfo[0], 5);

//     setTrackID(&currplayer->trackinfo[1], 2);
//     setTrackName(&currplayer->trackinfo[1], "Song 2");
//     setTrackDuration(&currplayer->trackinfo[1], 5);

//     setTrackID(&currplayer->trackinfo[2], 3);
//     setTrackName(&currplayer->trackinfo[2], "Song 3");
//     setTrackDuration(&currplayer->trackinfo[2], 195);

//     setTrackID(&currplayer->trackinfo[3], 4);
//     setTrackName(&currplayer->trackinfo[3], "Song 4");
//     setTrackDuration(&currplayer->trackinfo[3], 230);

//     setTrackID(&currplayer->trackinfo[4], 5);
//     setTrackName(&currplayer->trackinfo[4], "Song 5");
//     setTrackDuration(&currplayer->trackinfo[4], 180);

//     printf("Playlist Make Complete\n");
// }
int totalTrackNum;
int shuffleToggle=0,repeatToggle=0;
void makePlaylist(struct Curr_Player *playlist)
{
    FILE *jsonfile = fopen("playlist.json", "r");
    if (jsonfile == NULL)
    {
        printf("[!] Cannot Load JSON File\n");
    }
    char jsonBuffer[2048];
    int totalTracks = fread(jsonBuffer, 1, sizeof(jsonBuffer), jsonfile);
    fclose(jsonfile);
    cJSON *json = cJSON_Parse(jsonBuffer);
    cJSON *pl = cJSON_GetObjectItemCaseSensitive(json, "PlayList1");
    cJSON *track = NULL;
    int trackCounter = 0;
    int currentTrackID=0;
    playlist->totalTrackNum = 4;
    cJSON_ArrayForEach(track, pl)
    {
        cJSON *id = cJSON_GetObjectItemCaseSensitive(track, "TrackID");
        cJSON *tname = cJSON_GetObjectItemCaseSensitive(track, "TrackName");
        cJSON *tdur = cJSON_GetObjectItemCaseSensitive(track, "Duration");
        setTrackID(&playlist->trackinfo[trackCounter], atoi(id->valuestring));
        setTrackName(&playlist->trackinfo[trackCounter], tname->valuestring);
        int hours, minutes, seconds;
        sscanf(tdur->valuestring, "%d:%d:%d", &hours, &minutes, &seconds);
        setTrackDuration(&playlist->trackinfo[trackCounter], hours * 3600 + minutes * 60 + seconds);
        trackCounter++;
    }
    cJSON_Delete(json);
}
void playTrack(struct Curr_Player *currplayer,int trid)
{
    currplayer->currentTrackDuration = currplayer->trackinfo[trid].TrackDuration;
    //printf("Currently playing Track no: %d\nTrack name: %s\n",currplayer->trackinfo[currplayer->currentTrackID].TrackID,currplayer->trackinfo[currplayer->currentTrackID].TrackName);
}
void pauseTrack(struct Curr_Player *currplayer)
{
    printf("Paused\n");
    if(sec==0)
    {
        sec=0;
    }
    else
    {
        sec--;
    }
}
void nextTrack(struct Curr_Player *currplayer)
{
    // printf("Next Track %d  %d\n",currplayer->currentTrackID,totalTrackNum);
    // sleep(3);
    currplayer->currentTrackID=(currplayer->currentTrackID+1)%currplayer->totalTrackNum;
    userChoice=1;
    timer=0;
    sec=0;
}
void previousTrack(struct Curr_Player *currplayer)
{
    //printf("Prev Track");
    if(currplayer->currentTrackID==0)
    {
        currplayer->currentTrackID=totalTrackNum-1;
    }
    else
    {
        currplayer->currentTrackID=currplayer->currentTrackID-1;
    }
    userChoice=1;
    timer=0;
    sec=0;
}
void shufflePlaylist(struct Curr_Player *shuffleplayer)
{
        printf("Shuffle: ON\n");
        printf("Playlist is being shuffled\n");
        sleep(2);
        for (int i = shuffleplayer->totalTrackNum - 1; i > 0; i--)
        {
        int j = rand() % (i + 1);
        char tempName[50];
        int tempDuration;

        // struct Track_Info temp = currplayer->trackinfo[i];
        // currplayer->trackinfo[i]=currplayer->trackinfo[j];
        // currplayer->trackinfo[j]=temp;

        strncpy(tempName, shuffleplayer->trackinfo[i].TrackName, sizeof(tempName));
        tempDuration = shuffleplayer->trackinfo[i].TrackDuration;

        strncpy(shuffleplayer->trackinfo[i].TrackName, shuffleplayer->trackinfo[j].TrackName, sizeof(tempName));
        shuffleplayer->trackinfo[i].TrackDuration = shuffleplayer->trackinfo[j].TrackDuration;

        strncpy(shuffleplayer->trackinfo[j].TrackName, tempName, sizeof(tempName));
        shuffleplayer->trackinfo[j].TrackDuration = tempDuration;
        }    
}
void repeatTrack()
{
    if (!repeatToggle)
    {
        printf("Repeat: ON\n");
        repeatToggle = 1;
    }
    else
    {
        printf("Repeat:  OFF\n");
        repeatToggle = 0;
    }
    userChoice=1; 
}

void printPlaylist(struct Curr_Player *currplayer)
{
    printf("Current Track ID: %d\n", currplayer->currentTrackID);
    printf("Total Number of Tracks: %d\n", currplayer->totalTrackNum);

    for (int i = 0; i < currplayer->totalTrackNum; i++)
    {
        printf("Track %d:\n", i + 1);
        printf("  Track ID: %d\n", currplayer->trackinfo[i].TrackID);
        printf("  Track Name: %s\n", currplayer->trackinfo[i].TrackName);
        printf("  Duration (in seconds): %d\n", currplayer->trackinfo[i].TrackDuration);
    }
}