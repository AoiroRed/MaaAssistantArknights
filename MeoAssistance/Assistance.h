#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>

#include "AssDef.h"

namespace MeoAssistance {
	class WinMacro;

	class Assistance
	{
		enum class Task {
			StartButton1,
			StartButton2
		};
	public:
		Assistance();
		~Assistance();

		bool setSimulatorType(SimulatorType type);
		void start();
		// void pause();
		void stop();

	private:
		static void identify_function(Assistance* pThis);	// 识别线程，生产者
		static void control_function(Assistance* pThis);	// 控制线程，消费者

		bool run_task(Task task);

		std::shared_ptr<WinMacro> m_pCtrl = nullptr;
		std::shared_ptr<WinMacro> m_pWindow = nullptr;
		std::shared_ptr<WinMacro> m_pView = nullptr;
		std::queue<Task> m_tasks;
		std::mutex m_tasks_mutex;

		std::thread m_control_thread;
		std::thread m_identify_thread;
		bool m_control_exit = false;
		bool m_identify_exit = false;
		bool m_control_running = false;
		bool m_identify_running = false;
		std::condition_variable m_control_cv;
		std::condition_variable m_identify_cv;
	};

}