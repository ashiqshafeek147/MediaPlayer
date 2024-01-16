#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "threadcntrl.h"
#include "player.h"
extern struct Curr_Player currplayer,shuffleplayer;
extern int shuffleToggle;
extern int repeatToggle;
extern pthread_t displayHandle, userinput;
int sec=0,hr=0,min=0,timer=0;
char *songName;
int sleepTimer=1000000;
void* displaySong(void * args)
{
    while(1)
    {
        if(userChoice !=99)
        {
        //scanf("%d",&userChoice);
        system("clear");
        switch(userChoice)
        {
            case 1 : 
                //printf("Play");
                if(!shuffleToggle)
                {
                    playTrack(&currplayer,currplayer.currentTrackID);
                    songName=currplayer.trackinfo[currplayer.currentTrackID].TrackName;    
                }
                else
                {
                    playTrack(&shuffleplayer,shuffleplayer.currentTrackID);
                    songName=shuffleplayer.trackinfo[shuffleplayer.currentTrackID].TrackName;
                }
                break;
            case 2 : 
                //printf("Pause");
                if(!shuffleToggle)
                {
                    pauseTrack(&currplayer);
                }
                else
                {
                    pauseTrack(&shuffleplayer);
                }
                break;
            case 3 :
                if(!shuffleToggle)
                {
                    nextTrack(&currplayer);                     
                    songName=currplayer.trackinfo[currplayer.currentTrackID].TrackName;
                }
                else
                {
                    nextTrack(&shuffleplayer);
                    songName=shuffleplayer.trackinfo[shuffleplayer.currentTrackID].TrackName;
                }
                //printf("Next");
                break;
            case 4 :
                if(!shuffleToggle)
                {
                    previousTrack(&currplayer);                     
                    songName=currplayer.trackinfo[currplayer.currentTrackID].TrackName;
                }
                else
                {
                    previousTrack(&shuffleplayer);
                    songName=shuffleplayer.trackinfo[shuffleplayer.currentTrackID].TrackName;
                } 
                //printf("Previous");
                break;
            case 5 : 
                //printf("Shuffle");
                shufflePlaylist(&shuffleplayer);
                printPlaylist(&shuffleplayer);
                sleep(2);
                if (!shuffleToggle)
                {
                    printf("Shuffle: ON\n");
                    shuffleToggle = 1;
                }
                else
                {
                    printf("Shuffle: OFF\n");
                    shuffleToggle = 0;
                }
                userChoice = 1;
                break;
            case 6 : 
                //printf("Repeat");
                repeatTrack();
                break;
            case 7 : 
                printf("Playing at 0.5x\n");
                sleepTimer=2000000;
                break;
            case 8 : 
                printf("Playing at 1x\n");
                sleepTimer=1000000;
                break;
            case 9 : 
                printf("Playing at 2x\n");
                sleepTimer=500000;
                break;
            case 0 : 
                printf("\nSayanora");
                pthread_cancel(displayHandle);
                pthread_cancel(userinput);
                sleep(2);
                exit(0);
                break;
        }
        //printf("\nDuration: %02d:%02d:%02d",hr,min,sec);
        fflush(stdout);
        display(songName);       
        sec++;
        timer++;
        if(sec>=60)
        {
            sec=0;
            min++;
        }
        if(min>=60)
        {
            min=0;
            hr++;
        }
        struct Curr_Player *player;
        if(!shuffleToggle) player=&currplayer;
        else player=&shuffleplayer;
        if(timer>player->currentTrackDuration)
        {  
            if(!repeatToggle)
            {
                player->currentTrackID++;
            }
            sec=0;
            min=0;
            hr=0;
            timer=0;
        }
        usleep(sleepTimer);
        
        fflush(stdout);
        }
    }
    return NULL;
}
void* userInput(void* args)
{
    while(1)
    {
        if(userChoice==0)
        {
            break;
        }
        //printf("Select : ");
        scanf("%d",&userChoice);
        //printf("\nInput recieved\n");
    }
    return NULL;
}
void display(char* songName)
{
    if (!shuffleToggle)
        {
            printf("Now Playing: %s\t", songName);
            printf("Duration: %02d:%02d:%02d\n", hr, min, sec);
            printf("Total Duration: %d\n", currplayer.currentTrackDuration);
            printf("Music Player Menu\n");
            printf("1. Play    2. Pause    3. Next    4. Previous    5. Shuffle    6. Repeat    7. 0.5x    8. 1x    9. 2x    0. Exit\n");
        }
        else
        {
            printf("Now Playing: %s\t", songName);
            printf("Duration: %02d:%02d:%02d\n", hr, min, sec);
            printf("Total Duration: %d\n", shuffleplayer.currentTrackDuration);
            printf("Music Player Menu\n");
            printf("1. Play    2. Pause    3. Next    4. Previous    5. Shuffle    6. Repeat    7. 0.5x    8. 1x    9. 2x    0. Exit\n");
        }
        
}