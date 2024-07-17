#include "main.h"

void folderBtnClick(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);

    char path[1024];
    sprintf(path,"%s/%s",getcwd(NULL,0),(char*)lv_event_get_user_data(e));
    switchDir(path);
}

void fileLongClick(lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    if(!strcmp(lv_label_get_text(lv_obj_get_child(target,0)),"..")) return;

    if (lv_obj_get_child_cnt(target)>1) {
        lv_obj_del(lv_obj_get_child(target,1));
        return;
    }

    lv_obj_t* check = lv_img_create(target);
    lv_img_set_src(check,&ui_img_check_png);
    lv_obj_clear_flag(ui_file_control_panel,LV_OBJ_FLAG_HIDDEN);
}

void serverFileLongClick (lv_event_t* e) {
    lv_obj_t* target = lv_event_get_target(e);
    if(!strcmp(lv_label_get_text(lv_obj_get_child(target,0)),"..")) return;

    if (lv_obj_get_child_cnt(target)>1) {
        lv_obj_del(lv_obj_get_child(target,1));
        return;
    }

    lv_obj_t* check = lv_img_create(target);
    lv_img_set_src(check,&ui_img_check_png);
    lv_obj_clear_flag(ui_file_control_panel1,LV_OBJ_FLAG_HIDDEN);
}

void searchKbClick (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    char path[1024];
    uint16_t btn_id;

    switch (event_code) {
        case LV_EVENT_READY:
            strncpy(path,lv_textarea_get_text(ui_search_ta),sizeof(path));

            switchDir(path);
            break;

        case LV_EVENT_LONG_PRESSED:
            btn_id = lv_keyboard_get_selected_btn(target);
            if (!strcmp(lv_keyboard_get_btn_text(target,btn_id),LV_SYMBOL_BACKSPACE))
                lv_textarea_set_text(ui_search_ta,"");
    }
}

void searchTaFocus(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_textarea_set_text(target,lv_textarea_get_placeholder_text(target));
        _ui_flag_modify(ui_search_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        lv_textarea_set_text(target,"");
        _ui_flag_modify(ui_search_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void searchKb1Click (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    char path[1024];
    uint16_t btn_id;

    switch (event_code) {
        case LV_EVENT_READY:
            strncpy(path,lv_textarea_get_text(ui_search_ta1),sizeof(path));

            switchServerDir(path);
            break;
        
        case LV_EVENT_LONG_PRESSED:
            btn_id = lv_keyboard_get_selected_btn(target);
            if (!strcmp(lv_keyboard_get_btn_text(target,btn_id),LV_SYMBOL_BACKSPACE))
                lv_textarea_set_text(ui_search_ta1,"");
    }
}


void searchTa1Focus(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_textarea_set_text(target,lv_textarea_get_placeholder_text(target));
        _ui_flag_modify(ui_search_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        lv_textarea_set_text(target,"");
        _ui_flag_modify(ui_search_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void commandKbClick (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    char cmd[1024];
    uint16_t btn_id;

    switch (event_code) {
        case LV_EVENT_READY:
            sprintf(cmd,"%s %s",cur_terminal_cmd,lv_textarea_get_text(ui_command_ta));

            _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
            _ui_flag_modify(ui_command_ta, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

            system(cmd);
            switchDir("./");
            break;
        
        case LV_EVENT_LONG_PRESSED:
            btn_id = lv_keyboard_get_selected_btn(target);
            if (!strcmp(lv_keyboard_get_btn_text(target,btn_id),LV_SYMBOL_BACKSPACE))
                lv_textarea_set_text(ui_command_ta,"");
    }
}

void commandKb1Click (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    char cmd[1024];
    uint16_t btn_id;

    switch (event_code) {
        case LV_EVENT_READY:
            sprintf(cmd,"%s %s",cur_terminal_cmd,lv_textarea_get_text(ui_command_ta1));

            _ui_flag_modify(ui_command_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
            _ui_flag_modify(ui_command_ta1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

            terminalToServer(cmd);

            switchServerDir("./");

            break;
        
        case LV_EVENT_LONG_PRESSED:
            btn_id = lv_keyboard_get_selected_btn(target);
            if (!strcmp(lv_keyboard_get_btn_text(target,btn_id),LV_SYMBOL_BACKSPACE))
                lv_textarea_set_text(ui_command_ta1,"");
    }
}

void commandTaFocus(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        lv_textarea_set_text(target,"");
        _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(target, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        strcpy(cur_terminal_cmd,"");
    }
}

void commandTa1Focus(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_FOCUSED) {
        _ui_flag_modify(ui_command_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
        lv_textarea_set_text(target,"");
        _ui_flag_modify(ui_command_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(target, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        strcpy(cur_terminal_cmd,"");
    }
}


void newFolderButton (lv_event_t * e) {
    strcpy(cur_terminal_cmd,"mkdir");

    lv_textarea_set_placeholder_text(ui_command_ta,"new folder name");
    _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_command_ta, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void newFolder1Button (lv_event_t * e) {
    strcpy(cur_terminal_cmd,"mkdir");

    lv_textarea_set_placeholder_text(ui_command_ta1,"new folder name");
    _ui_flag_modify(ui_command_keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_command_ta1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void newFileButton (lv_event_t * e) {
    strcpy(cur_terminal_cmd,"touch");

    lv_textarea_set_placeholder_text(ui_command_ta,"new file name");
    _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_command_ta, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void terminalButton (lv_event_t * e) {
    strcpy(cur_terminal_cmd,"");

    lv_textarea_set_placeholder_text(ui_command_ta,"terminal command");
    _ui_flag_modify(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    _ui_flag_modify(ui_command_ta, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void deleteFileButton (lv_event_t* e){
    char cmd[1024] = "rm -rf";
    for (int i=0;i<lv_obj_get_child_cnt(ui_files_panel);i++) {
        lv_obj_t* file_obj = lv_obj_get_child(ui_files_panel,i);

        if (lv_obj_get_child_cnt(file_obj)>1) {
            sprintf (cmd,"%s %s",cmd,lv_label_get_text(lv_obj_get_child(file_obj,0)));
        }
    }
    
    system(cmd);

    switchDir("./");
}

void deleteFile1Button (lv_event_t* e) {
    char cmd[1024] = "rm -rf";
    for (int i=0;i<lv_obj_get_child_cnt(ui_files_panel1);i++) {
        lv_obj_t* file_obj = lv_obj_get_child(ui_files_panel1,i);

        if (lv_obj_get_child_cnt(file_obj)>1) {
            sprintf (cmd,"%s %s",cmd,lv_label_get_text(lv_obj_get_child(file_obj,0)));
        }
    }

    terminalToServer(cmd);

    switchServerDir("./");
}


void cloudDownloadButton (lv_event_t* e) {

    for (int i=0;i<lv_obj_get_child_cnt(ui_files_panel1);i++) {
        lv_obj_t* file_obj = lv_obj_get_child(ui_files_panel1,i);

        if (lv_obj_get_child_cnt(file_obj)>1) {
            getFile(lv_label_get_text(lv_obj_get_child(file_obj,0)));
        }
    }

    switchServerDir("./");
}

void panelBackButton (lv_event_t* e) {
    switchDir("./");
}

void panelBack1Button (lv_event_t* e) {
    switchServerDir("./");
}

void uploadButton (lv_event_t* e) {
    for (int i=0;i<lv_obj_get_child_cnt(ui_files_panel);i++) {
        lv_obj_t* file_obj = lv_obj_get_child(ui_files_panel,i);

        if (lv_obj_get_child_cnt(file_obj)>1) {
            sendFile(lv_label_get_text(lv_obj_get_child(file_obj,0)));
        }
    }

    switchDir("./");
}

void mainScreenCb (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_cloud_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, &ui_cloud_screen_screen_init);
        switchServerDir("./");
    }
}

void cloudScreenCb (lv_event_t* e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, &ui_main_screen_screen_init);
        switchDir("./");
    }
}

void serverFolderClick (lv_event_t* e) {
    lv_obj_t * target = lv_event_get_target(e);

    switchServerDir(lv_label_get_text(lv_obj_get_child(target,0)));
}
