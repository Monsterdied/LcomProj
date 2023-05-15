#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "videocard.h"

static void *video_mem; 

static uint8_t bytesperpixel;

 vbe_mode_info_t info;




void (videographics_init)(uint16_t mode){
  reg86_t r86;
   
  /* Specify the appropriate register values */
  
  memset(&r86, 0, sizeof(r86));	/* zero the structure */

  r86.intno = 0x10; /* BIOS video services */
  r86.ah = 0x4F;    /* Set Video Mode function */
  r86.al = 0x02;    /* 80x25 text mode */
  mode |=(1<<14);
  r86.bx=mode;
  /* Make the BIOS call */

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
  }


}

int (mappVm)(uint16_t mode){
  struct minix_mem_range mr;
  unsigned int vram_base;
  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use
              the frame-buffer size, instead */
  int r;				    


    if(vbe_get_mode_info(mode,&info)!=OK){
      return 1;
    }

    

  vram_base=info.PhysBasePtr;
  bytesperpixel=info.BytesPerScanLine / info.XResolution;
  vram_size=info.XResolution*info.YResolution*bytesperpixel;



  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

	

  if( 0 != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }



  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);


  if(video_mem == MAP_FAILED){
    panic("couldn't map video memory");
    return 1;
    }
  return 0;
}



int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){

  if(x>=info.XResolution || y>=info.YResolution || y<0 || x<0) return 1;
  for(int i=0; i<height;i++){
    vg_draw_hline(x,y+i,width,color);
  }
  return 0;
}


void (vg_draw_Pixel)(uint16_t x, uint16_t y, uint32_t color){
  uint64_t off_set=((y*info.XResolution)+x)*bytesperpixel;
    void *addr = (void *)((char *) video_mem + off_set);

  memcpy(addr, &color, info.BytesPerScanLine / info.XResolution);

}
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){

  for(uint16_t i=0;i<len;i++){

      vg_draw_Pixel(i+x, y, color);
  }
  return 0;
}

uint32_t (R)(uint32_t first){
  uint32_t tmp = first>>info.RedFieldPosition;
  uint32_t mask_of_red = ((1<<info.RedMaskSize) - 1);
  return tmp & mask_of_red;
}
uint32_t (G)(uint32_t first){
  uint32_t tmp = first>>info.GreenFieldPosition;// vmi.GreenFieldPosition aponta para a posição da lsb da cor
  uint32_t mask_of_green = ((1<<info.GreenMaskSize) - 1);//vmi.greenMaskSize é apenas o numero de bytes utilizado pela cor
  return tmp & mask_of_green;//se fizermos a bitwise operation ficamos apenas com as bits que precisamos
}
uint32_t (B)(uint32_t first){
  uint32_t tmp = first>>info.BlueFieldPosition;
  uint32_t mask_of_blue = ((1<<info.BlueMaskSize) - 1);
  return tmp & mask_of_blue;
}






