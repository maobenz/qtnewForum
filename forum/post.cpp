#include "post.h"
#include "header.h"
Post::Post(string a,string b,string c,string d,int e)
{
    userName=a;
    title=b;
    contents=c;
    time=d;
    id=e;

}

string Post:: getContents()
{
    return contents;
}

string Post:: getTitle()
{
    return title;
}

string Post:: getuserName()
{
    return userName;
}

int Post::getID()
{
    return id;
}


void Post:: changeComments(int i)
{
    comments.push_back(i);
}
vector<int> Post::getComments()
{
    return comments;
}

string Post::getTime()
{
    return time;
}


void Post::deleteComments(int id)
{
    int i;
    for(i=0;i<comments.size();i++)
    {
        if(comments[i]==id)
        {
            vector<int>::iterator it =comments.begin()+i;
            comments.erase(it);
            break;
        }
    }
}
