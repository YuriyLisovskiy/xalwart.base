/**
 * workers/abstract_worker.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Abstract worker.
 */

#pragma once

// C++ libraries.
#include <typeindex>

// Module definitions.
#include "../_def_.h"


__MAIN_NAMESPACE_BEGIN__

class AbstractWorker
{
public:
	class Task
	{
	};

	// Represent a function that will be called with an event.
	using TaskListener = std::function<void(Task&)>;

	virtual ~AbstractWorker() = default;

	template<class TaskType>
	inline void add_task_listener(const std::function<void(AbstractWorker*, TaskType&)>& listener)
	{
		this->add_task_listener(_get_task_type<TaskType>(), [this, listener](auto& task)
		{
			listener(this, static_cast<TaskType&>(task));
		});
	}

	template <class TaskType, typename ...TaskParametersType>
	inline void inject_task(TaskParametersType&&... parameters)
	{
		this->inject_task(
			_get_task_type<TaskType>(),
			std::make_unique<TaskType>(std::forward<TaskParametersType>(parameters)...)
		);
	}

	virtual void stop() = 0;

protected:
	virtual void add_task_listener(const std::type_index& task_type, const TaskListener& listener) = 0;

	virtual void inject_task(const std::type_index& task_type, std::unique_ptr<Task> task) = 0;

private:
	template<typename T>
	static auto _get_task_type()
	{
		return std::type_index(typeid(T));
	}
};

__MAIN_NAMESPACE_END__
