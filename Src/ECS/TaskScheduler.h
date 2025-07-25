#include "marl/defer.h"
#include "marl/event.h"
#include "marl/scheduler.h"
#include "marl/waitgroup.h"

#include <utility> // 用于 std::forward 和 std::invoke

class TaskScheduler
{
  public:
    // 初始化并绑定调度器到当前线程
    TaskScheduler()
    {
        scheduler.bind();
    }

    // 自动解绑并清理调度器
    ~TaskScheduler()
    {
        scheduler.unbind();
    }

    // 提交单个任务（支持任意参数）
    template <typename Func, typename... Args>
    void schedule(Func &&func, Args &&...args)
    {
        // 使用完美转发捕获函数和参数
        marl::schedule([func = std::forward<Func>(func),
                        args = std::make_tuple(std::forward<Args>(args)...)] {
            // 使用 std::apply 解包参数并调用函数
            std::apply(func, args);
        });
    }

    // 批量提交任务并返回关联的WaitGroup
    template <typename Func, typename... Args>
    marl::WaitGroup scheduleBatch(int numTasks, Func &&func, Args &&...args)
    {
        marl::WaitGroup wg(numTasks);

        for (int i = 0; i < numTasks; ++i)
        {
            // 使用完美转发捕获函数和参数
            marl::schedule([i,
                            func = std::forward<Func>(func),
                            args = std::make_tuple(std::forward<Args>(args)...),
                            &wg // 捕获WaitGroup引用
            ] {
                // 确保任务完成时计数减1（即使发生异常）
                defer(wg.done());

                // 调用函数并传递参数
                std::apply(func, std::tuple_cat(
                                     std::make_tuple(i), // 添加任务索引作为第一个参数
                                     args));
            });
        }

        return wg;
    }

    // 创建事件对象
    static marl::Event createEvent(marl::Event::Mode mode = marl::Event::Mode::Manual)
    {
        return marl::Event(mode);
    }

    // 等待任务组完成
    static void waitGroupComplete(marl::WaitGroup &wg)
    {
        wg.wait();
    }

  private:
    // 禁止复制和移动
    TaskScheduler(const TaskScheduler &) = delete;
    TaskScheduler(const TaskScheduler &&) = delete;
    TaskScheduler &operator=(const TaskScheduler &) = delete;
    TaskScheduler &operator=(const TaskScheduler &&) = delete;

    // 使用所有核心初始化调度器
    marl::Scheduler scheduler{marl::Scheduler::Config::allCores()};
};