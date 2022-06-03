#ifndef _ORANGES_MEM_H_
#define _ORANGES_MEM_H_
//added by wangshining 2021-12-26
#define NR_MEM_PER_DRIVE 3
#define MEM_FS_SIZE 256
struct t_dev_mem
{
        u32 start_mem;
        u32 fs_type;
        u32 size;
};

struct t_mem_info
{
        void *base;
        int size;
        int use_count;
        struct t_dev_mem dev_mem_table[NR_MEM_PER_DRIVE];
};
struct mem_fs
{
        u32 lin_addr;
        u32 phy_address;
} mem_fs[260];
PUBLIC int read_sector_mem(void *buf, int position, int size, int proc_nr);
PUBLIC int write_sector_mem(void *buf, int position, int size, int proc_nr);

/*add by wangshining 2021-12-20*/

PUBLIC void init_mem();
PUBLIC void mem_open();
PUBLIC void mem_close();
PUBLIC void mem_service();
PUBLIC void mem_rdwt(MESSAGE *p);
#endif