#ifndef VIRTUALCOM_H
#define VIRTUALCOM_H

#include <wx/string.h>
#include <stdint.h>

class VirtualCom
{
    public:
        static VirtualCom& getManager()
        {
            static VirtualCom manager;
            return manager;
        }

        /**
        * 定义虚拟串口对
        * 每一对虚拟串口在创建时会自动生成序号
        **/
        typedef struct {
            uint8_t index;
            wxString comA;
            wxString comB;
        } CommPairType;

        //以阻塞方式执行一个命令并返回其执行结果
        uint8_t execReadBack(wxString cmd,char* read_buff,size_t buff_len);

        //安装虚拟串口驱动
        uint8_t installDriver();

        //加载虚拟串口列表
        void loadCommPairs(CommPairType* commPairs,size_t* numOfPairs);

        //创建一对新的虚拟串口
        void createComPair(wxString comportA,wxString comportB);

        //删除指定的一对虚拟串口
        void removeComPair(uint8_t pairIndex);

    protected:

    private:
        //禁用拷贝构造
        VirtualCom();
        ~VirtualCom();
        VirtualCom(const VirtualCom&);
        void operator=(VirtualCom&);
};

#endif // VIRTUALCOM_H
