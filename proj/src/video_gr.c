#include <lcom/lcf.h>

#include <stdint.h>
#include "video_gr.h"

static void* membuffer;
static void* secondbuffer;
static void* thirdbuffer;
uint32_t VramSize;
uint16_t bytes_per_pixel;
vbe_mode_info_t vmi;

int (vg_init_new)(uint16_t mode){
    reg86_t reg;
    memset(&reg,0,sizeof(reg));
    reg.intno = 0x10;
    reg.ax = 0x4F02;
    reg.bx = BIT(14) | mode;
    if(sys_int86(&reg) != OK){
        return 1;
    }
    return 0;
}

int (map_vram)(uint16_t mode){
    struct minix_mem_range mr_first ;
    struct minix_mem_range mr_secondary ;
    struct minix_mem_range mr_third ;
    int r;				    

    if(vbe_get_mode_info(mode , &vmi) != OK){
        return 1;
    }
    bytes_per_pixel =   vmi.BytesPerScanLine/vmi.XResolution;
    VramSize = vmi.XResolution * vmi.YResolution * bytes_per_pixel; 
    //------------------------------------- map first buffer
    mr_first.mr_base = (phys_bytes) vmi.PhysBasePtr;	
    mr_first.mr_limit = mr_first.mr_base + 3*VramSize;  

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr_first)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    /* Map memory */

    membuffer = vm_map_phys(SELF, (void *)mr_first.mr_base, VramSize);

    if(membuffer == MAP_FAILED)
        panic("couldn't map video memory");
    
    //------------------------------------- map second buffer
    mr_secondary.mr_base = (phys_bytes) vmi.PhysBasePtr + VramSize;	


    secondbuffer = vm_map_phys(SELF, (void *)mr_secondary.mr_base, VramSize);

    if(secondbuffer == MAP_FAILED)
        panic("couldn't map video memory");

    //------------------------------------- map third buffer
    mr_third.mr_base = (phys_bytes) vmi.PhysBasePtr + 2*VramSize;	
    mr_third.mr_limit = mr_third.mr_base + VramSize;  


    thirdbuffer = vm_map_phys(SELF, (void *)mr_third.mr_base, VramSize);

    if(thirdbuffer == MAP_FAILED)
        panic("couldn't map video memory");
    memset(thirdbuffer , 0 , VramSize);
    memset(secondbuffer , 0 , VramSize);
    memset(membuffer , 0 , VramSize);
    return 0;


}

int (vg_getBuffer)(reg86_t *reg){
    reg->ax = 0x4F07;
    reg->bl =0x01;
    reg->intno = 0x10;
    reg->bh = 0x00;    
    if(sys_int86(reg) != OK){
        return 1 ;
    }
    

    return 0;
}

int (vg_update)(){
    //switch buffer
    reg86_t reg;
    memset(&reg , 0 , sizeof(reg));
    if(vg_getBuffer(&reg) != OK){
        return 1;
    }
    reg86_t reg_2;
    memset(&reg_2,0,sizeof(reg_2));          
    reg_2.ax = 0x4F07;      
        reg_2.bh = 0x00;       
    reg_2.bl = 0x00;    
    reg_2.intno =0x10;                    
    if(reg.dx == 0){
        reg_2.dx = vmi.YResolution;
    }else if(reg.dx == vmi.YResolution){
        reg_2.dx = 2*vmi.YResolution;
    }else{
        reg_2.dx = 0;
    }
    if(sys_int86(&reg_2) != OK){
        return 1;
    }
    void* tmp = membuffer;
    membuffer = secondbuffer;
    secondbuffer = thirdbuffer;
    thirdbuffer = tmp;
    memset(thirdbuffer , 0 , VramSize);
    return 0; 
}

int (R)(uint32_t color){
    return 1;
}
int (G)(uint32_t color){
    return 1;
}
int (B)(uint32_t color){
    return 1;
}

int (draw_pixel)(uint16_t x , uint16_t y , uint32_t color){
    uint32_t offset = (vmi.XResolution *y + x ) * bytes_per_pixel;
    void* addr  = (void*)((char*) secondbuffer + offset  );
    if(memcpy(addr , &color , bytes_per_pixel) != NULL){
        return 1;
    }
    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    for(int j = x ; j< x + len ; j++){
        draw_pixel(j,y,color);
    }
        return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
        for(int i = y ; i < y + height ; i ++){
            vg_draw_hline(x,i,width,color);
        }
        return 0;
}
int (drawXpm)(xpm_map_t xpm,int x , int y){
    xpm_image_t img;
    uint8_t *map;
    map = xpm_load(xpm,XPM_INDEXED,&img);
    int height = img.height;
    int width = img.width;
      for(int i = y; i < height + y; i++){
        for (int j = x ; j < width + x; j++){

          draw_pixel(j, i, *map);

          map++;
        }
      }
      return 0;
}
int (drawXpm8_8_8)(xpm_image_t img,int x , int y){
    int height = img.height;
    int width = img.width;
    int index = 0;
      for(int i = y; i < height + y; i++){
        for (int j = x ; j < width + x; j++){
        
        uint8_t bpp = img.size / (img.height * img.width);

        uint32_t color = 0;
            color |= *(img.bytes + (index * bpp) + 0);
            color |= *(img.bytes + (index * bpp) + 1) << (1 * 8);
            color |= *(img.bytes + (index * bpp) + 2) << (2 * 8);

            if (color == CHROMA_KEY_GREEN_888) {
                index++;
                continue;
            }

          draw_pixel(j, i,color);

            index++;
        }
      }
      return 0;
}
