#include "../../lv_examples.h"
#if LV_USE_PNG && LV_USE_IMG && LV_BUILD_EXAMPLES

/**
 * Open a PNG image from a file and a variable
 */
void lv_example_png_1(void)
{
    LV_IMG_DECLARE(img_wink_png);
    lv_obj_t * img;

    img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &img_wink_png);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);

    img = lv_img_create(lv_scr_act());

    // 使用图像数组实现显示图像 （缺点就是会让项目体积变大不方便传输）
    // lv_img_set_src(img, "A:lvgl/examples/libs/png/wink.png");

    // 使用图像的文件进行显示 （缺点就是图像跟程序需要分开传输 ， 优点就是图像的信息与程序没有直接关联因此程序文件更小）
    lv_img_set_src(img, "S:R-C.jpg");

    lv_obj_align(img, LV_ALIGN_RIGHT_MID, -20, 0);
}

#endif
