#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/power_supply.h>
#include <linux/sched.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Battery-Aware Scheduler Demo (simulatable)");

#define DEFAULT_NICE 0
#define BATTERY_NICE 10

static struct delayed_work battery_work;

static int force_mode = -1;
module_param(force_mode, int, 0644);
MODULE_PARM_DESC(force_mode, "-1=AUTO, 0=AC, 1=BATTERY");

static unsigned int poll_ms = 5000;
module_param(poll_ms, uint, 0644);
MODULE_PARM_DESC(poll_ms, "Polling interval in ms (default 5000)");

static bool last_batt_state = false;
static bool have_last = false;

static bool on_battery_auto(void) {
  struct power_supply *psy;
  union power_supply_propval val;
  bool batt = false;

  psy = power_supply_get_by_name("BAT0");
  if (!psy)
    return false;

  if (!power_supply_get_property(psy, POWER_SUPPLY_PROP_ONLINE, &val))
    batt = (val.intval == 0);
  power_supply_put(psy);
  return batt;
}

static bool on_battery_now(void) {
  if (force_mode == 0)
    return false;
  if (force_mode == 1)
    return true;
  return on_battery_auto();
}

static void adjust_task_weights(struct work_struct *work) {
  struct task_struct *task;
  bool battery = on_battery_now();
  unsigned int adjusted = 0;

  rcu_read_lock();
  for_each_process(task) {
    if (!task->mm)
      continue;
    if (!task->signal)
      continue;

    if (!task->signal->tty) {
      if (battery) {
        if (task_nice(task) != BATTERY_NICE) {
          set_user_nice(task, BATTERY_NICE);
          pr_info(
              "battery-aware: Adjusted PID %d (%s) to nice %d (battery mode)\n",
              task->pid, task->comm, BATTERY_NICE);
          adjusted++;
        }
      } else {
        if (task_nice(task) != DEFAULT_NICE) {
          set_user_nice(task, DEFAULT_NICE);
          pr_info(
              "battery-aware: Adjusted PID %d (%s) to nice %d (default mode)\n",
              task->pid, task->comm, DEFAULT_NICE);
          adjusted++;
        }
      }
    }
  }
  rcu_read_unlock();

  if (!have_last || battery != last_batt_state || force_mode != -1) {
    pr_info("battery-aware: state=%s (force_mode=%d) adjusted=%u tasks\n",
            battery ? "ON_BATTERY" : "ON_AC", force_mode, adjusted);
    last_batt_state = battery;
    have_last = true;
  }

  schedule_delayed_work(&battery_work, msecs_to_jiffies(poll_ms));
}

static int __init battery_sched_init(void) {
  INIT_DELAYED_WORK(&battery_work, adjust_task_weights);
  schedule_delayed_work(&battery_work, msecs_to_jiffies(poll_ms));
  pr_info("Battery-Aware Scheduler loaded (poll=%ums, force_mode=%d)\n",
          poll_ms, force_mode);
  return 0;
}

static void __exit battery_sched_exit(void) {
  cancel_delayed_work_sync(&battery_work);
  pr_info("Battery-Aware Scheduler unloaded\n");
}

module_init(battery_sched_init);
module_exit(battery_sched_exit);
