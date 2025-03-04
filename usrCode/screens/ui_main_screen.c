// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_main_screen_screen_init(void)
{
    ui_main_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_main_screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_imgs = lv_obj_create(ui_main_screen);
    lv_obj_remove_style_all(ui_imgs);
    lv_obj_set_width(ui_imgs, 100);
    lv_obj_set_height(ui_imgs, 50);
    lv_obj_set_align(ui_imgs, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgs, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_imgs, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image4 = lv_img_create(ui_imgs);
    lv_img_set_src(ui_Image4, &ui_img_default_file_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image1 = lv_img_create(ui_imgs);
    lv_img_set_src(ui_Image1, &ui_img_check_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 40
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image3 = lv_img_create(ui_imgs);
    lv_img_set_src(ui_Image3, &ui_img_folder_png);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_search_ta = lv_textarea_create(ui_main_screen);
    lv_obj_set_width(ui_search_ta, 700);
    lv_obj_set_height(ui_search_ta, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_search_ta, 0);
    lv_obj_set_y(ui_search_ta, 20);
    lv_obj_set_align(ui_search_ta, LV_ALIGN_TOP_MID);
    lv_textarea_set_placeholder_text(ui_search_ta, "Goto...");
    lv_textarea_set_one_line(ui_search_ta, true);
    lv_obj_add_state(ui_search_ta, LV_STATE_USER_2);       /// States



    ui_files_panel = lv_obj_create(ui_main_screen);
    lv_obj_set_width(ui_files_panel, 720);
    lv_obj_set_height(ui_files_panel, 300);
    lv_obj_set_align(ui_files_panel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_files_panel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_files_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    ui_control_panel = lv_obj_create(ui_main_screen);
    lv_obj_set_width(ui_control_panel, 750);
    lv_obj_set_height(ui_control_panel, 75);
    lv_obj_set_x(ui_control_panel, 0);
    lv_obj_set_y(ui_control_panel, -10);
    lv_obj_set_align(ui_control_panel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_control_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_control_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    ui_new_file = lv_imgbtn_create(ui_control_panel);
    lv_imgbtn_set_src(ui_new_file, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_add_file_png, NULL);
    lv_obj_set_height(ui_new_file, 40);
    lv_obj_set_width(ui_new_file, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_new_file, LV_ALIGN_CENTER);

    ui_new_folder = lv_imgbtn_create(ui_control_panel);
    lv_imgbtn_set_src(ui_new_folder, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_new_folder_png, NULL);
    lv_obj_set_height(ui_new_folder, 40);
    lv_obj_set_width(ui_new_folder, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_new_folder, LV_ALIGN_CENTER);

    ui_terminal = lv_imgbtn_create(ui_control_panel);
    lv_imgbtn_set_src(ui_terminal, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_terminal_png, NULL);
    lv_obj_set_height(ui_terminal, 40);
    lv_obj_set_width(ui_terminal, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_terminal, LV_ALIGN_CENTER);

    ui_file_control_panel = lv_obj_create(ui_main_screen);
    lv_obj_set_width(ui_file_control_panel, 750);
    lv_obj_set_height(ui_file_control_panel, 75);
    lv_obj_set_x(ui_file_control_panel, 0);
    lv_obj_set_y(ui_file_control_panel, -10);
    lv_obj_set_align(ui_file_control_panel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_file_control_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_file_control_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_add_flag(ui_file_control_panel, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_panel_back = lv_imgbtn_create(ui_file_control_panel);
    lv_imgbtn_set_src(ui_panel_back, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_undo_png, NULL);
    lv_obj_set_height(ui_panel_back, 40);
    lv_obj_set_width(ui_panel_back, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_panel_back, LV_ALIGN_CENTER);

    ui_delete_file = lv_imgbtn_create(ui_file_control_panel);
    lv_imgbtn_set_src(ui_delete_file, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_delete_png, NULL);
    lv_obj_set_height(ui_delete_file, 40);
    lv_obj_set_width(ui_delete_file, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_delete_file, LV_ALIGN_CENTER);

    ui_cloud_upload = lv_imgbtn_create(ui_file_control_panel);
    lv_imgbtn_set_src(ui_cloud_upload, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_cloud_upload_png, NULL);
    lv_obj_set_height(ui_cloud_upload, 40);
    lv_obj_set_width(ui_cloud_upload, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_align(ui_cloud_upload, LV_ALIGN_CENTER);

    ui_search_keyboard = lv_keyboard_create(ui_main_screen);
    lv_obj_set_width(ui_search_keyboard, 750);
    lv_obj_set_height(ui_search_keyboard, 200);
    lv_obj_set_x(ui_search_keyboard, 0);
    lv_obj_set_y(ui_search_keyboard, -20);
    lv_obj_set_align(ui_search_keyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_search_keyboard, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_command_keyboard = lv_keyboard_create(ui_main_screen);
    lv_obj_set_width(ui_command_keyboard, 750);
    lv_obj_set_height(ui_command_keyboard, 200);
    lv_obj_set_x(ui_command_keyboard, 0);
    lv_obj_set_y(ui_command_keyboard, -20);
    lv_obj_set_align(ui_command_keyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_command_keyboard, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_command_ta = lv_textarea_create(ui_main_screen);
    lv_obj_set_width(ui_command_ta, 700);
    lv_obj_set_height(ui_command_ta, LV_SIZE_CONTENT);    /// 40
    lv_obj_set_x(ui_command_ta, 0);
    lv_obj_set_y(ui_command_ta, 20);
    lv_obj_set_align(ui_command_ta, LV_ALIGN_TOP_MID);
    lv_textarea_set_placeholder_text(ui_command_ta, "Goto...");
    lv_textarea_set_one_line(ui_command_ta, true);
    lv_obj_add_state(ui_command_ta, LV_STATE_USER_2);       /// States
    lv_obj_add_flag(ui_command_ta, LV_OBJ_FLAG_HIDDEN);     /// Flags



}
