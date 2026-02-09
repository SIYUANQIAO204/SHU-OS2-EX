
//
// Created by qiao on 25-12-8.
//定义了虚拟页和内存块
/*通过逻辑地址到实际地址的转化以及模拟修改内存中的内容
 */
#ifndef OS_MEMORY_H
#define OS_MEMORY_H
namespace memory{
    class VM{
    private:
        int st_address;//虚拟页的起始地址
        int id;//虚拟页的ID
        bool exist_in_memory;//该虚拟页是否存在与内存中
        bool modify;//该虚拟页内容发生修改
        int vis_time;//该虚拟页在存在于内存期间的访问次数
        int block_id;//分配的内存块的ID
    public:
        VM(int id, int address , bool exist= false, bool mod = false, int vis = 0, int block =-1)
        : id(id), st_address(address), exist_in_memory(exist), modify(mod), vis_time(vis), block_id(block) {}
        ~VM() = default;
        int getId() const {return id;}
        int getStaddress() const {return st_address;}//获取实际地址块的起始位置
        bool getModifyStatus() const {return modify;}//获悉虚拟页是否存在修改
        bool getExistStatus() const {return exist_in_memory;}//确认虚拟页是否存在于内存中
        int getVisitTime() const {return vis_time;}//获知该内存块的访问次数
        int getBlockId() const {return block_id;}//获知该虚拟页对应的内存块的ID
        void modifing() {modify= true;}//发生修改
        void visit() {vis_time++;}//对该虚拟页进行访问
        void setBlockId(int block) {block_id = block;}//为该虚拟页分配内存块
        void setInMemory() {exist_in_memory = true;}//将虚拟页的状态更改为存在内存中
        void releaseFromMemory() {exist_in_memory = false; modify = false;}//将虚拟页从内存中换出
    };

    class block{
    private:
        int id;
        int st_address;//内存块的起始地址
        bool opy;//内存被占用
    public:
        block(int id,int address,bool opied = false)
        :id(id),st_address(address), opy(opied) {}
        ~block() =default;
        int getStaddress() const {return st_address;};
        int getId() const {return id;};
        bool getOpied() const {return opy;};
        void release() {opy = false;};
        void allocate() {opy = true;};
    };

}
#endif //OS_MEMORY_H
