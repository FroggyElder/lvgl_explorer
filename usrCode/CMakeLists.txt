SET(SOURCES screens/ui_main_screen.c
    screens/ui_cloud_screen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_default_file_png.c
    images/ui_img_check_png.c
    images/ui_img_folder_png.c
    images/ui_img_add_file_png.c
    images/ui_img_new_folder_png.c
    images/ui_img_terminal_png.c
    images/ui_img_undo_png.c
    images/ui_img_delete_png.c
    images/ui_img_cloud_upload_png.c
    images/ui_img_cloud_download_png.c)

add_library(ui ${SOURCES})
