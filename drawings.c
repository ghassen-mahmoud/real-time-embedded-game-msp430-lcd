

#include"drawings.h"
void rectangle (void){
    Filled_rectangle(0, 127, 0, 127, GRAPHICS_COLOR_ORANGE);
}
void circle (void){

    Filled_circle(25, 50, 20, GRAPHICS_COLOR_GREEN);
}
int8_t clear_drawing (uint8_t fig_number){

    if(fig_number==1){
        Filled_rectangle(0, 19, 0, 99, GRAPHICS_COLOR_WHITE);

        return 0 ;
    }else if(fig_number==2){
        Filled_circle(25, 50, 20, GRAPHICS_COLOR_WHITE);
        return 0 ;
    }else{
        return -1;
    }
}
