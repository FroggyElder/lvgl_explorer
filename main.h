#ifndef _MAIN_H_
#define _MAIN_H_

#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "ui.h"

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

#define DISP_BUF_SIZE (480 * 1024)

//init functions
void lvglInit ();
void ui_event_init();

//misc functions
int fileCmp (const void* a,const void* b);
void switchDir (char* path);
void loadFiles (struct dirent* files,int dir_i,lv_obj_t* container,lv_event_cb_t fileLongClick,lv_event_cb_t folderBtnClick);

//event functions
void folderBtnClick(lv_event_t* e);
void fileLongClick(lv_event_t* e);

void serverFolderClick (lv_event_t* e);
void serverFileLongClick (lv_event_t* e);

void searchKbClick (lv_event_t* e);
void searchTaFocus(lv_event_t * e);

void searchKb1Click (lv_event_t* e);
void searchTa1Focus(lv_event_t * e);

void commandTaFocus(lv_event_t * e);
void commandKbClick (lv_event_t* e);

void commandTa1Focus(lv_event_t * e);
void commandKb1Click (lv_event_t* e);

void newFolderButton (lv_event_t * e);
void newFileButton (lv_event_t * e);
void terminalButton (lv_event_t * e);

void newFolder1Button (lv_event_t * e);

void deleteFileButton (lv_event_t* e);
void panelBackButton (lv_event_t* e);
void uploadButton (lv_event_t* e);

void deleteFile1Button (lv_event_t* e);
void panelBack1Button (lv_event_t* e);
void cloudDownloadButton (lv_event_t* e);

void mainScreenCb (lv_event_t* e);
void cloudScreenCb (lv_event_t* e);




//globals
char cur_terminal_cmd[256];
extern int server_socket;

//cloud connection
#define SERVER_PORT 8888
#define SERVER_IP "47.95.8.182"
#define MY_PORT 8888

enum client_request {
    CR_CHANGE_DIR,CR_UPLOAD_FILE,CR_DOWNLOAD_FILE,CR_READY,CR_TERMINAL
};

int tcpInit (struct sockaddr_in* addr,uint16_t port,char* ip);
void sendFile (char* filename);
void getFile (char* filename);
void switchServerDir (char* path);
void terminalToServer (char* cmd);

#endif