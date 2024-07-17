#include "main.h"
int server_socket = -1;

int tcpInit (struct sockaddr_in* addr,uint16_t port,char* ip) {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket<0) {
        perror("server socket init");
        return -1;
    }

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = inet_addr(ip);

    for (int i=0;i<31;i++) {
        if (connect(tcp_socket,(struct sockaddr*)addr,sizeof(struct sockaddr_in))==0) break;
        else {
            printf("Waiting for server: %ds\n",i);
            sleep(1);
        }
        if(i==30) {
            printf ("Server down, terminating\n");
            close(tcp_socket);
            return -1;
        }
    }


    return tcp_socket;
}

void sendFile (char* filename) {
    int snd_fd = open(filename,O_RDONLY);
    if (snd_fd<0) {
        perror ("open");
        return;
    }

    struct stat snd_stat;
    fstat(snd_fd,&snd_stat);
    if (S_ISDIR(snd_stat.st_mode)) {
        close (snd_fd);
        return;
    }

    struct sockaddr_in server_addr;
    server_socket = tcpInit(&server_addr,MY_PORT,SERVER_IP);
    if (server_socket<0) {
        perror("tcpInit");
        close(snd_fd);
        return;
    }

    int msg = CR_UPLOAD_FILE;
    write(server_socket,&msg,sizeof(msg));
    write(server_socket,filename,strlen(filename)+1);

    read(server_socket,&msg,sizeof(msg));

    char send_buf[1024];
    for (size_t i=0;;i++) {
        size_t snd_size = read(snd_fd,send_buf,sizeof(send_buf));
        if (snd_size<=0) break;
        printf ("Sent %ldkb file\n",i);
        write(server_socket,&send_buf,snd_size);
    }
    printf ("Send completed\n");

    close(snd_fd);

    close(server_socket);
}

void getFile (char* filename) {
    struct sockaddr_in server_addr;
    server_socket = tcpInit(&server_addr,MY_PORT,SERVER_IP);
    if (server_socket<0) {
        perror("tcpInit");
        return;
    }

    int msg = CR_DOWNLOAD_FILE;
    write(server_socket,&msg,sizeof(msg));

    write(server_socket,filename,strlen(filename)+1);

    read(server_socket,&msg,sizeof(msg));
    if (msg!=CR_DOWNLOAD_FILE) {
        printf("request to get file refused :%s\n",filename);
        close(server_socket);
        return;
    }

    printf("getting file:%s\n",filename);
    char file_buf[1024];
    int fd = open(filename,O_WRONLY|O_CREAT,0666);
    while (1) {
        size_t ret = read(server_socket,file_buf,sizeof(file_buf));
        if (ret<=0) {
            break;
        }

        write(fd,file_buf,ret);
    }

    close(fd);
    close(server_socket);
}

void switchServerDir (char* path) {
    struct sockaddr_in server_addr;
    server_socket = tcpInit(&server_addr,MY_PORT,SERVER_IP);
    if (server_socket<0) {
        perror("tcpInit");
        return;
    }

    int msg = CR_CHANGE_DIR;
    write(server_socket,&msg,sizeof(msg));
    write(server_socket,path,1024);

    char server_path[1024];
    read(server_socket,server_path,sizeof(server_path));
    lv_textarea_set_placeholder_text(ui_search_ta1,server_path);
    lv_obj_add_flag(ui_file_control_panel1,LV_OBJ_FLAG_HIDDEN);

    int dir_i;
    struct dirent files[1024];
    read(server_socket,&dir_i,sizeof(dir_i));


    for (int i=0;i<dir_i;i++) {
        read(server_socket,files[i].d_name,sizeof(files[i].d_name));
    }

    for (int i=0;i<dir_i;i++) {
        read(server_socket,&files[i].d_type,sizeof(files[i].d_type));
    }

    loadFiles(files,dir_i,ui_files_panel1,serverFileLongClick,serverFolderClick);

    close(server_socket);
}

void terminalToServer (char* cmd) {
    struct sockaddr_in server_addr;
    server_socket = tcpInit(&server_addr,MY_PORT,SERVER_IP);
    if (server_socket<0) {
        perror("tcpInit");
        return;
    }

    int msg = CR_TERMINAL;
    write(server_socket,&msg,sizeof(msg));


    write(server_socket,cmd,strlen(cmd)+1);

    close(server_socket);
}