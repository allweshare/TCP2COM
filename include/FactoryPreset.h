#ifndef FACTORYPRESET_H
#define FACTORYPRESET_H

#include <memory>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/fileconf.h>

using namespace std;

class FactoryPreset
{
    public:
        static FactoryPreset& getPreset()
        {
            static FactoryPreset preset;
            return preset;
        }
        shared_ptr<wxFileConfig> config;        //改用智能指针，不需要手动 delete
        const wxFileName app_exe_path;          //可执行程序的绝对路径
        const wxString app_root_dir;            //应用程序根目录
        const wxString cfg_file_path;           //配置文件存放路径
        wxString vcom_driver_path;              //分别对应32位或64位的驱动
        void SaveConfig();                      //修改完任意一项配置都需要保存
    protected:

    private:
        //禁用拷贝构造
        FactoryPreset();
        ~FactoryPreset();
        FactoryPreset(const FactoryPreset&);
        void operator=(FactoryPreset&);
};

#endif // FACTORYPRESET_H
