#pragma once
#include <thread>
#include <queue>
#include <mutex>

class ThreadPool
{
private:
	vector<thread> m_threads;
	queue<std::function<void()>> m_funcQueue;//먼저 들어온 함수가 먼저 실행되는 자료구조를 사용하기 위함
	bool m_isPaused;//일시정지를 할 이유가 있을지 모르겠네
	bool m_isDestroy;//threadPool이 사라질때 다른함수들에 알려줄 방법이 필요하다

	mutable mutex m_mutex;
public:
	//threadSize : 사용할 스레드의 개수
	//기본값 : hardware_concurrency : 논리 프로세서 개수
	ThreadPool(int threadSize = thread::hardware_concurrency());
	~ThreadPool();
public:
	void AddFunc(std::function<void()> func);
	template<typename ...Args>
	void AddFunc(std::function<void(Args...)> func, Args... args)
	{
		m_funcQueue.push([&func, args...](){func(args...)});//가변 템플릿 인자를 통해서 인자가 있는 함수도 추가할수 있게 되었다.
	}
	//이미 실행중인 함수를 제외한 이후 함수들은 작동을 일시정지 한다
	inline void Pause() { m_isPaused = true; }
	//일시정지 상태를 해제한다
	inline void Resume() { m_isPaused = false; }
	//이미 실행중인 함수를 제외한 이후 함수들을 제거한다
	//void Reset();
	//이미 실행중인 함수를 detach하고 이후 함수들을 제거한다
	//void Reset();
public:
	inline bool isEmpty() const { return m_funcQueue.empty(); }
	inline bool isPaused() const { return m_isPaused; }
};

