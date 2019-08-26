#include "DXUT.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadSize)
	:m_isPaused(false), m_isDestroy(false)
{
	m_threads.reserve(threadSize);//미리 vector의 공간을 잡아두는 역할을 한다. 재할당이 일어나지 않게 방지할수 있다.
	for (int i = 0; i < threadSize; ++i)
	{
		m_threads.emplace_back([this]() // 람다식
		{//this를 캡쳐하면 이 클래스 내부의 변수는 모두 다룰수 있게 된다.
			while (true)
			{
				unique_lock lock(m_mutex);//m_funcQueue는 여러스레드에서 동시에 접근할것이다. 변수를 다루기 전에 문을 닫고 혼자 사용하자
				//lock_gurad는 무조건 소멸자에서만 unlock을 호출 할 수 있지만 lock_guard는 unlock을 호출 할 수 있다.

				if (m_funcQueue.empty() && m_isDestroy) return;//할일도 없고 이제 Pool이 삭제 될때가 되었으면 thread도 일을 그만두자..
				if (m_funcQueue.empty() || m_isPaused) continue;//일이 없거나 일시정지 상태일때는 굳이 mutex를 걸일도 없이 대기상태에 있는다.


				auto targetFunc = std::move(m_funcQueue.front());
				m_funcQueue.pop();//원하는 함수를 찾아서 빼고 나면

				lock.unlock();//이제 문닫고 나와서 일해야지

				targetFunc();
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	m_isDestroy = true;
	//auto&에서 &를 빼면 나오는 소리는 thread의 복사생성자가 없기 때문에 나오는것. 범위기반 for문에서 &가 안붙어있으면 복사생성자를 호출한다는 뜻이다.
	for (auto& iter : m_threads)//이미 실행중인 스레드들이 모두 종료될때까지 기다려야한다.(파일이 수정중이다가 프로그램이 강제종료되면..?)
		iter.join();
}

void ThreadPool::AddFunc(std::function<void()> func)
{
	m_funcQueue.push(std::move(func));
}