/*
* Copyright (C) 2016-2025, L-Acoustics and its contributors

* This file is part of LA_avdecc.

* LA_avdecc is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* LA_avdecc is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General Public License
* along with LA_avdecc.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file job_queue.hpp
 * @author Vitalij Mast
 */

#pragma once

#include <deque>
#include <functional>
#include <limits>
#include <mutex>
#include <utility>

class JobQueue final
{
public:
    using Job = std::function<void()>;

    JobQueue()                           = default;
    JobQueue(const JobQueue&)            = delete;
    JobQueue& operator=(const JobQueue&) = delete;

    void enqueue(const Job& job)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        job_queue_.push_back(job);
    }

    void enqueue(Job&& job)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        job_queue_.push_back(std::move(job));
    }

    std::size_t process(std::size_t max_count = std::numeric_limits<std::size_t>::max())
    {
        std::size_t processed = 0;

        while (processed < max_count)
        {
            Job job;

            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (job_queue_.empty())
                {
                    break;
                }

                job = std::move(job_queue_.front());
                job_queue_.pop_front();
            }

            if (job)
            {
                job();
            }

            ++processed;
        }

        return processed;
    }

    std::size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return job_queue_.size();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return job_queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::deque<Job>    job_queue_;
};
