#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "Log.h"
#include "LogSystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CLogManagerFactory::FACTORY_TYPE_NAME = LOGSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CLogSystem::CLogSystem(const VRString& strName):m_pDefaultLog(NULL)
	{
		SetName(strName);
	}

	CLogSystem::~CLogSystem()
	{
		// 回收内存
		VR_MUTEX_AUTO;

		// 遍历删除
		MapStrLog::iterator itor = m_mapStrLog.begin();
		for (; m_mapStrLog.end() != itor; ++itor)
		{
			// 回收软件
			VRSOFT_DELETE(itor->second);
		}

		// 清空所有数据
		m_mapStrLog.clear();
	}

	// 创建默认日志
	ILog* CLogSystem::CreateLog(const VRString& strLog, bool bDefaultLog, bool debuggerOutput , bool suppressFileOutput )
	{
		VR_MUTEX_AUTO;
		// 创建日志系统
		ILog* pLog = new CLog(strLog, debuggerOutput, suppressFileOutput);
		// 判断是否分配成功
		if (NULL == pLog)
		{
			throw ERROR_EXCEPT;
			return (NULL);
		}

		// 设置是否为默认的日志系统
		if (!m_pDefaultLog || bDefaultLog)
		{
			m_pDefaultLog = pLog;
		}

		// 添加进入到系统中
		m_mapStrLog.insert(MapStrLog::value_type(strLog, pLog));
		return (pLog);
	}

	// 获得默认的系统日志
	ILog* CLogSystem::GetDefaultLog(void)
	{
		VR_MUTEX_AUTO;
		return (m_pDefaultLog);
	}

	// 设置当前系统日志
	ILog* CLogSystem::SetDefaultLog(ILog* pLog)
	{
		VR_MUTEX_AUTO;

		// 保存当前日志
		ILog* pOldLog = m_pDefaultLog;
		m_pDefaultLog = pLog;
		return (pOldLog);
	}

	// 获得系统日志对象
	ILog* CLogSystem::GetLog(const VRString& strLog)
	{
		VR_MUTEX_AUTO;

		// 查询日志
		MapStrLog::iterator itor = m_mapStrLog.find(strLog);
		if (m_mapStrLog.end() == itor)
		{
			throw ERROR_EXCEPT;
			return (NULL);
		}

		// 返回日志
		return (itor->second);
	}

	// 销毁日志对象
	void CLogSystem::DestoryLog(const VRString& strLog)
	{
		// 查询日志
		MapStrLog::iterator itor = m_mapStrLog.find(strLog);
		// 判断是否存在
		if (m_mapStrLog.end() == itor)
		{
			return;
		}

		// 判断是否为当前日志
		if (itor->second == m_pDefaultLog)
		{
			m_pDefaultLog = NULL;
		}

		// 删除
		delete itor->second;
		m_mapStrLog.erase(itor);

		// 判断当前是否默认值
		if ((NULL == m_pDefaultLog) && (!m_mapStrLog.empty()))
		{
			m_pDefaultLog = m_mapStrLog.begin()->second;
		}
	}

	void CLogSystem::DestoryLog(ILog* pLog)
	{
		DestoryLog(pLog->GetName());
	}

	// 写入系统日志
	void CLogSystem::SetLogMessage(const VRString& strMsg, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		VR_MUTEX_AUTO;

		// 判断默认的是否为空
		if (NULL != m_pDefaultLog)
		{
			m_pDefaultLog->SetLogMessage(strMsg, uiCode, lml, maskDebug);
		}
	}

	const VRString& CLogSystem::GetTypeName(void) const
	{
		return CLogManagerFactory::FACTORY_TYPE_NAME;
	}

	// 初始化系统
	void CLogSystem::Init(void)
	{

	}
}

