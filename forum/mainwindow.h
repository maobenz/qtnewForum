#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>

#include<QPushButton>
#include<QLineEdit>
#include<header.h>
#include<QRadioButton>
#include<QLabel>
#include<QTextEdit>
#include<QTextCodec>
#include<QScrollArea>
#include<QWidget>
#include<QDialog>
#include<QHBoxLayout>
#include<user.h>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void defaultUserTime();   //配置起始时间
    void buildnewDatebase();
    void initializenewDatabase();
    void builduserDatabase();
    void insertDatabase();
    void insertanonylousDatabase(string id,string name,string password,string time);
    void insertmoderatorDatabase(string id,string name,string password,string time,int level,
                                 int accusationtimes,int section);
    void insertordinaryuserDatabase(string id,string name,
             string password,string time,int level,int accusationtimes);

    void deleteordinaryuserDatabase(string id);
    void deletemoderatorDatabase(string id);


    void examineanonylousDatabase();
    //void initializeForum();     //初始化论坛
    void initializeNewForum();    //另一种初始化
    int ifconform(string a,string b);   //判断用户名密码是否正确，以及判断是哪种用户类型输入
    void startForum();   //开始界面创造
    bool ifrepeat(string userName);   //判断用户名是否重复
    void mapProduce();   //初始化结束之后创建用户帖子评论之间的对应关系
    void produceNewUser(string a,string b);  //产生新用户
    void produceNewAnonymous(string a);   //产生新的匿名用户
    void enterForum();    //返回起始界面
    void showComments(int index);   //显示评论内容
    void showUsers();   //显示用户信息
    void addcomments(QString str);   //增加评论内容
    void showModeratorName();    //显示论坛名称  C++学习论坛
    void addPosts(QString content,QString title);   //增加帖子
    void showPosts();    //显示帖子到界面上
    int getPostsIndex(int id);    //得到帖子的索引
    int getCommentsIndex(int id);   //得到评论的索引
    void deleteComments(int index);   //删除评论
    void deletePosts(int index);   //删除帖子
    void hidecommentandpost();   //隐藏帖子评论
    void changeModerator(string s);   //改变版主
    int sumOnline();

    void examinePostdatabase();
    void examineCommentdatabase();
    void examineSectiondatabase();

    void addcommentdatabase(int id,string name, string time,string content);

    void addpostdatabase(int id,string name, string time,string title,string content);

    void changeModeratorDatabase(string id1,string id2);//改变版主数据库

    void deletepostdatabase(int id);
    void deletecommentdatabase(int id);

    void deleteUserComments(int index) ;//删除用户类下的评论id

    void errorfile();

     void closeEvent(QCloseEvent *e);


private:
    QSqlDatabase database;
    //QSqlQuery sql_query;


    vector<class Administrator> administrators;   //管理员类vector
    vector<class Ordinaryuser> ordinaryusers;  //普通用户类vector
    vector<class Moderator> moderators;   //版主类vector
    vector<class Anonymoususer> anonymoususers;    //匿名用户类
    vector<class Section> sections;   //板块类vector
    vector<class Post> posts;   //帖子类vector
    vector<class Comment> comments;   //帖子类vector


    vector<QPushButton*>postbuttons;       //帖子类按钮
    vector<QPushButton*>postbuttonsDelete;       //帖子删除类按钮
    vector<QLabel*>commentbuttons;         //评论类label
    vector<QPushButton*>commentbuttonsDelete;   //评论删除类按钮
    vector<QPushButton*>commentAccuse;
    QScrollArea*area;   //滚动区
    QWidget*paint;    //画布


    //Ui::MainWindow *ui;
    QPushButton *button1;   // 登录按钮
    QPushButton *button2;   //注册按钮
    QPushButton *button3;   //注册结束确定按钮

    QPushButton *button5;   // 5 6 7 是三个板块按钮
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;   //帖子提交
    QPushButton *button9;   //注销按钮
    QPushButton *button10;   //更换版主操作
    QPushButton *button11;   //评论提交
    QPushButton *button12;   //显示用户详细信息



    QLineEdit* line1;   //输入用户名的输入行
    QLineEdit* line2;    //输入密码的输入行
    QRadioButton *button4;   //选中管理员登录按钮
    QRadioButton *anonymousIn;
    QRadioButton *ordinaryuserIn;
    QLabel*q1;
    QLabel*q2;
    QLabel* moderatorName; // 论坛名称  C++学习论坛
    QLabel*commentshow;  //评论显示
    QPalette pe;
    QTextCodec *codec;

    QLabel*userNameInput;
    QLabel*passwordInput;

    QLabel*userName;  //用户名字
    QLabel*Id;   //ID号
    QLabel*userkindpic;   //用户种类

    QLabel*PostUp;
    QLabel*PostContentShow;
    QLabel*PostTimeShow;



    QLabel*postwindow;   //这个就是帖子的label
    QLabel*postTime;   //帖子的时间
    QLabel*postId;     //贴子的ID
    QTextEdit*writePost;   //这个就是输入框
    QTextEdit*writeComment;  //写新的评论
    QLineEdit*titleinsert;   //输入标题


    QDialog*dialog;
    QDialog* showUserInformation;

    //dialog*dia;
    QLineEdit*linenewmoderator;
    QPushButton*changemoderator;

    QDialog*errorinfo;
    QPushButton*errorConfirm;

    QIcon icon;   //照片

    QHBoxLayout *layout;

    int userkind;   //记录当前登陆的用户是哪种类型，1代表普通用户，2代表版主，0代表管理员;
    int num;    //记录当前用户索引
    int postnum;       //用户正在观看哪个帖子
    int sectionnum;   //用户正在观看哪个版块
    int deletePostID;
    int deleteCommentID;

    bool error;




public slots:
    void ClickButton1(); //按钮定义的关联函数
    void ClickButton2();
    void ClickButton3();
    void ClickButton5();
    void ClickButton6();
    void ClickButton7();
    void ClickButton8();
    void ClickButton9();
    void ClickButton10();
    void ClickButton11();
    void ClickButton12();   //更换版主操作
    void ClickButton13();
    void ClickButton14();   //个人信息说明
    void ClickButton15();   //举报操作

};

#endif // MAINWINDOW_H
