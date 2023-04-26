#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "videocard.h"

vbe_mode_info_t vmi;
static void *video_mem;
static int  bytes_per_pixel;
void* (videographics_init)(uint16_t mode){
   reg86_t reg86;
   memset(&reg86, 0, sizeof(reg86));
   reg86.intno = 0x10;
   reg86.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
   reg86.bx = 1<<14|mode;
   if( sys_int86(&reg86) != 0 ) {
      printf("vg_exit(): sys_int86() failed \n");
      return NULL;
   }
   return NULL;

}


int (mappVm)(uint16_t mode){
  struct minix_mem_range mr;
  unsigned int vram_base;
  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use
              the frame-buffer size, instead */
  int r;				    


    if(vbe_get_mode_info(mode,&vmi)!=OK){
      return 1;
    }

    

  vram_base=vmi.PhysBasePtr;
  bytes_per_pixel=vmi.BytesPerScanLine / vmi.XResolution;
  vram_size=vmi.XResolution*vmi.YResolution*bytes_per_pixel;



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
  if(height+y>vmi.YResolution){
    height=vmi.YResolution-y;
  }
  if(width+x>vmi.XResolution){
    width=vmi.XResolution-x;
  }
  for(int i=0;i<height;i++){
    vg_draw_hline(x,y+i,width,color);
  }
  
  return EXIT_SUCCESS;
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){

  for(int i=0;i<len;i++){
    drawPixel(x+i,y,color);
  }
  return EXIT_SUCCESS;
}
void (drawPixel)(uint16_t x , uint16_t y,uint32_t color){
  uint64_t off_set=((y*vmi.XResolution)+x)*bytes_per_pixel;
    void *addr = (void *)((char *) video_mem + off_set);

  memcpy(addr, &color, vmi.BytesPerScanLine / vmi.XResolution);

}
