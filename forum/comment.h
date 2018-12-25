#ifndef COMMENT_H
#define COMMENT_H
#include "header.h"

class Comment
{
public:
    Comment(string a,string b,string c,int d);
    string getuserName();   //返回用户名
    string getContents(); //返回内容
    string getTime();  //返回时间
    int getID(); //返回ID
private:
    int id;
    string userName;
    string content;
    string time;
};

#endif // COMMENT_H
