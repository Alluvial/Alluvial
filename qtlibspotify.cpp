
/******************************************************

  STOP HERE!  NO SERIOUSLY FUCKING STOP RIGHT NOW!
  IN ORDER FOR THIS CODE TO WORK YOU MUST GET A LIBSPOTIFY
  APPLICATION KEY FROM: https://devaccount.spotify.com/my-account/keys/

  GOT IT, YET?????????? PROBABLY NOT BUT FUCK IT!!!
  OK SO NOW WHEN YOU HAVE YOUR APPLICATION KEY, TAKE IT AND PLACE
  IT IN THE PARENT DIRECTORY OF THE FOLDER WHICH THIS FILE
  (fyi: this file is called qtlibspotify.cpp) IS CURRENTLY!

  DO NOT PUT IT ANYWHERE ELSE!! IF YOU DO A BAD PERSON WILL FIND YOU
  EAT ALL OF YOUR NUTELLA AND PEANUT BUTTER AND ICE CREAM. HE WILL
  ALSO CLOG YOUR TOILETS WITH YOU FAVORITE PAIR OF SOCKS!

  *****************************************************/

#define USER_AGENT "AlluvialMusicPlayer1"

#include "qtlibspotify.h"
//#include "../appkey.c"
#include "../appkey.h"
#include <QDebug>


#include "../appkey.h"

static int notify_events;
static pthread_mutex_t notify_mutex;
static pthread_cond_t notify_cond;
bool FLAG_SPOTIFY_STATUS;

static void  connection_error(sp_session *session, sp_error error){
    qDebug() << "Spotify:  Connection Error - " << sp_error_message(error);
}
static void logged_in(sp_session *session, sp_error error){
    qDebug() << "Spotify: Logged_in Reached";
    if(SP_ERROR_OK != error){
        FLAG_SPOTIFY_STATUS=false;
        qDebug() << "Spotify:  Log in failed: " << sp_error_message(error);
    }
    else{
        qDebug() << "Spotify: Log in successful";
        FLAG_SPOTIFY_STATUS=true;
    }

}
static void logged_out(sp_session *session){
    qDebug() << "Spotify: Logged Out";
}
static void log_message(sp_session *session, const char *data){
    qDebug() << "Spotify: log_message - "<< data;
}
static void notify_main_thread(sp_session *session){
    pthread_mutex_lock(&notify_mutex);
    notify_events = 1;
    pthread_cond_signal(&notify_cond);
    pthread_mutex_unlock(&notify_mutex);
}

static sp_session_callbacks callbacks = {
    &logged_in,
    &logged_out,
    NULL,
    &connection_error,
    NULL,
    &notify_main_thread,
    NULL,
    NULL,
    &log_message
};

static const char* convertToString(QString strInput){
    QByteArray byteForm = strInput.toLatin1();
    const char* charPtrForm = byteForm.data();
    return charPtrForm;
}

static void search_complete(sp_search* search, void* userdata){
    if(sp_search_error(search) == SP_ERROR_OK){
        //format and return the search results?????
        /*
         * options:
         *  1) return three result type for albums, artist, and tracks
         *
         *  2) return tracks with info about album/artist/etc
         * */
    }
    else{
        qDebug() << "Spotify: search result error - " << sp_search_error(search);
    }
    sp_search_release(search);
}
/*
static getDevice_ID(){
    FILE file;
}
*/
QtLibSpotify::QtLibSpotify()
{
    //emit spotifyLogin(username, password);


}

QtLibSpotify::~QtLibSpotify()
{

}

int QtLibSpotify::initSpotify(QString username, QString password){

    sp_session_config config;
    memset(&config, 0, sizeof(config));
    sp_error error;
    sp_error login_error;
    sp_session *session;

    qDebug() << "AppKey:" << g_appkey;

    config.api_version=SPOTIFY_API_VERSION;

    config.cache_location= "tmp";
    config.settings_location="tmp";
    /*
    const u_int8_t g_appKey[] = {

        };
    */
    config.proxy="193.235.32.164";
    config.application_key = g_appkey;
    qDebug() << g_appkey;
    config.application_key_size = sizeof(g_appkey);
    qDebug() << sizeof(g_appkey);

    config.user_agent = USER_AGENT;
    config.callbacks = &callbacks;
   // config.device_id= getDevice_ID();
    qDebug() << "next";

    qDebug()<< "initSpotify: Session_create result: " << (error = sp_session_create(&config, &session));
    if(SP_ERROR_OK != error)
    {
        qDebug() << "Spotify: failed to create session" << sp_error_message(error);
        return 2;
    }
    else
    {

        login_error = spotifyLogin(session, username, password);
        if(SP_ERROR_OK != login_error){
            qDebug() << "Spotify: Login Error - " << sp_error_message(login_error);
        }
    }
    return 0;
}

void QtLibSpotify::searchSpotify(sp_session *session, QString searchQuery){
    const char* strQuery = convertToString(searchQuery);
    sp_search_create(session, strQuery, 0, 10, 0, 10, 0, 10, 0, 10, SP_SEARCH_STANDARD, &search_complete, NULL);
}

void QtLibSpotify::playSongSpotify(sp_session *session, sp_track* track){
    sp_error error = sp_session_player_load(session, track);
    if(SP_ERROR_OK != error){
        qDebug() << "Spotify " <<sp_error_message(error);
    }
    else{
        sp_session_player_play(session, 1);
    }

}

/*
 * Public Slots
 *
 */
sp_error QtLibSpotify::spotifyLogin(sp_session *user_session, QString username, QString password){
    qDebug() << "spotifyLogin Signal was picked up";
    sp_error spotifyLoginError;
    const char* strUsername = convertToString(username);
    const char* strPassword = convertToString(password);
    //qDebug() << "Spotify: try relogin - " << sp_session_relogin(user_session);
    qDebug() <<"Spotify: try login - " << sp_error_message(spotifyLoginError=sp_session_login(user_session, strUsername, strPassword, 1, NULL));
    return spotifyLoginError;
}

sp_error QtLibSpotify::spotifyLogout(sp_session *user_session){
    qDebug() << "spotifyLogout Signal was picked up";
    return sp_session_logout(user_session);
}



