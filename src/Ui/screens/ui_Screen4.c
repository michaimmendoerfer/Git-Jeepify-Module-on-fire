// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project_Jeepify_Large_PDC

#include "../ui.h"

void ui_Screen4_screen_init(void)
{
    ui_Screen4 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Screen4, &ui_img_bgpng_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Keyboard1 = lv_keyboard_create(ui_Screen4);
    lv_obj_set_width(ui_Keyboard1, 405);
    lv_obj_set_height(ui_Keyboard1, 199);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);

    ui_TextArea1 = lv_textarea_create(ui_Screen4);
    lv_obj_set_width(ui_TextArea1, 248);
    lv_obj_set_height(ui_TextArea1, 44);
    lv_obj_set_x(ui_TextArea1, 113);
    lv_obj_set_y(ui_TextArea1, 6);
    lv_obj_set_align(ui_TextArea1, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_TextArea1, "Placeholder...");



    lv_keyboard_set_textarea(ui_Keyboard1, ui_TextArea1);

}
