#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/rbtree.h>
#include <linux/slab.h>

struct my_node {
    int data;
    struct rb_node node;
};

struct rb_root my_tree = RB_ROOT;

static int __init rbtree_simple_init(void) {
    struct my_node *new_node;
    struct rb_node *node = my_tree.rb_node;
    int data = 42;

    printk(KERN_INFO "Initializing simple rbtree module\n");

    
    new_node = kmalloc(sizeof(*new_node), GFP_KERNEL);
    new_node->data = data;
    rb_link_node(&new_node->node, NULL, &my_tree.rb_node);
    rb_insert_color(&new_node->node, &my_tree);

    printk(KERN_INFO "Inserted node with data: %d\n", data);

    
    if (node && container_of(node, struct my_node, node)->data == data)
        printk(KERN_INFO "Found node with data: %d\n", data);
    else
        printk(KERN_INFO "Node not found.\n");

    return 0;
}

static void __exit rbtree_simple_exit(void) {
    struct rb_node *node = my_tree.rb_node;

    if (node) {
        struct my_node *entry = container_of(node, struct my_node, node);
        printk(KERN_INFO "Removing node with data: %d\n", entry->data);
        rb_erase(&entry->node, &my_tree);
        kfree(entry);
    }

    printk(KERN_INFO "Exiting simple rbtree module\n");
}

module_init(rbtree_simple_init);
module_exit(rbtree_simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple rbtree kernel module");
