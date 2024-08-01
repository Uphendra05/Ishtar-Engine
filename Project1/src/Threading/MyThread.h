#pragma once
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <iostream>
#include <functional>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN




CRITICAL_SECTION g_CriticalSection;

namespace CriticalSection
{

	static void InitCS()
	{
		InitializeCriticalSection(&g_CriticalSection);

	}
	static void EnterCS()
	{
		EnterCriticalSection(&g_CriticalSection);
	}
	static void LeaveCS()
	{
		LeaveCriticalSection(&g_CriticalSection);
	}

	static void DeleteCS()
	{
		DeleteCriticalSection(&g_CriticalSection);
	}

}

namespace InterLock
{
	template <typename T>
	T Exchange(volatile T* target, T value) 
	{
		return InterlockedExchange(target, value);
	}

	template <typename T>
	T Add(volatile T* addend, T value) 
	{
		return InterlockedAdd(addend, value);
	}

	template <typename T>
	T Add64(volatile T* addend, T value)
	{
		return InterlockedAdd64(addend, value);
	}

	template <typename T>
	T Increment(volatile T* addend) 
	{
		return InterlockedIncrement(addend);
	}

	template <typename T>
	T Decrement(volatile T* addend) 
	{
		return InterlockedDecrement(addend);
	}

	template <typename T>
	T CompareExchange(volatile T* destination, T exchange, T comparand) 
	{
		return InterlockedCompareExchange(destination, exchange, comparand);
	}


}



enum class WaitTypes
{
	NONE = 0,
	SINGLE = 1,
	MULTIPLE = 2
};

template <typename Function, typename... Args>
class CustomThread
{

public:
	CustomThread() = default;
	CustomThread(Function func, Args... args) : m_ThreadFunction(std::bind(func, args...)) {}



	static DWORD WINAPI ThreadFunctionWrapper(LPVOID lpParam)
	{
		CustomThread* this_Threader = static_cast<CustomThread*>(lpParam);

		if (this_Threader)
		{
			this_Threader->m_ThreadFunction();
			return 0;
		}


			return 1;
	
	}

	HANDLE StartSingleThread() 
	{

		//CriticalSection::InitCS();

		m_ThreadHandle = CreateThread(
				NULL,                   // lpThreadAttributes,
				0,                      // dwStackSize,
				ThreadFunctionWrapper,  // lpStartAddress,
				this,                   // lpParameter,
				0,                      // dwCreationFlags,
				&m_ThreadId);           // lpThreadId

			if (m_ThreadHandle == nullptr)
			{
				std::cerr << "Thread creation failed!" << std::endl;
			}
			else
			{
				std::cerr << "Thread Created" << std::endl;

			}

			//WaitForSingleObject(m_ThreadHandle, 1000);
			//CloseHandle(m_ThreadHandle);

			//CriticalSection::DeleteCS();

			return m_ThreadHandle;
		
	}


	HANDLE StartMultipleThreads()
	{
		CriticalSection::InitCS();
		const unsigned int noofthreads = 14;
		HANDLE m_ThreadHandles[noofthreads] = { 0 };
		DWORD m_ThreadIds[noofthreads] = { 0 };


		for (unsigned int i = 0; i != noofthreads; i++)
		{
			m_ThreadHandles[i] = CreateThread(
							   NULL,                   // lpThreadAttributes,
							   0,                      // dwStackSize,
							   ThreadFunctionWrapper,  // lpStartAddress,
							   this,                   // lpParameter,
							   0,                      // dwCreationFlags,
							   &(m_ThreadIds[i]));           // lpThreadId
			
			if (m_ThreadIds[i] == NULL)
			{
				std::cerr << "Thread creation failed!" << std::endl;
			}

			

		}


		WaitForMultipleObjects(noofthreads, m_ThreadHandles, false, 1);

		size_t sizeOfArray = sizeof(m_ThreadHandles) / sizeof(m_ThreadHandles[0]);
		std::cout << "Size of the array: " << sizeOfArray << std::endl;
		CriticalSection::DeleteCS();

		return m_ThreadHandles[noofthreads];


	}

    
	void Begin(const HANDLE myHandle = nullptr, DWORD milliSecs = INFINITE, WaitTypes types = WaitTypes::NONE )
	{
		switch (types)
		{
		case WaitTypes::NONE:
			//Do Nothing;

			break;
		case WaitTypes::SINGLE:
			WaitForSingleObject(myHandle,milliSecs);

			break;
		case WaitTypes::MULTIPLE:

			//WaitForMultipleObjects(mt);
			break;
		default:
			break;
		}

	}

	/*bool End(const HANDLE myHandle = nullptr)
	{
		return CloseHandle(myHandle);
	}*/

	HANDLE GetThreadHandle() const 
	{
		return m_ThreadHandle;
	}


private:

	std::function<void()>  m_ThreadFunction;
	HANDLE m_ThreadHandle;
	DWORD m_ThreadId;
	WaitTypes m_WaitType;


	

};

#endif MYTHREAD_H
	



	








