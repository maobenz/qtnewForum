#ifndef SECTION_H
#define SECTION_H
#include"header.h"
#include"post.h"
class Section
{
public:
    Section(string a,string b);   //初始化
    void changeposts(int i);    //增加帖子
    vector<int> getPosts();  //返回帖子id
    string getTitle();  //返回标题
    string getModeratorName();   //返回版主用户名
    void deletePosts(int id);   //删除帖子
    void changeModerator(string a);  //改变版主
private:
    string title;
    vector<int>posts;
    string moderatorName;

};

#endif // SECTION_H



