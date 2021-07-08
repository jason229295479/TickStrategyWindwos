#ifndef _SINGLETON_H_
#define  _SINGLETON_H_
/************************************************************************/
/* µ¥ÀýÄ£Ê½                                                                     */
/************************************************************************/
template <typename T>
class Singleton
{
public:
	template<typename... Args>
	static T* Instance(Args&&... args)
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T(std::forward<Args>(args)...);
		}
		return m_pInstance;
	}

	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			throw std::logic_error("the instance is not init.");
		}
		return m_pInstance;
	}


	static void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}

private:
	Singleton() {}

	virtual ~Singleton() {}

	Singleton(const Singleton &) {}
	Singleton& operator= (const Singleton &) {}

	static T* m_pInstance;
};
#endif // _SINGLETON_H_
