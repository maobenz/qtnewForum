#ifndef ORDINARYUSER_H
#define ORDINARYUSER_H
#include "header.h"
//#include <user.h>
class User      //用户
{
public:
    User(string a,string b,string c,string d);
    void getInfor(string&a,string&b);
    string getId();   //返回ID
    string getuserName();  //返回用户名
    string getpassword();  //返回密码
    string getLastOnlineTime();    //返回最后一次在线时间
    void changeuserName(string a);   //改变用户名
    void changepassword(string a);   //改变密码
    void changeID(string a);   //改变ID
    virtual void deletePosts(int id);
    int entryUser(string a,string b);    //进入系统判断
    void outUser();  //系统登出
    void Online();   //系统登录
     void changeCondition(int i);   //改变状态
     void changeLastOnlineTime(string a);   //改变最后一次登录时间
     bool getOnline();    //返回在线状态


private:
    string id;
    string userName;
    string password;
    string lastonlineTime;
    bool online;
};

class Anonymoususer : public User
{
public:
    Anonymoususer(string a,string b,string c,string d):User(a,b,c,d)
    {}
    void deletePosts(int id);

};

class Ordinaryuser : public User    //普通用户
{
public:
    Ordinaryuser(string a,string b,string c,string d):User(a,b,c,d)
    {}
    void addPosts(int i);
    void addComments(int i);
    void changeComments(vector<int> m);
    void changePosts(vector<int> m);
    void deletePosts(int id);
    virtual void deleteComments(int id);
    vector<int> getPostId();
    vector<int> getCommentId();
    int getLevel();
    void changeLevel(int i);
    int getAccusationtimes();
    void addAccusationtimes(int i);
    void getUserInfo();
private:
    vector<int> PostId;
    vector<int> CommentId;
    int level;
    int accusationtimes;
};




class Administrator : public User   //管理员
{
    public:
        Administrator(string a,string b,string c,string d):User(a,b,c,d)
         {}
};

class Moderator : public Ordinaryuser    //版主
{
public:
    Moderator(string a,string b,string c,string d):Ordinaryuser(a,b,c,d)
      {}
    void changeSection(int i);
    int getSection();
private:
    int section;   //板块号;
    vector<int> PostId;
    vector<int> CommentId;


};

#endif // ORDINARYUSER_H
