#include "scheduler.h"
#include <SDL.h>

namespace Nebel
{
    SchedulerTask::SchedulerTask(std::function<void(float)> &action, double interval) : action(action), timestep(1/interval)
    {
        //
    }
    //Scheduler::Scheduler(std::function<void()> &action, double interval) : action(action), interval(interval)
    //{
    //    NOW = SDL_GetPerformanceCounter();
    //}
    Scheduler::Scheduler()
    {
        NOW = SDL_GetPerformanceCounter();
    }
    size_t Scheduler::addTask(SchedulerTask &task)
    {
        tasks.push_back(&task);
        return tasks.size()-1;
    }
    void Scheduler::removeTask(size_t index)
    {
        //tasks.pop_back();
    }
    void Scheduler::Update()
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        //deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency() );
        //accumulator += deltaTime;
        //if (accumulator >= interval) //TODO
        //{
        //    action();
	    //    accumulator -= interval;
        //}
        for (size_t i = 0; i < tasks.size(); i++)
        {
            tasks[i]->accumulator += deltaTime;
            if (tasks[i]->accumulator >= tasks[i]->timestep) //TODO
            {
                tasks[i]->action(deltaTime);
                tasks[i]->accumulator -= tasks[i]->timestep;
            }
        }
        
    }
} // namespace Nebel
