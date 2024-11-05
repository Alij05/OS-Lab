#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

static int __init process_info_init(void) {
    struct task_struct *task;
    
    printk(KERN_INFO "Loading Process Info Module\n");
    for_each_process(task) {
        
        pid_t pid = task->pid;
        
        const char *process_name = task->comm;
        
        unsigned long cpu_usage = task->utime + task->stime;
        
        unsigned long mem_usage = task->mm ? task->mm->total_vm << (PAGE_SHIFT - 10) : 0; 
        
        printk(KERN_INFO "Process: %s [PID: %d] CPU Usage: %lu RAM Usage: %lu KB\n",
               process_name, pid, cpu_usage, mem_usage);
	printk("-------------------------------------------");
    }
    return 0;
}

static void __exit process_info_exit(void) {
    printk(KERN_INFO "Removing Process Info Module\n");
}

module_init(process_info_init);
module_exit(process_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Module to Display Process Information");

