/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  系统线程基类			                                        */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _VRSOFTTHREAD_H_
#define _VRSOFTTHREAD_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL CVRSoftThread
	{
	public:
		explicit CVRSoftThread(void);
		virtual ~CVRSoftThread(void);

	public:
		// 开始启动线程
		void Start(void);
		// 结束线程 线程结束返回
		void Join(void);
		// 线程挂起
		void Suspend(void);
		// 是否停止
		bool IsStop(void);
		// 是否挂起
		bool IsSuspend(void);

	protected:
		// 运行线程
		virtual void Run(void);
		// 线程结束之后执行
		virtual void Exit(void);
		

	private:
		// 循环执行线程
		void Loop(void);

	private:
		volatile bool m_bStop; // 是否停止
		volatile bool m_bIsStop; // 是否执行停止
		volatile bool m_bSuspend; // 是否挂起
		boost::thread* m_pBoostThread; // 多线程
	};
}


#endif // _VRSOFTTHREAD_H_