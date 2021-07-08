#ifndef _QAMSGPACK_HPP_
#define  _QAMSGPACK_HPP

#include <sstream>
#include "msgpack.hpp"
#include "CommUtil.h"
class QAMsgPack
{
public:
	//���л�
	template<typename T>
	static void Serialize(T &&t, std::string &str)
	{
		std::stringstream buffer;
		//msgpack::sbuffer sbuf;
		msgpack::pack(buffer, t);
		// send the buffer ...
		buffer.seekg(0);
		// deserialize the buffer into msgpack::object instance.
		str.clear();
		str = buffer.str();		
	}

	//�����л� ������ͨ��ע�����л��е�'\0',������ݸ�string��������ֽض�
	template<typename T>
	static void Deserialized(const char *data, int isize, T &t )
	{
		try
		{
			if (data == nullptr || isize == 0)
			{
				return;
			}
			msgpack::object_handle oh = msgpack::unpack(data, isize);
			msgpack::object deserialized = oh.get();
			deserialized.convert(t);
		}
		catch (msgpack::type_error * e)
		{
			e->what();
			//std::cout << e->what() << std::endl;
		}
	}


	//�����л�
	template<typename T>
	static void Deserialized(const std::string &str, T &t)
	{
		try
		{
			if (str.empty())
			{
				return;
			}
			msgpack::object_handle oh = msgpack::unpack(str.data(), str.length());
			msgpack::object deserialized = oh.get();
			deserialized.convert(t);
		}
		catch (msgpack::type_error * e)
		{
			e->what();
			
			//std::cout << e->what() << std::endl;
		}
	}
};

//test 

#endif // _QAMSGPACK_HPP_
