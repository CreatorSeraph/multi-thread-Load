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

	template<typename Func, typename ...Args, typename = typename std::enable_if_t<std::is_invocable_v<Func, Args...>>>
	void AddFunc(Func func, Args&&... args)
	{
		unique_lock lock(m_mutex);//m_funcQueue는 여러스레드에서 동시에 접근할것이다. 변수를 다루기 전에 문을 닫고 혼자 사용하자
		//m_funcQueue.push([func = std::move(func), ...args = std::forward<Args>(args)](){func(args...); });
		//m_funcQueue.push([func, args...](){func(args...);});
		m_funcQueue.push(std::bind(func, args...));
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

