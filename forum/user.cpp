#include "user.h"
#include "header.h"
User:: User(string a,string b,string c,string d)
{
    id=a;
    userName=b;
    password=c;
    lastonlineTime=d;
    online=false;
}

string User::getId()
{
    return id;
}

string User::getuserName()
{
    return userName;
}

string User::getpassword()
{
    return password;
}


int User::entryUser(string a,string b)
{
    if(a==userName&&b==password)
        return 1;
    else if(a==userName&&b!=password)
        return 2;
    else return 0;
}

void User::outUser()   //登出操作
{
    online=false;
}

void User::deletePosts(int id)
{

}


void Ordinaryuser::addComments(int i)
{
    CommentId.push_back(i);
}

void Ordinaryuser::addPosts(int i)
{
    PostId.push_back(i);
}

void Ordinaryuser::deletePosts(int id)
{
    int i;
    for(i=0;i<PostId.size();i++)
    {
        if(PostId[i]==id)
        {
            vector<int>::iterator it =PostId.begin()+i;
            PostId.erase(it);
            break;
        }
    }
}


void Ordinaryuser::deleteComments(int id)
{
    int i;
    for(i=0;i<CommentId.size();i++)
    {
        if(CommentId[i]==id)
        {
            vector<int>::iterator it =CommentId.begin()+i;
            CommentId.erase(it);
            break;
        }
    }
}


void Ordinaryuser::changeComments(vector<int> m)
{
    int i;
    CommentId.clear();
    for(i=0;i<m.size();i++)
        CommentId.push_back(m[i]);
}



void Ordinaryuser::changePosts(vector<int> m)
{
    int i;
    PostId.clear();
    for(i=0;i<m.size();i++)
        PostId.push_back(m[i]);
}


vector<int> Ordinaryuser::getPostId()
{
    return PostId;
}

vector<int> Ordinaryuser::getCommentId()
{
    return CommentId;
}


int Ordinaryuser::getLevel()
{
    return level;
}

void Ordinaryuser::changeLevel(int i)
{
    level=i;
}


int Ordinaryuser::getAccusationtimes()
{
    return accusationtimes;
}

void Ordinaryuser::addAccusationtimes(int i)
{
    accusationtimes=i;
}


void Moderator::changeSection(int i)
{
    section=i;
}

int Moderator::getSection()
{
    return section;
}

void User::changeCondition(int i)   //改变用户状态
{
    if(i==1)
    {
        online=true;
    }
    else online=false;

}

void User::changeuserName(string a)
{
    userName=a;
}

void User::changepassword(string a)
{
    password=a;
}

void User::changeID(string a)
{
    id=a;
}

void User::changeLastOnlineTime(string a)
{
    lastonlineTime=a;
}

string User::getLastOnlineTime()
{
    return lastonlineTime;
}

void User::Online()
{
    online=true;
}

bool User::getOnline()
{
    return online;
}

void User::getInfor(string&a,string&b)
{
    a=userName;
    b=id;
}


void Anonymoususer::deletePosts(int id)
{

}




