#include "main.h"

void lvglInit () {
    /*lvgl初始化*/
    lv_init();

    /*输出设备初始化及注册*/
    fbdev_init();
    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];
    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    //输入设备初始化及注册
    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);
    if (mouse_indev==NULL) {
        perror("mouse init");
        exit(-1);
    }
}

int fileCmp (const void* a,const void* b) {
    struct dirent* file_a = (struct dirent*)a;
    struct dirent* file_b = (struct dirent*)b;

    if (file_a->d_type-file_b->d_type) {
        if (file_a->d_type == DT_DIR) return -1;
        if (file_b->d_type == DT_DIR) return 1;
        return file_a->d_type - file_b->d_type;
    }
    else return strcmp(file_a->d_name,file_b->d_name);

}

void loadFiles (struct dirent* files,int dir_i,lv_obj_t* container,lv_event_cb_t fileLongClick,lv_event_cb_t folderBtnClick) {
    lv_obj_clean(container);
    qsort(files,dir_i,sizeof(files[0]),fileCmp);
    for (int i=0;i<dir_i;i++) {
        if (strcmp(files[i].d_name,"..")&&files[i].d_name[0]=='.') continue;
        
        lv_obj_t* file_icon = lv_imgbtn_create(container);
        lv_obj_set_height(file_icon, 64);
        lv_obj_set_width(file_icon, 64);   /// 1
        lv_obj_set_align(file_icon, LV_ALIGN_CENTER);
        lv_obj_add_event_cb(file_icon,fileLongClick,LV_EVENT_LONG_PRESSED,NULL);

        lv_obj_t* file_name = lv_label_create(file_icon);
        lv_obj_set_width(file_name, 64);   /// 1
        lv_obj_set_height(file_name, LV_SIZE_CONTENT);    /// 1
        lv_obj_set_align(file_name, LV_ALIGN_CENTER);
        lv_label_set_text(file_name,files[i].d_name);

        switch (files[i].d_type)
        {
            case DT_DIR:
                lv_imgbtn_set_src(file_icon, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_folder_png, NULL);
                lv_obj_add_event_cb(file_icon,folderBtnClick,LV_EVENT_SHORT_CLICKED,lv_label_get_text(file_name));
                break;
            
            default:
                lv_imgbtn_set_src(file_icon, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_default_file_png, NULL);
                break;
        }
    }
}

void switchDir (char* path) {
    char cur_dir[1024];
    if(chdir(path)<0) {
        perror("chdir");
        return;
    }

    //refresh objs
    lv_obj_add_flag(ui_file_control_panel,LV_OBJ_FLAG_HIDDEN);
    lv_textarea_set_placeholder_text(ui_search_ta,getcwd(cur_dir,sizeof(cur_dir)));

    DIR* dir = opendir(cur_dir);
    struct dirent files[1024];
    int dir_i = 0;
    while (1) {
        if (dir_i>=1024) break;
        struct dirent* temp = readdir(dir);
        if (temp==NULL) break;
        files[dir_i++] = *temp;
    }

    loadFiles(files,dir_i,ui_files_panel,fileLongClick,folderBtnClick);

    closedir(dir);
}

void ui_event_init() {
    //jump keyboard and ta
    lv_obj_add_event_cb(ui_search_keyboard,searchKbClick,LV_EVENT_ALL,NULL);
    lv_obj_add_event_cb(ui_search_ta,searchTaFocus,LV_EVENT_ALL,NULL);

    //command keyboard and ta
    lv_obj_add_event_cb(ui_command_keyboard,commandKbClick,LV_EVENT_ALL,NULL);
    lv_obj_add_event_cb(ui_command_ta,commandTaFocus,LV_EVENT_ALL,NULL);

    //server jump keyboard and ta
    lv_obj_add_event_cb(ui_search_keyboard1,searchKb1Click,LV_EVENT_ALL,NULL);
    lv_obj_add_event_cb(ui_search_ta1,searchTa1Focus,LV_EVENT_ALL,NULL);

    //command keyboard and ta
    lv_obj_add_event_cb(ui_command_keyboard1,commandKb1Click,LV_EVENT_ALL,NULL);
    lv_obj_add_event_cb(ui_command_ta1,commandTa1Focus,LV_EVENT_ALL,NULL);

    //function buttons
    lv_obj_add_event_cb(ui_new_folder,newFolderButton,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_new_file,newFileButton,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_terminal,terminalButton,LV_EVENT_CLICKED,NULL);

    //server function buttons
    lv_obj_add_event_cb(ui_new_folder1,newFolder1Button,LV_EVENT_CLICKED,NULL);

    //file function buttons
    lv_obj_add_event_cb(ui_delete_file,deleteFileButton,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_panel_back,panelBackButton,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_cloud_upload,uploadButton,LV_EVENT_CLICKED,NULL);

    //server file functions
    lv_obj_add_event_cb(ui_delete_file1,deleteFile1Button,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_panel_back1,panelBack1Button,LV_EVENT_CLICKED,NULL);
    lv_obj_add_event_cb(ui_cloud_download,cloudDownloadButton,LV_EVENT_CLICKED,NULL);

    //screen switch
    lv_obj_add_event_cb(ui_main_screen, mainScreenCb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_cloud_screen, cloudScreenCb, LV_EVENT_ALL, NULL);

}

int main(void)
{
    //init lvgl
    lvglInit();

    //init basic ui 
    ui_init();
    ui_event_init();

    //switch to root dir
    switchDir("/root");

    /*事物处理及告知lvgl节拍数*/
    while(1) {
        lv_timer_handler();//事务处理
        lv_tick_inc(5);//节拍累计
        usleep(5000);
    }

    return 0;
}


/*用户节拍获取*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}