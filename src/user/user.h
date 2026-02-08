
//
// Created by qiao on 25-12-25.
//
/*
 写了三种用户类型，不过由于时间限制并没有给对应的访问权限做限制
 进入系统默认为Guest，需要进行登陆，给用户组预留了一定的接口
 可以在创建用户时设置主文件夹的用户路径
 */


#ifndef OS_USER_H
#define OS_USER_H
#pragma once
#include <utility>
#include "../file/inode.h"
#include "string"
#include "iostream"
namespace user {

    enum class UserClass{
        Administer,
        User,
        Guest
    };

    class user {
    private:
        int uid;
        std::string userName;
        int gid;
        std::string homeDir;
        UserClass Class;
        std::string password;
    public:
        user(int id, std::string name, std::string pass, UserClass permission, std::string dir = "" , int group =0):
                uid(id), userName(name), password(std::move(pass)), Class(permission), gid(group) { homeDir = dir+name;}
        ~user() = default;
        void setGroup(int group) {gid = group;}
        void changePremission(UserClass premission) { Class = premission;}
        int getUid() const {return uid;}
        int getGid() const {return gid;}
        std::string getHomeDir() const {return homeDir;}
        bool checkPasswd(const std::string& input) const {return input == password;}
        void changePasswd(std::string newPassWd) {password = newPassWd;}
        std::string getName() const {return userName;}
        bool checkPremission(file::Permission premission, int owner)//不同的用户拥有不同的权限，文件权限定义在file.h中
        {
            if(premission == file::Permission::PUBLIC) return true;
            else if(premission == file::Permission::PRIVATE)
            {
                if(uid == owner || Class == UserClass::Administer) return true;
                else return false;
            }
            else{
                if(Class == UserClass::Administer) return true;
                else return false;
            }
        }
        void changename(const std::string& newname) { userName = newname; homeDir = newname;}
        bool checkName(const std::string& input) {return input == userName;}
        void showInfo() const{
            std::cout<<"Name : "<<userName<<'\n'<<"Class : ";
            if(Class == UserClass::Administer) std::cout<<"Administer\n";
            else if(Class == UserClass::User) std::cout<<"User\n";
            else if(Class == UserClass::Guest) std::cout<<"Guest\n";
            else std::cout<<"Unknown\n";
            std::cout<<"Uid is : "<<uid;
            std::cout<<"\nGroup id is : "<<gid<<'\n';
        }
    };
}

#endif //OS_USER_H

