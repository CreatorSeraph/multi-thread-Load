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

