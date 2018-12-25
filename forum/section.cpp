#include "section.h"
#include"header.h"
Section::Section(string a,string b)
{
    title=a;
    moderatorName=b;
}
void Section::changeposts(int i)
{
    posts.push_back(i);
}
vector<int>Section:: getPosts()
{
    return posts;
}
string Section::getTitle()
{
    return title;
}
string Section::getModeratorName()
{
    return moderatorName;
}

void Section::deletePosts(int id)
{
    int i;
    for(i=0;i<posts.size();i++)
    {
        if(posts[i]==id)
        {
            vector<int>::iterator it =posts.begin()+i;
            posts.erase(it);
            break;
        }
    }
}

void Section::changeModerator(string a)
{
    moderatorName=a;
}
