#ifndef _TRACK_H
#define _TRACK_H

struct Track_Info
{
    int TrackID;
    char TrackName[100];
    int TrackDuration;
};
void setTrackID(struct Track_Info *trackinfo, int tid);
void setTrackName(struct Track_Info *trackinfo, const char* tname);
void setTrackDuration(struct Track_Info *trackinfo, int tdur);


int getTrackID(struct Track_Info *trackinfo);
const char* getTrackName(struct Track_Info *trackinfo);
int getTrackDuration(struct Track_Info *trackinfo);

#endif
