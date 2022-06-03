//add by wangshining 2021-12-20
#define NR_PHY_DEV_DRV 10 // 暂定为 10
//add by wangshining 2021-12-20
#define NO_DRV 0
#define DRV_FLOPPY 1
#define DRV_CDROM 2
#define DRV_IDE_HD 3 // 目前已经实现 IDE 驱动
#define DRV_CHAR_TTY 4
#define DRV_SCSI_HD 5
#define DRV_SATA_HD 6
#define DRV_MEM 7 // 对应我们要编写的驱动器类型
//add by wangshining 2021-12-20
struct t_phy_driver_op
{
    int (*open)(const char *, int, int);
    int (*close)(int);
    //int(_read_sector)(int, void _, int);
    //int(_write_sector)(int, void_, int); // 写一个扇区，指向函数的指针，指向具体的写扇区函数
} phy_driver_op_table[NR_PHY_DEV_DRV];
//add by wangshining 2021-12-20
struct t_phy_device_driver
{
    char driver_name[14];
    u8 flag; // 表示是否空闲？
    u8 type_driver;
    // 物理设备类型，驱动程序编码，也可以理解为主设备号。例如，DRV_IDE_HD（如果想把 IDE 的四块硬盘看作是四个驱动程序的话，可以定义四个常量 DRV_PRIMARY_MASTER 等，占据 IDE_HD 的 4 项），DRV_SATA_HD 等。代码可以据此判断调用相应的驱动程序。
    struct t_phy_driver_op *drv_op;
    // 指向相应的驱动程序结构的指针
} phy_device_driver_table[NR_PHY_DEV_DRV];
