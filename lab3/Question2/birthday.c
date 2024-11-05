#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Linux kernel module to demonstrate linked lists");
MODULE_VERSION("0.1");

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

static int __init birthday_init(void) {
    struct birthday *person;
    
    int i;
    for (i = 0; i < 5; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i + 1;
        person->month = i + 1;
        person->year = 1995 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
        printk(KERN_INFO "Added: %d/%d/%d\n", person->day, person->month, person->year);
    }

    
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "Traversing: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

static void __exit birthday_exit(void) {
    struct birthday *ptr, *next;

    
    list_for_each_entry_reverse(ptr, &birthday_list, list) {
        printk(KERN_INFO "Removing: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }

    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }
    
    printk(KERN_INFO "Module exited and memory freed\n");
}

module_init(birthday_init);
module_exit(birthday_exit);
