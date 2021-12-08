#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
	struct head_list *next;
	ktime_t start_time;
	ktime_t end_time;
};

MODULE_AUTHOR("Kondratiuk Pavlo <pasha.kondratiuk32@gmail.com>");
MODULE_DESCRIPTION("AK-2 Lab5");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static uint count_int = 1;
module_param(count_int, uint, 0444);
MODULE_PARM_DESC(count_int, "Number_of_prints");

static int __init hello_init(void)
{
	uint i = 0;

	struct head_list *this_var, *next_var;

	pr_info("Input %d\n", count_int);

	if (!count_int) {
		pr_info("Enter parameter > 0");
		pr_info("");
		return 0;
	}

	if (count_int >= 5 && count_int <= 10) {
		pr_warn("Parameter must be < 5");
	} else {
		if (count_int > 10) {
			pr_err("Parameter > 10");
			pr_info("");
			return -EINVAL;
		}
	}

	head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);
	this_var = head;

	for (i = 0; i < count_int; i++) {
		this_var->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
		this_var->start_time = ktime_get();
		pr_info("Hello, world!!!!!\n");
		this_var->end_time = ktime_get();
		next_var = this_var;
		this_var = this_var->next;
	}

	kfree(next_var->next);
	next_var->next = NULL;

	return 0;
}

static void __exit hello_exit(void)
{
	struct head_list *tmp_var;

	while (head != NULL && count_int != 0) {
		tmp_var = head;
		pr_info("time_of_printing: %lld",
			tmp_var->end_time - tmp_var->start_time);
		head = tmp_var->next;
		kfree(tmp_var);
	}
	pr_info("Md_rm");
	pr_info("");
}

module_init(hello_init);
module_exit(hello_exit);
