#pragma once

#include <cstdint>
#include <functional>

namespace Nebel
{
    struct SchedulerTask
    {
        double timestep = 0;
        double accumulator = 0;
        std::function<void()> action;
        SchedulerTask(std::function<void()> &action, double interval);
    };
    struct Scheduler
    {
        uint64_t NOW = 0;
        uint64_t LAST = 0;
        double deltaTime = 0;
        //double interval = 0;
        //double accumulator = 0;
        //std::function<void()> action;
        std::vector<SchedulerTask*> tasks;

        //Scheduler(std::function<void()> &action, double interval);
        Scheduler();
        size_t addTask(SchedulerTask &task);
        void removeTask(size_t index);
        void Update();
    };
} // namespace Nebel
