    #include <stdio.h>
    #include <cjson/cJSON.h>
    #include <string.h>
    #include "threadcntrl.h"
    #include "player.h"

    struct Curr_Player currplayer,shuffleplayer ;
    int userChoice=99;
    pthread_t displayHandle,userinput;
    FILE *jsonfile;

    void main()
    {
        int playListOpt = 0;
        int plLoc = 0;
        char pathName[1024], path[1024];
        char command1[] = "curl ";
        char command2[] = "> remote.json";
        char finalCommand[] = "";

        printf("Welcome to Music Player:\n");
        printf("Choose Playlist Location:\n");
        printf("1. Local Playlist\n2. Remote Playlist\n>>> \n");
        scanf("%d", &plLoc);

        if (plLoc == 1)
        {
            printf("Enter the file path: \n");
            scanf("%s", pathName);
            printf("Loading local playlist..\n");
            jsonfile = fopen(pathName, "r");
        }
        else
        {
            printf("Enter the remote file path: ");
            scanf("%s", pathName);
            //printf("Obtaining remote playlist...\n");
            strcat(command1, pathName);
            strcat(command1, "> remote.json");
            printf("%s\n", command1);
            sleep(2);
            system(command1);
            jsonfile = fopen("remote.json", "r");
        }

        if (jsonfile == NULL)
        {
            printf("[!] Cannot Load JSON File\n");
        }
        char jsonBuffer[2048];
        int totalBytes = fread(jsonBuffer, 1, sizeof(jsonBuffer), jsonfile);

        fclose(jsonfile);
        printf("Music Player Menu\n");
        printf("1. Play    2. Pause    3. Next    4. Previous    5. Shuffle    6. Repeat    7. 0.5x    8. 1x    9. 2x    0. Exit\n");
        //printf("\nSelect : "); 
        makePlaylist(&currplayer);
        makePlaylist(&shuffleplayer);
        // printf("%d\n", getTrackID(&currplayer.trackinfo[0]));
        // printf("%s\n", getTrackName(&currplayer.trackinfo[0]));
        // printf("%d", getTrackDuration(&currplayer.trackinfo[0]));
        pthread_create(&displayHandle,NULL,displaySong,NULL);
        pthread_create(&userinput,NULL,userInput,NULL);
        // printf("\n%d\n", currplayer.trackinfo[1].TrackID);
        // printf("%s\n", currplayer.trackinfo[1].TrackName);
        // printf("%d\n", currplayer.trackinfo[1].TrackDuration);
        
        pthread_join(displayHandle,NULL);
        pthread_join(userinput,NULL);

        
    }