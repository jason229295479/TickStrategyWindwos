#include "Singleton.h"

template<typename T>
T* Singleton<T>::m_pInstance = nullptr;