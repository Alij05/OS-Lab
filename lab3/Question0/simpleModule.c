#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

int simple_init(void){
 pr_info("Loading module...\n");
 return 0;
}

void simple_exit(void){
 pr_info("Removing module.\n");
}

module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("OS-LAB-Group");
