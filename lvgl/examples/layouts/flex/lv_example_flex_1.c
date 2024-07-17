#include "../../lv_examples.h"
#if LV_USE_FLEX && LV_BUILD_EXAMPLES

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
        printf("UsrData:%d\n" , (int)lv_event_get_user_data(e));
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

/**
 * A simple row and a column layout with flexbox
 */
void lv_example_flex_1(void)
{
    /*Create a container with ROW flex direction*/
    lv_obj_t * cont_row = lv_obj_create(lv_scr_act()); // 创建了一个产片显示框
    lv_obj_set_size(cont_row, 480, 480); // 设置显示框的大小
    lv_obj_align(cont_row, LV_ALIGN_TOP_MID, 0, 5); // 设置当前显示框的对齐方式
    lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW);

    /*Create a container with COLUMN flex direction*/
    // lv_obj_t * cont_col = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(cont_col, 200, 150);
    // lv_obj_align_to(cont_col, cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    // lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

    uint32_t i;

    for(i = 0; i < 50; i++) {

        lv_obj_t * obj;  // 按钮
        lv_obj_t * label; // 标签
        lv_obj_t * img; // 图像

        obj = lv_btn_create(cont_row); // 在显示框中创建一个按钮btn
        lv_obj_set_size(obj, 100, LV_PCT(100)); //  设置按钮的大小 宽度设置为100 高度则是自动识别

        // 设置按钮的回调函数
        // （当按钮被点击后会执行event_handler）
        //  并携带一个参数  i  到响应函数 event_handler 中
        lv_obj_add_event_cb(obj, event_handler, LV_EVENT_ALL, (void *)i); 

        img = lv_img_create(obj); // 创建一个图像标签
        lv_img_set_src(img, "S:102.png"); // 设置图像的内容
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 5); // 设置当前图像居中对齐


        label = lv_label_create(obj); // 创建一文本标签（用于显示文字）
        lv_label_set_text_fmt(label, "UnitPrice: %u", i); // 设置文字的内容(建议显示单价)
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 5); // 设置对其方式为底部中心对齐

    }
}

#endif
