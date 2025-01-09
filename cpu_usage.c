#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/sched.h>
#include <linux/sched/loadavg.h>

static void log_cpu_usage(struct timer_list *t);

static struct timer_list my_timer;
static int interval = 10;

module_param(interval, int, 0644);
MODULE_PARM_DESC(interval, "Czas pomiędzy zapisami");

static void log_cpu_usage(struct timer_list *t)
{
    unsigned long avg_load;

    avg_load = avenrun[0]/65536*100;

    pr_info("Obicążenie CPU: %lu%%\n", avg_load);

    mod_timer(&my_timer, jiffies + msecs_to_jiffies(interval*1000));

}

static int __init cpu_usage_init(void){
    pr_info("Monitor użycia CPU załawdowany z interwałem %u sekund", interval);
    timer_setup(&my_timer, log_cpu_usage, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(interval*1000));

    return 0;
}

static void __exit cpu_usage_exit(void){
    pr_info("Monitr użycia CPU wyłączony");
    del_timer_sync(&my_timer);
}

module_init(cpu_usage_init);
module_exit(cpu_usage_exit);

MODULE_LICENSE("GPL");
