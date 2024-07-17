#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SERVER_IP "47.95.8.182"
#define SERVER_PORT 8888
#define BACK_LOG 5

enum client_request {
    CR_CHANGE_DIR,CR_UPLOAD_FILE,CR_DOWNLOAD_FILE,CR_READY,CR_TERMINAL
};

int client_socket = -1;

int tcpInit (struct sockaddr_in* server_addr) {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket<0) {
        perror("server socket init");
        return -1;
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(SERVER_PORT);
    server_addr->sin_addr.s_addr = INADDR_ANY;

    int on = 1;
    setsockopt(tcp_socket,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    if(bind(tcp_socket,(struct sockaddr*)server_addr,sizeof(struct sockaddr_in))<0) {
        perror ("server bind");
        return -1;
    }
    if(listen(tcp_socket,BACK_LOG)<0) {
        perror ("server listen");
        return -1;
    }

    return tcp_socket;
}

void getClientFile () {
    char file_name[256];
    read(client_socket,file_name,sizeof(file_name));

    int rcv_fd = open(file_name,O_WRONLY|O_CREAT,0666);
    char rcv_buf[1024];

    int msg = 0;
    write(client_socket,&msg,sizeof(msg));

    for (size_t i=0;;i++){
        printf ("Recvived %ld kb data\n",i);
        size_t rcv_size = read(client_socket,&rcv_buf,sizeof(rcv_buf));
        if (rcv_size<=0) break;
        write (rcv_fd,rcv_buf,rcv_size);
    }

    printf ("Receive completed\n");
    close(rcv_fd);

    struct sockaddr_in addr;
}

void switchServerDir() {
    char rcv_path[1024];
    read(client_socket,rcv_path,sizeof(rcv_path));

    char cur_dir[1024];
    getcwd(cur_dir,sizeof(cur_dir));

    if (chdir(rcv_path)<0) {
        char tar_dir[2048];
        sprintf(tar_dir,"%s/%s",cur_dir,rcv_path);
        chdir(tar_dir);
    }
    
    getcwd(cur_dir,sizeof(cur_dir));
    write(client_socket,cur_dir,sizeof(cur_dir));


    DIR* dir = opendir(cur_dir);
    struct dirent files[1024];
    int dir_i = 0;

    while (1) {
        if (dir_i>=1024) break;
        struct dirent* temp = readdir(dir);
        if (temp==NULL) break;

        if (!strcmp(temp->d_name,"..")&&!strcmp(cur_dir,"/home/cy/cloud"))
            continue;

        files[dir_i++] = *temp;
    }

    write(client_socket,&dir_i,sizeof(dir_i));
   
    for (int i=0;i<dir_i;i++) {
        write(client_socket,files[i].d_name,sizeof(files[i].d_name));
    }

    for (int i=0;i<dir_i;i++) {
        write(client_socket,&files[i].d_type,sizeof(files[i].d_type));
    }

    closedir(dir);
}

void terminalFromClient() {
    char cmd[256];
    read(client_socket,cmd,sizeof(cmd));

    system(cmd);
}

void sentFile() {
    char filename[256];
    read(client_socket,filename,sizeof(filename));
    
    struct stat file_stat;
    stat(filename,&file_stat);
    if(S_ISDIR(file_stat.st_mode)) {
        int msg = ~CR_DOWNLOAD_FILE;
        write(client_socket,&msg,sizeof(msg));
        close(client_socket);
        return;
    }

    int msg = CR_DOWNLOAD_FILE;
    write(client_socket,&msg,sizeof(msg));

    int fd = open(filename,O_RDONLY);

    char file_buf[1024];
    while (1) {
        size_t ret = read(fd,file_buf,sizeof(file_buf));
        if (ret<=0) {
            break;
        }
        write(client_socket,file_buf,ret);
    }

    close(fd);
    close(client_socket);
}

int main () {
    chdir("/home/cy/cloud");

    struct sockaddr_in server_addr;
    int listen_socket = tcpInit(&server_addr);

    int client_msg;
    while (1) {
        close (client_socket);
        client_socket = accept(listen_socket,NULL,NULL);
        if (client_socket<0) {
            perror("accept");
            return -1;
        }

        if (read(client_socket,&client_msg,sizeof(client_msg)) <=0) continue;
        switch(client_msg) {
            case CR_UPLOAD_FILE:
                getClientFile();
                break;

            case CR_CHANGE_DIR:
                switchServerDir();
                break;

            case CR_TERMINAL:
                terminalFromClient();
                break;

            case CR_DOWNLOAD_FILE:
                sentFile();
                break;

            default:
                break;
        }
    }
}