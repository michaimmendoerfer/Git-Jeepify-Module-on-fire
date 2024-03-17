SET(SOURCES screens/ui_Screen2.c
    screens/ui_Screen3.c
    screens/ui_Screen4.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    images/ui_img_bgpng_png.c
    images/ui_img_1053270667.c)

add_library(ui ${SOURCES})
