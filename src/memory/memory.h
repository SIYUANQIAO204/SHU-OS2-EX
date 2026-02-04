//
// Created by qiao on 25-12-8.
//

#ifndef OS_MEMORY_H
#define OS_MEMORY_H
namespace memory{
    class VM{
    private:
        int st_address;
        int id;
        bool exist_in_memory;
        bool modify;
        int vis_time;
        int block_id;
    public:
        VM(int id, int address , bool exist= false, bool mod = false, int vis = 0, int block =-1)
        : id(id), st_address(address), exist_in_memory(exist), modify(mod), vis_time(vis), block_id(block) {}
        ~VM() = default;
        int getId() const {return id;}
        int getStaddress() const {return st_address;}
        bool getModifyStatus() const {return modify;}
        bool getExistStatus() const {return exist_in_memory;}
        int getVisitTime() const {return vis_time;}
        int getBlockId() const {return block_id;}
        void modifing() {modify= true;}
        void visit() {vis_time++;}
        void setBlockId(int block) {block_id = block;}
        void setInMemory() {exist_in_memory = true;}
        void releaseFromMemory() {exist_in_memory = false; modify = false;}
    };

    class block{
    private:
        int id;
        int st_address;
        bool opy;
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
