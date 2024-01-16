#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
// const char *playlist_json = "{ \"musicPlayer\": { \"currentSong\": \"Song Title\", \"artist\": \"Artist Name\", \"album\": \"Album Name\", \"duration\": \"00:00\", \"isPlaying\": false, \"volume\": 50, \"playlist\": [ { \"song\": \"Song 1\", \"artist\": \"Artist 1\", \"album\": \"Album 1\", \"duration\": \"00:00\" }, { \"song\": \"Song 2\", \"artist\": \"Artist 2\", \"album\": \"Album 2\", \"duration\": \"00:00\" } ] } }";

const char *playlist_json[1024];

enum MHD_Result ;
answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    if (0 == strcmp(url, "/playlist.json"))
    {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(playlist_json), (void *)playlist_json, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }
    else
    {
        const char *not_found = "Not found";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found), (void *)not_found, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main()
{
    FILE *fp = fopen("playlist.json", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
    else
    {
        printf("File opened\n");
    }
    // char json_data[1024];
    // strncpy(json_data, "haii", sizeof(json_data));
    fread(playlist_json, 1, sizeof(playlist_json), fp);
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}