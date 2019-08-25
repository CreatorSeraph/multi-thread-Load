#include "DXUT.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadSize)
	:m_isPaused(false), m_isDestroy(false)
{
	m_threads.reserve(threadSize);//�̸� vector�� ������ ��Ƶδ� ������ �Ѵ�. ���Ҵ��� �Ͼ�� �ʰ� �����Ҽ� �ִ�.
	for (int i = 0; i < threadSize; ++i)
	{
		m_threads.emplace_back([this]() {//this�� ĸ���ϸ� �� Ŭ���� ������ ������ ��� �ٷ�� �ְ� �ȴ�.
			while (true)
			{
				if (m_funcQueue.empty() && m_isDestroy) return;//���ϵ� ���� ���� Pool�� ���� �ɶ��� �Ǿ����� thread�� ���� �׸�����..
				if (m_funcQueue.empty() || m_isPaused) continue;//���� ���ų� �Ͻ����� �����϶��� ���� mutex�� ���ϵ� ���� �����¿� �ִ´�.

				unique_lock lock(m_mutex);//���� ���� ���峪���� �ϴ� ������ �ᱸ�� ��������
				//lock_gurad�� ������ �Ҹ��ڿ����� Ǯ�� ������ lock_guard�� unlock�� ȣ���Ҽ� �ִ�.

				auto targetFunc = std::move(m_funcQueue.front());
				m_funcQueue.pop();//���ϴ� �Լ��� ã�Ƽ� ���� ����

				lock.unlock();//���� ���ݰ� ���ͼ� ���ؾ���

				targetFunc();
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	m_isDestroy = true;
	//auto&���� &�� ���� ������ �Ҹ��� thread�� ��������ڰ� ���� ������ �����°�. ������� for������ &�� �Ⱥپ������� ��������ڸ� ȣ���Ѵٴ� ���̴�.
	for (auto& iter : m_threads)//�̹� �������� ��������� ��� ����ɶ����� ��ٷ����Ѵ�.(������ �������̴ٰ� ���α׷��� ��������Ǹ�..?)
		iter.join();
}

void ThreadPool::AddFunc(std::function<void()> func)
{
	m_funcQueue.push(std::move(func));
}