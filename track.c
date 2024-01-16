#include "player.h"
#include <string.h>

void setTrackID(struct Track_Info *trackinfo, int tid)
{
    trackinfo->TrackID=tid;
}
void setTrackName(struct Track_Info *trackinfo, const char* tname)
{
    strncpy(trackinfo->TrackName,tname,sizeof(trackinfo)+10);
}
void setTrackDuration(struct Track_Info *trackinfo, int tdur)
{
    trackinfo->TrackDuration=tdur;
}
int getTrackID(struct Track_Info *trackinfo)
{
    return trackinfo->TrackID;
}
const char* getTrackName(struct Track_Info *trackinfo)
{
    return trackinfo->TrackName;
}
int getTrackDuration(struct Track_Info *trackinfo)
{
    return trackinfo->TrackDuration;
}