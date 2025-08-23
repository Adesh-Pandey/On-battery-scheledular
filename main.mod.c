#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0x86954ffd, "power_supply_get_by_name" },
	{ 0x04ea78e3, "power_supply_get_property" },
	{ 0x2b79f936, "power_supply_put" },
	{ 0xd272d446, "__rcu_read_lock" },
	{ 0xa2152099, "init_task" },
	{ 0x04be2b8f, "set_user_nice" },
	{ 0xd272d446, "__rcu_read_unlock" },
	{ 0x534ed5f3, "__msecs_to_jiffies" },
	{ 0xaef1f20d, "system_wq" },
	{ 0x8ce83585, "queue_delayed_work_on" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xe4de56b4, "__ubsan_handle_load_invalid_value" },
	{ 0x71798f7e, "delayed_work_timer_fn" },
	{ 0x02f9bbf0, "init_timer_key" },
	{ 0x73bebd3f, "param_ops_uint" },
	{ 0x73bebd3f, "param_ops_int" },
	{ 0x85acaba2, "cancel_delayed_work_sync" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0x86954ffd,
	0x04ea78e3,
	0x2b79f936,
	0xd272d446,
	0xa2152099,
	0x04be2b8f,
	0xd272d446,
	0x534ed5f3,
	0xaef1f20d,
	0x8ce83585,
	0xd272d446,
	0xe4de56b4,
	0x71798f7e,
	0x02f9bbf0,
	0x73bebd3f,
	0x73bebd3f,
	0x85acaba2,
	0xe8213e80,
	0xd272d446,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"power_supply_get_by_name\0"
	"power_supply_get_property\0"
	"power_supply_put\0"
	"__rcu_read_lock\0"
	"init_task\0"
	"set_user_nice\0"
	"__rcu_read_unlock\0"
	"__msecs_to_jiffies\0"
	"system_wq\0"
	"queue_delayed_work_on\0"
	"__stack_chk_fail\0"
	"__ubsan_handle_load_invalid_value\0"
	"delayed_work_timer_fn\0"
	"init_timer_key\0"
	"param_ops_uint\0"
	"param_ops_int\0"
	"cancel_delayed_work_sync\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BFD4BE2ECD233A6F38C7C68");
