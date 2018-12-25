#ifndef POST_H
#define POST_H
#include "header.h"
#include "string.h"
class Post
{
public:
    Post(string a,string b,string c,string d,int e);
    string getContents();
    string getTitle();  //返回标题
    string getTime();   //返回时间
    void changeComments(int i);  //增加评论
    string getuserName();   //获取用户名
    int getID();  //获取用户ID
    vector<int> getComments();  //获取评论
    void deleteComments(int id);   //删除评论
private:
    int id;
    string userName;
    string time;
    string title;
    string contents;
    vector<int> comments;
};

#endif // POST_H
