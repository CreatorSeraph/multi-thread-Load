#pragma once
#include <thread>
#include <queue>
#include <mutex>

class ThreadPool
{
private:
	vector<thread> m_threads;
	queue<std::function<void()>> m_funcQueue;//���� ���� �Լ��� ���� ����Ǵ� �ڷᱸ���� ����ϱ� ����
	bool m_isPaused;//�Ͻ������� �� ������ ������ �𸣰ڳ�
	bool m_isDestroy;//threadPool�� ������� �ٸ��Լ��鿡 �˷��� ����� �ʿ��ϴ�

	mutable mutex m_mutex;
public:
	//threadSize : ����� �������� ����
	//�⺻�� : hardware_concurrency : �� ���μ��� ����
	ThreadPool(int threadSize = thread::hardware_concurrency());
	~ThreadPool();
public:
	void AddFunc(std::function<void()> func);

	template<typename Func, typename ...Args, typename = typename std::enable_if_t<std::is_invocable_v<Func, Args...>>>
	void AddFunc(Func func, Args&&... args)
	{
		unique_lock lock(m_mutex);//m_funcQueue�� ���������忡�� ���ÿ� �����Ұ��̴�. ������ �ٷ�� ���� ���� �ݰ� ȥ�� �������
		//m_funcQueue.push([func = std::move(func), ...args = std::forward<Args>(args)](){func(args...); });
		//m_funcQueue.push([func, args...](){func(args...);});
		m_funcQueue.push(std::bind(func, args...));
	}
	//�̹� �������� �Լ��� ������ ���� �Լ����� �۵��� �Ͻ����� �Ѵ�
	inline void Pause() { m_isPaused = true; }
	//�Ͻ����� ���¸� �����Ѵ�
	inline void Resume() { m_isPaused = false; }
	//�̹� �������� �Լ��� ������ ���� �Լ����� �����Ѵ�
	//void Reset();
	//�̹� �������� �Լ��� detach�ϰ� ���� �Լ����� �����Ѵ�
	//void Reset();
public:
	inline bool isEmpty() const { return m_funcQueue.empty(); }
	inline bool isPaused() const { return m_isPaused; }
};

