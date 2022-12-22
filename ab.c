#include <linux/module.h>
#include <linux/kernel.h>
// #include <stdio.h>
#include <linux/sched.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Doe");
MODULE_DESCRIPTION("A module that prints task_struct details of a process");

int pid = -1;
module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "PID of the process to print task_struct details for");

static int __init task_struct_details_init(void)
{
    struct task_struct *task;
    struct pid *pid_struct;

    // Check if a valid PID was passed as a parameter
    if (pid <= 0) {
        printk(KERN_INFO "Invalid PID\n");
        return -EINVAL;
    }

    // Get the task_struct for the specified PID
    pid_struct = find_get_pid(pid);
    task = pid_task(pid_struct, PIDTYPE_PID);
    if (!task) {
        printk(KERN_INFO "Unable to find task_struct for PID %d\n", pid);
        return -EINVAL;
    }

    // Print the process group ID, user ID, and command path of the process
    printk(KERN_INFO "Process group ID: %d\n", task->tgid);
    // printk(KERN_INFO "User ID: %d\n", task->uid);
    printk(KERN_INFO "Command path: %s\n", task->comm);

    return 0;
}

static void __exit task_struct_details_exit(void)
{
    printk(KERN_INFO "Exiting task_struct details module\n");
}

module_init(task_struct_details_init);
module_exit(task_struct_details_exit);
