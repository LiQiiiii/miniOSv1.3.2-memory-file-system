/*************************************************************************/ /**
 *****************************************************************************
 * @file   mem.c
 * @author liqi
 * @date   2021-12-24
 *****************************************************************************
 *****************************************************************************/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "proc.h"
#include "global.h"
#include "proto.h"
#include "fs_const.h"
#include "hd.h"
#include "fs.h"
#include "fs_misc.h"
#include "mem.h"                                                           //added by wangshining 2021-12-26
#include "driver.h"                                                        //added by wangshining 2021-12-26
PUBLIC struct t_phy_device_driver phy_device_driver_table[NR_PHY_DEV_DRV]; //added by liqi 2021-12-23
PUBLIC struct t_phy_driver_op phy_driver_op_table[NR_PHY_DEV_DRV];         //added by liqi 2021-12-23                                //added by liqi 2021-12-23

/*****************************************************************************
 *                                init_mem
 *****************************************************************************/
PUBLIC void init_mem()
{
    /* add by wangshining 2021-12-20*/

    memset(&mem_info, 0, sizeof(mem_info));

    mem_info.size = 2048;
    mem_info.use_count = 0;
    int i, tempaddr;
    int *phy_addr;
    tempaddr = MEMFSLinBase;
    for (i = 0; i < MEM_FS_SIZE; i++, tempaddr += num_4K)
    {

        mem_fs[i].phy_address = do_kmalloc_4k();
        mem_fs[i].lin_addr = K_PHY2LIN(mem_fs[i].phy_address);
        // phy_addr = mem_fs[i].phy_address;
        //deleted by wnagshining 2021-12-28
        // disp_str("mem_start:");
        // disp_int(i);
        // disp_str(" ");
        // disp_int(mem_fs[i].lin_addr);
        // disp_str(" ");
        // disp_int(phy_addr);
        // disp_str("\n");
        // lin_mapping_phy(mem_fs[i].lin_addr,
        //                 MAX_UNSIGNED_INT,
        //                 p_proc_current->task.pid,
        //                 PG_P | PG_USU | PG_RWW,  //页目录的属性位
        //                 PG_P | PG_USU | PG_RWW); //页表的属性位
    }
    mem_info.base = (void *)((MEMFSLinBase)&0xFFFFF000);
    for (i = 1; i < NR_MEM_PER_DRIVE; i++)
    {
        mem_info.dev_mem_table[i].start_mem = (i - 1) * 1024;
        mem_info.dev_mem_table[i].size = 1024;
    }
    mem_info.dev_mem_table[1].fs_type = ORANGE_TYPE;
    mem_info.dev_mem_table[2].fs_type = FAT32_TYPE;
    mem_info.dev_mem_table[0].start_mem = 0;
    mem_info.dev_mem_table[0].size = 0;
    mem_info.dev_mem_table[0].fs_type = NO_FS_TYPE;
}
/*add by wangshining 2021-12-26 */
/*add by wangshining 2021-12-26 */
PUBLIC void mem_open()
{

    if (mem_info.use_count++ == 0)
    {
        mem_service();
    }
    return;
}
/*add by wangshining 2021-12-26 */
PUBLIC void mem_close()
{
    mem_info.use_count--;
    return;
}
/*add by wangshining 2021-12-26 */
PUBLIC void mem_service()
{
    disp_str("mem_base:");
    disp_int(mem_info.base);
    disp_str("\n");
    disp_str("mem_size:");
    disp_int(mem_info.size);
    disp_str("\n");
    int i;
    for (i = 0; i < NR_MEM_PER_DRIVE; i++)
    {
        disp_str("PART_");
        disp_int(i);
        disp_str(": base ");
        disp_int(mem_info.dev_mem_table[i].start_mem);
        disp_str(", size ");
        disp_int(mem_info.dev_mem_table[i].size);
        disp_str("\n");
    }
    return;
}
PUBLIC int read_sector_mem(void *buf, int position, int size, int proc_nr)
{
    int mem_p = position >> 3;
    int off = position % 8;
    int *p = mem_fs[mem_p].lin_addr;
    // disp_str("before:");
    // disp_int(p);
    // disp_str("  ");
    p += (off * 512) >> 2;
    int size_left = size >> SECTOR_SIZE_SHIFT;
    int i = 0;
    int size_i = 0;
    // disp_str("\nread:");
    // disp_int(position);
    // disp_str(" ");
    // disp_str("read:");
    // disp_int(mem_p);
    // disp_str(" | ");
    // disp_int(off);
    // disp_str("  ");
    // disp_str("after:");
    // disp_int(p);
    // disp_str("\n");
    // phys_copy(buf, p, size_left);

    // disp_int(size);
    // disp_str(" \n");
    void *la = (void *)va2la(proc_nr, buf);
    while (size_left)
    {
        int left_sect = min(8, size_left);
        if (i == 0)
        {
            left_sect = min(8 - off, size_left);
            //disp_int(left_sect);
            memcpy(la, p, left_sect * 512);
        }
        else
        {
            p = mem_fs[mem_p + i].lin_addr;
            la = (void *)va2la(proc_nr, buf + size_i);
            memcpy(la, p, left_sect * 512);
        }
        size_i += left_sect * 512;
        i++;

        size_left -= left_sect;
        //disp_int(size_left);
    }
    // disp_str("buf: ");
    // disp_str(buf);
    // disp_str("\n");
    return 1;
}
PUBLIC int write_sector_mem(void *buf, int position, int size, int proc_nr)
{
    // disp_str("\nwrite:");
    // disp_int(position);
    // disp_str(" ");
    // disp_int(size);
    // disp_str(" \n");
    int mem_p = position >> 3;
    int off = position % 8;
    int *p = mem_fs[mem_p].lin_addr;
    // disp_str("before:");
    // disp_int(p);
    // disp_str(" ");
    p += (off * 512) >> 2;
    // disp_str("write:");
    // disp_int(mem_p);
    // disp_str(" | ");
    // disp_int(off);
    // disp_str("  ");
    // disp_str("after:");
    // disp_int(p);
    // disp_str("\n");
    int size_left = size >> SECTOR_SIZE_SHIFT;
    int i = 0;
    int size_i = 0;
    // disp_str("buf: ");
    // disp_str(buf);
    // disp_str("\n");
    //phys_copy(p, buf, size_left);
    void *la = (void *)va2la(proc_nr, buf);
    while (size_left)
    {
        int left_sect = min(8, size_left);
        if (i == 0)
        {
            left_sect = min(8 - off, size_left);
            memcpy(p, la, left_sect * 512);
        }
        else
        {
            p = mem_fs[mem_p + i].lin_addr;
            la = (void *)va2la(proc_nr, buf + size_i);
            memcpy(p, la, left_sect * 512);
        }
        size_i += left_sect * 512;
        i++;
        size_left -= left_sect;
    }
    return 1;
}