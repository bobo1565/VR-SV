/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地球系统插件			                                        */
/* 时间： 2015-05-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _EARTHSYSTEMPLUGIN_H_
#define _EARTHSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CEarthSystemPlugin : public IPlugin
	{
	public:
		explicit CEarthSystemPlugin(void);
		virtual ~CEarthSystemPlugin(void);

	public:
		// 获取插件名称
		virtual const VRString& GetPluginName(void) const;
		// 获得插件版本
		virtual const VRString GetPluginVersion(void) const ;
		// 获得插件描述
		virtual const VRString& GetPluginDiscribe(void) const;
		// 安装插件
		virtual void Install(void) ;
		// 初始化插件
		virtual void Initialise(void);
		// 清除插件
		virtual void Shutdown(void);
		// 卸载插件
		virtual void UnInstall(void);

	private:
		IComFactory* m_pIComFactory; // 组件工厂
	};

	// 注册插件
	REGISTER_VRSOFT_PLUGIN(CEarthSystemPlugin, OSGEARTH_DLL);
}


#endif // _EARTHSYSTEMPLUGIN_H_
