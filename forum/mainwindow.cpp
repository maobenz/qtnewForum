#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{

    int i,j,k;
    int id;
    string s[5];
    string ss;
    QString str;
    error=false;

    initializeNewForum();

    //首先初始化数据库

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("XingYeZhiXia");
        database.setPassword("123456");
    }



    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {

    }

    //buildnewDatebase();
    //builduserDatabase();
    //insertDatabase();
    initializenewDatabase();
    insertDatabase();

    //examinePostdatabase();
    //examineCommentdatabase();


    //initializeForum();
    button1 = new QPushButton("登陆", this);
    button2= new QPushButton("注册", this);
    button3= new QPushButton("确定", this);
    button4= new QRadioButton("管理员",this);
    anonymousIn=new QRadioButton("匿名用户",this);
    ordinaryuserIn=new QRadioButton("普通用户",this);


    button5=new QPushButton("C++语法学习",this);
    button6=new QPushButton("问题交流讨论",this);
    button7=new QPushButton("优秀代码展示",this);


    button5->setVisible(false);
    button6->setVisible(false);
    button7->setVisible(false);



    button9=new QPushButton("注销",this);
    button9->setVisible(false);
    line1= new QLineEdit(this);
    line2= new QLineEdit(this);

    passwordInput=new QLabel("密码:",this);

    userNameInput=new QLabel("用户名:",this);
    passwordInput->setVisible(true);
    userNameInput->setVisible(true);

    button3->setVisible(false);
    connect(button1, SIGNAL(clicked()), this, SLOT(ClickButton1()));
    connect(button2, SIGNAL(clicked()), this, SLOT(ClickButton2()));
    connect(button3, SIGNAL(clicked()), this, SLOT(ClickButton3()));
    connect(button9, SIGNAL(clicked()), this, SLOT(ClickButton9()));



    writePost=new QTextEdit(this);
    writePost->setVisible(false);


    writeComment=new QTextEdit(this);
    writeComment->setVisible(false);

    area=new QScrollArea(this);
    area->setVisible(false);
    paint=new QWidget(area);
    area->setWidget(paint);

    postwindow=new QLabel(paint);
    postTime=new QLabel(paint);
    commentshow=new QLabel(paint);

    PostUp=new QLabel(paint);
    PostContentShow=new QLabel(paint);
    PostTimeShow=new QLabel(paint);

    button8=new QPushButton("提交",this);
    button8->setGeometry(2200,1000,100,50);
    button8->setVisible(false);
    connect(button8, SIGNAL(clicked()), this, SLOT(ClickButton8()));

    button11=new QPushButton("提交",this);
    button11->setGeometry(2200,1000,100,50);
    button11->setVisible(false);
    connect(button11, SIGNAL(clicked()), this, SLOT(ClickButton7()));

    button10=new QPushButton("更换",this);
     connect(button10, SIGNAL(clicked()), this, SLOT(ClickButton12()));
     button10->setVisible(false);

     button12=new QPushButton("详细信息",this);
      connect(button12, SIGNAL(clicked()), this, SLOT(ClickButton14()));
      button12->setVisible(false);

    titleinsert=new QLineEdit(this);
    titleinsert->setGeometry(500,900,1700,100);
    titleinsert->setVisible(false);

    moderatorName=new QLabel(this);


     dialog=new QDialog();
     dialog->setVisible(false);
     linenewmoderator=new QLineEdit(dialog);
     linenewmoderator->setVisible(false);
     linenewmoderator->setGeometry(50,10,100,50);
     changemoderator=new QPushButton("确定",dialog);
     changemoderator->setGeometry(120,70,50,50);
     dialog->setFixedSize(300,150);

     /*

     errorinfo=new QDialog();
     errorinfo->setVisible(false);
     errorConfirm=new QPushButton("确定",dialog);
     errorConfirm->setGeometry(120,70,50,50);
     errorinfo->setFixedSize(300,150);
     */



     connect(changemoderator, SIGNAL(clicked()), this, SLOT(ClickButton13()));
     //connect(errorConfirm, SIGNAL(clicked()), this, SLOT(closeEvent(QCloseEvent *e)));



     QPixmap pixmap("C:\\Users\\63176\\Documents\\forum\\sky2.jpg");
     QPalette palette=this->palette();
     palette.setBrush(QPalette::Background,QBrush(pixmap));
     this->setPalette(palette);




    writeComment ->setStyleSheet("background-color: rgb(255, 255, 255, 60);");
    writePost ->setStyleSheet("background-color: rgb(255, 255, 255, 60);");
     titleinsert->setStyleSheet("background-color: rgb(255, 255, 255, 60);");
     paint->setStyleSheet("background-color: rgb(255, 255, 255, 60);");
     area->setStyleSheet("background-color: rgb(255, 255, 255, 60);");



     line1->setGeometry(600,300,300,50);
     line2->setGeometry(600,400,300,50);
     button1->setGeometry(700,600,100,50);
     button2->setGeometry(700,700,100,50);
     button3->setGeometry(700,600,100,50);
     button4->setGeometry(1000,600,200,50);
     anonymousIn->setGeometry(1000,700,200,50);
     ordinaryuserIn->setGeometry(1000,500,200,50);

     button5->setGeometry(20,500,300,50);
     button6->setGeometry(20,600,300,50);
     button7->setGeometry(20,700,300,50);

     passwordInput->setGeometry(550,400,50,50);
     userNameInput->setGeometry(550,300,50,50);
     writePost->setGeometry(500,1000,1700,400);
     writeComment->setGeometry(500,1000,1700,400);

     button8->setGeometry(2200,1000,100,50);  //提交按钮
     button10->setGeometry(550,200,50,50);    //更换版主按钮
     button11->setGeometry(2200,1000,100,50);  //提交按钮

     area->setGeometry(500,250,1700,660);

}

fstream & operator <<(fstream & os,class Section& c)
{
    int i;
    int n=-1;
    os<<c.getTitle()<<endl;
    os<<c.getModeratorName()<<endl;
    for(i=0;i<c.getPosts().size();i++)
    {
        os<<c.getPosts()[i]<<" ";
    }
    os<<n<<endl<<endl;
}

fstream & operator <<(fstream & os,class Comment& c)
{
    os<<c.getID()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getContents()<<'#'<<endl;
    os<<c.getTime()<<endl<<endl;
}

fstream & operator <<(fstream & os,class Post& c)
{
    int i;
    int n=-1;
    os<<c.getID()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getTitle()<<endl;
    os<<c.getContents()<<'#'<<endl;
    os<<c.getTime()<<endl;
    for(i=0;i<c.getComments().size();i++)
    {
        os<<c.getComments()[i]<<" ";
    }
    os<<n<<endl<<endl;
}

fstream & operator <<(fstream & os,class Administrator& c)
{
    os<<c.getId()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getpassword()<<endl;
    os<<c.getLastOnlineTime()<<endl<<endl;
}


fstream & operator <<(fstream & os,class Anonymoususer & c)
{
    os<<c.getId()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getpassword()<<endl;
    os<<c.getLastOnlineTime()<<endl<<endl;
}

fstream & operator <<(fstream & os,class Ordinaryuser& c)
{
    int i;
    string s1,s2,s3;
    int n=-1;
    os<<c.getId()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getpassword()<<endl;
    os<<c.getLastOnlineTime()<<endl;
    os<<c.getLevel()<<endl;
    os<<c.getAccusationtimes()<<endl;
    for(i=0;i<c.getPostId().size();i++)
    {
        os<<c.getPostId()[i]<<" ";
    }
    os<<n<<endl;
    for(i=0;i<c.getCommentId().size();i++)
    {
         os<<c.getCommentId()[i]<<" ";
    }
    os<<n<<endl<<endl;
    return os;
}

fstream & operator <<(fstream & os,class Moderator& c)
{
    int i;
    string s1,s2,s3;
    int n;
    n=-1;
    os<<c.getId()<<endl;
    os<<c.getuserName()<<endl;
    os<<c.getpassword()<<endl;
    os<<c.getLastOnlineTime()<<endl;
    os<<c.getLevel()<<endl;
    os<<c.getAccusationtimes()<<endl;
    for(i=0;i<c.getPostId().size();i++)
    {
        os<<c.getPostId()[i]<<" ";
    }
    os<<n<<endl;
    for(i=0;i<c.getCommentId().size();i++)
    {
          os<<c.getCommentId()[i]<<" ";
    }
    os<<n<<endl;
    os<<c.getSection()<<endl<<endl;
    return os;
}


ifstream& operator >>(ifstream & os,class Ordinaryuser *& c)
{
    string s1,s2,s3,s4;
    int n1,n2;
    string s5,s6;
    string ss;
    int i,j;
    int pos;
    char ch;
    os>>s1>>s2>>s3>>s4;
    c=new Ordinaryuser(s1,s2,s3,s4);
    os>>n1;
    os>>n2;
    c->changeLevel(n1);
    c->addAccusationtimes(n2);
    pos=0;
    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->addPosts(n1);
   }

    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->addComments(n1);
    }

    return os;
}


ifstream& operator >>(ifstream & os,class Administrator *& c)
{
    string s1,s2,s3,s4;
    os>>s1>>s2>>s3>>s4;
    c=new Administrator(s1,s2,s3,s4);
    return os;
}

ifstream& operator >>(ifstream & os,class Anonymoususer *& c)
{
    string s1,s2,s3,s4;
    os>>s1>>s2>>s3>>s4;
    c=new Anonymoususer(s1,s2,s3,s4);
    return os;
}



ifstream& operator >>(ifstream & os,class Moderator *& c)
{
    string s1,s2,s3,s4;
    int i,n1,n2;
    os>>s1>>s2>>s3>>s4;
    c=new Moderator(s1,s2,s3,s4);
    os>>n1;
    os>>n2;
    c->changeLevel(n1);
    c->addAccusationtimes(n2);
    char ch;
    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->addPosts(n1);
   }

    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->addComments(n1);
    }

    os>>n1;
    c->changeSection(n1);
    return os;
}

ifstream& operator >>(ifstream & os,class Section *& c)
{
    string s1,s2;
    int n1,n2;
    os>>s1>>s2;
    c=new Section(s1,s2);
    char ch;
    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->changeposts(n1);
    }
}

ifstream& operator >>(ifstream & os,class Post *& c)
{
    string s1,s2,s3,s4;
    string ss;
    char ch;
    int n1,n2;
    os>>n1;
    os>>s1>>s2;
    //os>>ss;
    //cout<<ss<<"tt"<<endl;
    /*
    while(ss[0]!='#')
    {
        s3+=ss;
        os>>ss;
    }
    cout<<s3<<"uu"<<endl;
    */


    int sum=0;
    ch=os.get();
    ch=os.get();
    while(ch!='#')
    {
        s3+=ch;
        ch=os.get();
    }
    os>>s4;
    c=new Post(s1,s2,s3,s4,n1);
    while(1)
    {
        os>>n1;
        if(n1==-1)
            break;
        c->changeComments(n1);
    }
}

ifstream& operator >>(ifstream & os,class Comment *& c)
{
    string s1,s2,s3;
    char ch;
    int n1;
    os>>n1;
    os>>s1;
    ch=os.get();
    ch=os.get();
    while(ch!='#')
    {
        s2+=ch;
        ch=os.get();
    }
    os>>s3;
    c=new Comment(s1,s2,s3,n1);
}


void MainWindow::initializeNewForum()  //另一种初始化
{
    string s1,s2,s3;
    int n,m;
    int i;
    string s;
    ifstream file;
    string ss;

    file.open("administrator.txt",ios::in);
    if (file.is_open())
    {
        getline(file,ss);
        file>>n;
        for(i=0;i<n;i++)
        {
            Administrator*m;
            file >>m;
            administrators.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }


    file.open("ordinaryuser.txt",ios::in);
    if (file.is_open())
    {
        getline(file,ss);
        file>>n;
        for(i=0;i<n;i++)
        {
            Ordinaryuser*m;
            file >>m;
            ordinaryusers.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

    file.open("moderator.txt",ios::in);
    if (file.is_open())
    {
        getline(file,ss);
        file>>n;
        for(i=0;i<n;i++)
        {
            Moderator*m;
            file >>m;
            moderators.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

    file.open("anonylous.txt",ios::in);
    if (file.is_open())
    {
        getline(file,ss);
        file>>n;
        for(i=0;i<n;i++)
        {
            Anonymoususer*m;
            file >>m;
            anonymoususers.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

    file.open("posts.txt",ios::in);
    if (file.is_open())
    {
        file>>n;
        for(i=0;i<n;i++)
        {
            Post*m;
            file >>m;
            posts.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

    file.open("comments.txt",ios::in);
    if (file.is_open())
    {
        file>>n;
        for(i=0;i<n;i++)
        {
            Comment*m;
            file >>m;
            comments.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

    file.open("sections.txt",ios::in);
    if (file.is_open())
    {
        file>>n;
        for(i=0;i<n;i++)
        {
            Section*m;
            file >>m;
            sections.push_back(*m);
        }
        file.close();
    }
    else
    {
        cout<<"error happen"<<endl;
        errorfile();
    }

}

void MainWindow::errorfile()
{
    error=true;
    QLabel*text=new QLabel("没有找到相应的文件,请重新打开程序");
    text->setFixedSize(500,350);
    text->setVisible(true);
}



void MainWindow::initializenewDatabase()
{
    QSqlQuery sql_query;
    QString insert_sql;
    int i;
    QString str;


    QString clear_sql = "delete from ordinaryuser";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }


    clear_sql = "delete from administrator";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    clear_sql = "delete from moderator";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    clear_sql = "delete from anonymoususer";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    clear_sql = "delete from Comment";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }
    /*
    clear_sql = "delete from Post";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    clear_sql = "delete from Comment";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    clear_sql = "delete from Section";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }
    */


    //接下来是插入操作

    for(i=0;i<ordinaryusers.size();i++)
    {
        insert_sql = "insert into ordinaryuser values (?, ?, ?,?,?,?)";
        sql_query.prepare(insert_sql);
        str=QString::fromStdString(ordinaryusers[i].getId());
        sql_query.addBindValue(str);
        str=QString::fromStdString(ordinaryusers[i].getuserName());
        sql_query.addBindValue(str);
        str=QString::fromStdString(ordinaryusers[i].getpassword());
        sql_query.addBindValue(str);
        str=QString::fromStdString(ordinaryusers[i].getLastOnlineTime());
        sql_query.addBindValue(str);
        sql_query.addBindValue(ordinaryusers[i].getLevel());
        sql_query.addBindValue(ordinaryusers[i].getAccusationtimes());
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted ordinaryuser!";
        }
    }

    for(i=0;i<moderators.size();i++)
    {
         insert_sql = "insert into moderator values (?,?,?,?,?,?,?)";
         sql_query.prepare(insert_sql);
         str=QString::fromStdString(moderators[i].getId());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getuserName());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getpassword());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getLastOnlineTime());
         sql_query.addBindValue(str);
         sql_query.addBindValue(moderators[i].getLevel());
         sql_query.addBindValue(moderators[i].getAccusationtimes());
         sql_query.addBindValue(moderators[i].getSection());

         if(!sql_query.exec())
         {
             qDebug() << sql_query.lastError();
         }
         else
         {
             qDebug() << "inserted moderator!";
         }
    }

    for(i=0;i<anonymoususers.size();i++)
    {
        insert_sql = "insert into anonymoususer values (?, ?, ?,?)";
        sql_query.prepare(insert_sql);
        str=QString::fromStdString(anonymoususers[i].getId());
        sql_query.addBindValue(str);
        str=QString::fromStdString(anonymoususers[i].getuserName());
        sql_query.addBindValue(str);
        str=QString::fromStdString(anonymoususers[i].getpassword());
        sql_query.addBindValue(str);
        str=QString::fromStdString(anonymoususers[i].getLastOnlineTime());
        sql_query.addBindValue(str);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted anonymoususer!";
        }
    }



    for(i=0;i<comments.size();i++)
    {
        insert_sql = "insert into Comment values (?,?,?,?)";
        QString str;
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(comments[i].getID());
        str=QString::fromLocal8Bit(comments[i].getuserName().data());
        sql_query.addBindValue(str);
        str=QString::fromLocal8Bit(comments[i].getTime().data());
        sql_query.addBindValue(str);
        str=QString::fromLocal8Bit(comments[i].getContents().data());
        sql_query.addBindValue(str);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted comment!";
        }
    }
    examineCommentdatabase();



}




void MainWindow::insertDatabase()
{


    QSqlQuery sql_query;
    QString insert_sql;
    int i;
    QString str;
    QString select_all_sql;
    /*

    select_all_sql = "select * from administrator";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString  id= sql_query.value(0).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lasttime = sql_query.value(3).toString();
            qDebug()<<QString("id:%1    name:%2    password:%3     lasttime:%4" ).arg(id)
                      .arg(name).arg(password).arg(lasttime);
        }
    }
    cout<<"ee"<<endl;
    */






    select_all_sql = "select * from ordinaryuser";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {

            QString id = sql_query.value(0).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lastonlineTime = sql_query.value(3).toString();
            int level = sql_query.value(4).toInt();
            int accusationtimes = sql_query.value(5).toInt();
            qDebug()<<QString("id:%1    name:%2    password:%3   "
                              " lastonlineTime:%4   level:%5   accusationtimes:%6  "
                              ).arg(id)
                      .arg(name).arg(password).arg(lastonlineTime).arg(level).
                      arg(accusationtimes);
        }
    }


    select_all_sql = "select * from moderator";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {

            QString id = sql_query.value(0).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lastonlineTime = sql_query.value(3).toString();
            int level = sql_query.value(4).toInt();
            int accusationtimes = sql_query.value(5).toInt();
            int section=sql_query.value(6).toInt();
            qDebug()<<QString("id:%1    name:%2    password:%3   "
                              " lastonlineTime:%4   level:%5   accusationtimes:%6  "
                              "section:%7"
                              ).arg(id)
                      .arg(name).arg(password).arg(lastonlineTime).arg(level).
                      arg(accusationtimes).arg(section);
        }
    }




    /*
    select_all_sql = "select * from moderator";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {

            QString id = sql_query.value(0).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lastonlineTime = sql_query.value(3).toString();
            int level = sql_query.value(4).toInt();
            int accusationtimes = sql_query.value(5).toInt();
            int section = sql_query.value(6).toInt();
            qDebug()<<QString("id:%1    name:%2    password:%3   "
                              " lastonlineTime:%4   level:%5   accusationtimes:%6  "
                              " section:%7").arg(id)
                      .arg(name).arg(password).arg(lastonlineTime).arg(level).
                      arg(accusationtimes).arg(section);

        }
    }
    cout<<"uu"<<endl;


    select_all_sql = "select * from anonymoususer";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {


            QString  id= sql_query.value(0).toString();
            //QString Title = sql_query.value(3).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lasttime = sql_query.value(3).toString();


            qDebug()<<QString("id:%1    name:%2    password:%3     lasttime:%4" ).arg(id)
                      .arg(name).arg(password).arg(lasttime);
        }
    }
    cout<<endl;
    */








    /*
    QString clear_sql = "delete from ordinaryuser";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }
    */


    /*
    for(i=0;i<moderators.size();i++)
    {
     QString delete_sql = "delete from moderator where id = ?";
     sql_query.prepare(delete_sql);
     str=QString::fromStdString(moderators[i].getId().data());
     //str=QString::fromLocal8Bit(moderators[i].getId().data());
     sql_query.addBindValue(str);
     if(!sql_query.exec())
     {
         qDebug()<<sql_query.lastError();
     }
     else
     {
         qDebug()<<"deleted!";
     }
    }

    //cout<<moderators.size()<<"tt"<<endl;
    for(i=0;i<moderators.size();i++)
    {
         insert_sql = "insert into moderator values (?,?,?,?,?,?,?)";
         sql_query.prepare(insert_sql);
         str=QString::fromStdString(moderators[i].getId());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getuserName());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getpassword());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getLastOnlineTime());
         sql_query.addBindValue(str);
         sql_query.addBindValue(modersators[i].getLevel());
         sql_query.addBindValue(moderators[i].getAccusationtimes());
         sql_query.addBindValue(moderators[i].getSection());

         if(!sql_query.exec())
         {
             qDebug() << sql_query.lastError();
         }
         else
         {
             qDebug() << "inserted ok!";
         }
    }
    */



    /*
    QString create_sql = "create table ordinaryuser (id QString primary key,
                                        name QString, password QString,"
                         " lastonlineTime QString, level int, accusationtimes int )";
                         */

}

void MainWindow::buildnewDatebase()
{
    QSqlQuery sql_query;
    QString insert_sql;
    int i;
    QString str;

    QString create_sql = "create table ordinaryuser (id varchar(30) primary key, name varchar(30), password varchar(30),"
                         " lastonlineTime varchar(30), level int, accusationtimes int )";
    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
    }
    else
    {
        qDebug() << "Table ordinaryuser created!";
    }



      create_sql = "create table administrator (id  varchar(30) primary key, name varchar(30), password varchar(30),"
                            " lastonlineTime varchar(30) )";
       sql_query.prepare(create_sql);
       if(!sql_query.exec())
       {
           qDebug() << "Error: Fail to create table." << sql_query.lastError();
       }
       else
       {
           qDebug() << "Table administrator created!";
       }

       create_sql =  "create table moderator (id varchar(30) primary key, name varchar(30), password varchar(30),"
                     " lastonlineTime varchar(30), level int, accusationtimes int, section int)";
          sql_query.prepare(create_sql);
          if(!sql_query.exec())
          {
              qDebug() << "Error: Fail to create table." << sql_query.lastError();
          }
          else
          {
              qDebug() << "Table moderator created!";
          }

          create_sql =  "create table Post (id int primary key, userName varchar(30),"
                        " Time varchar(30), Title varchar(30), Content varchar(30))";
         sql_query.prepare(create_sql);
         if(!sql_query.exec())
         {
             qDebug() << "Error: Fail to create table." << sql_query.lastError();
         }
         else
         {
             qDebug() << "Table  Post created!";
         }

         create_sql =  "create table Comment (id int primary key, userName varchar(30),"
                       " Time varchar(30),  Content varchar(30))";
        sql_query.prepare(create_sql);
        if(!sql_query.exec())
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table Comment  created!";
        }

        create_sql =  "create table Section (title varchar(30),"
                      "   ModeratorName varchar(30))";
       sql_query.prepare(create_sql);
       if(!sql_query.exec())
       {
           qDebug() << "Error: Fail to create table." << sql_query.lastError();
       }
       else
       {
           qDebug() << "Table Section created!";
       }


}

void MainWindow::builduserDatabase()
{
    QSqlQuery sql_query;
    QString insert_sql;
    QString str;
    QString select_all_sql;
    int i;
    QString clear_sql = "delete from moderator";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }

    for(i=0;i<moderators.size();i++)
    {
         insert_sql = "insert into moderator values (?,?,?,?,?,?,?)";
         sql_query.prepare(insert_sql);
         str=QString::fromStdString(moderators[i].getId());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getuserName());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getpassword());
         sql_query.addBindValue(str);
         str=QString::fromStdString(moderators[i].getLastOnlineTime());
         sql_query.addBindValue(str);
         sql_query.addBindValue(moderators[i].getLevel());
         sql_query.addBindValue(moderators[i].getAccusationtimes());
         sql_query.addBindValue(moderators[i].getSection());

         if(!sql_query.exec())
         {
             qDebug() << sql_query.lastError();
         }
         else
         {
             qDebug() << "inserted ok!";
         }
    }

    clear_sql = "delete from ordinaryuser";
        sql_query.prepare(clear_sql);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "table cleared";
        }


        for(i=0;i<ordinaryusers.size();i++)
        {
             insert_sql = "insert into ordinaryuser values (?,?,?,?,?,?)";
             sql_query.prepare(insert_sql);
             str=QString::fromStdString(ordinaryusers[i].getId());
             sql_query.addBindValue(str);
             str=QString::fromStdString(ordinaryusers[i].getuserName());
             sql_query.addBindValue(str);
             str=QString::fromStdString(ordinaryusers[i].getpassword());
             sql_query.addBindValue(str);
             str=QString::fromStdString(ordinaryusers[i].getLastOnlineTime());
             sql_query.addBindValue(str);
             sql_query.addBindValue(ordinaryusers[i].getLevel());
             sql_query.addBindValue(ordinaryusers[i].getAccusationtimes());

             if(!sql_query.exec())
             {
                 qDebug() << sql_query.lastError();
             }
             else
             {
                 qDebug() << "inserted ok!";
             }
        }



}


void MainWindow::examinePostdatabase()
{
    QString str;
    QString select_all_sql;
    QSqlQuery sql_query;

    select_all_sql = "select * from Post";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int  id= sql_query.value(0).toInt();
            QString username = sql_query.value(1).toString();
            QString time = sql_query.value(2).toString();
            QString title = sql_query.value(3).toString();
            QString content = sql_query.value(4).toString();
            qDebug()<<QString("id:%1    username:%2    time:%3    title:%4     content:%5" ).arg(id)
                      .arg(username).arg(time).arg(title).arg(content);
        }
    }
    cout<<endl;
}


void MainWindow::examineCommentdatabase()
{
    QString str;
    QString select_all_sql;
    QSqlQuery sql_query;

    select_all_sql = "select * from Comment";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int  id= sql_query.value(0).toInt();
            QString username = sql_query.value(1).toString();
            QString time = sql_query.value(2).toString();
            QString content = sql_query.value(3).toString();
            qDebug()<<QString("id:%1    username:%2    time:%3     content:%4" ).arg(id)
                      .arg(username).arg(time).arg(content);
        }
    }
    cout<<endl;
}

void MainWindow::enterForum()
{
    moderatorName->setVisible(false);
    writePost->setVisible(false);
    writeComment->setVisible(false);

    line1->setVisible(true);
    line2->setVisible(true);
    button4->setVisible(true);
    anonymousIn->setVisible(true);
    ordinaryuserIn->setVisible(true);
    line1->clear();
    line2->clear();
    titleinsert->setVisible(false);

    if(userkind==0)
        administrators[num].outUser();
    else if(userkind==1)
        ordinaryusers[num].outUser();
    else if(userkind==2)
        moderators[num].outUser();
    hidecommentandpost();
    area->setVisible(false);
    if(commentshow)
    commentshow->setVisible(false);
    q1->setVisible(false);
    userName->setVisible(false);;  //用户名字
    Id->setVisible(false);;   //ID号
    userkindpic->setVisible(false);;   //用户种类

    button1->setVisible(true);
    button2->setVisible(true);
    button5->setVisible(false);
    button6->setVisible(false);
    button7->setVisible(false);
    button8->setVisible(false);
    button9->setVisible(false);
    button10->setVisible(false);
    button11->setVisible(false);
    button12->setVisible(false);

    passwordInput->setVisible(true);
    userNameInput->setVisible(true);

}



void MainWindow::ClickButton1()   //登录确定
{
    int i;
    QString nameUser = line1->text();
    QString password = line2->text();
    int result=ifconform(nameUser.toStdString(),password.toStdString());
    if(result==0)
    {
        if(userkind==0)
            administrators[num].Online();
        else if(userkind==1)
            ordinaryusers[num].Online();
        else if(userkind==2)
            moderators[num].Online();
        startForum();
    }
    else if(result==1)
    {
        QLabel*text=new QLabel("用户不存在");  //弹出提示框注册成功
        text->setFixedSize(300,100);
        text->setVisible(true);
        qDebug()<<"用户不存在"<<endl;    //弹出一个输入错误框，让用户重新输入
    }
    else if(result==2)
    {
        QLabel*text=new QLabel("输入密码错误");  //弹出提示框注册成功
        text->setFixedSize(300,100);
        text->setVisible(true);
        qDebug()<<"密码输入错误"<<endl;   //提示用户是密码输入错误
    }

}



void MainWindow::startForum()   //进入论坛
{

    button1->setVisible(false);
    button2->setVisible(false);
    button3->setVisible(false);
    button4->setVisible(false);
    anonymousIn->setVisible(false);
    ordinaryuserIn->setVisible(false);
    line1->setVisible(false);
    line2->setVisible(false);
    passwordInput->setVisible(false);
    userNameInput->setVisible(false);

    q1 =new QLabel(" <h1><<fontcolor=red>C++学习论坛欢迎您</font></h1>",this);
    QFont font ( "宋体" ,20, 75);
    q1->setFont(font);

    q1->setAlignment(Qt::AlignHCenter);
    q1->setVisible(true);
    q1->setGeometry(1000,100,1200,100);

    pe.setColor(QPalette::WindowText,Qt::red);
    q1->setPalette(pe);
    /*
    button5=new QPushButton("C++语法学习",this);
    button6=new QPushButton("问题交流讨论",this);
    button7=new QPushButton("优秀代码展示",this);

    button5->setGeometry(20,500,300,50);
    button6->setGeometry(20,600,300,50);
    button7->setGeometry(20,700,300,50);
    */

    button5->setVisible(true);
    button6->setVisible(true);
    button7->setVisible(true);
    button9->setVisible(true);

    button5->setObjectName(QString::number(0));
    button6->setObjectName(QString::number(1));
    button7->setObjectName(QString::number(2));
    connect(button5, SIGNAL(clicked()), this, SLOT(ClickButton5()));
    connect(button6, SIGNAL(clicked()), this, SLOT(ClickButton5()));
    connect(button7, SIGNAL(clicked()), this, SLOT(ClickButton5()));

    showUsers();

}


void MainWindow::showUsers()   //左上角显示用户信息
{
    string s,s1,s2,s3,s4;
    userName=new QLabel(this);
    Id=new QLabel(this);
    userkindpic=new QLabel(this);


    if(userkind==1)
    {
        ordinaryusers[num].getInfor(s3,s4);
        s1="UserName:"+s3;
        s2="Id:"+s4;
    }
    else if(userkind==0)
    {
        administrators[num].getInfor(s3,s4);
        s1="UserName:"+s3;
        s2="Id:"+s4;
    }
    else if(userkind==2)
    {
        moderators[num].getInfor(s3,s4);
        s1="UserName:"+s3;
        s2="Id:"+s4;
    }
    else if(userkind==3)
    {
        s1="anonymousUser";
        s2="Id:"+anonymoususers[num].getId();
    }


    QString str=QString::fromStdString(s1);
    userName->setText(str);
    userName->setGeometry(50,50,300,50);
    userName->setVisible(true);

    str=QString::fromStdString(s2);
    Id->setText(str);
    Id->setGeometry(50,100,300,50);
    Id->setVisible(true);

    s="userKind:";
    if(userkind==1)
    s+="ordinaryuser";
    else if(userkind==2)
    s+="medorater";
    else if(userkind==0)
    s+="administrator";
    else if(userkind==3)
    s+="anonymous";
    str=QString::fromStdString(s);
    userkindpic->setText(str);
    userkindpic->setGeometry(50,150,300,50);
    userkindpic->setVisible(true);

    button9->setGeometry(50,200,300,50);
    button12->setGeometry(50,300,300,50);
    button12->setVisible(true);





}

void MainWindow::ClickButton2()   //进入注册界面
{
    button1->setVisible(false);
    button2->setVisible(false);
    button3->setVisible(true);
}


void MainWindow::ClickButton5()   //进入某个板块下面
{

    //加上滚动界面
    int i;
    hidecommentandpost();
    //button8->setVisible(true);
    button11->setVisible(false);
    writeComment->setVisible(false);
    writePost->setVisible(true);
    titleinsert->setVisible(true);
    writePost->clear();
    titleinsert->clear();

    postwindow->setVisible(false);
    PostUp->setVisible(false);
    PostTimeShow->setVisible(false);
    postTime->setVisible(false);
    commentshow->setVisible(false);
    if(userkind!=0&&userkind!=3)
    button8->setVisible(true);

    //area->setGeometry(500,250,1700,660);
    area->setVisible(true);
    paint->setGeometry(0,0,1700,400);
    area->setWidget(paint);
   QObject *object = QObject::sender();
   QPushButton *push_button = qobject_cast<QPushButton *>(object);
   int index;
   if(push_button)
   {
       QString object_name = push_button->objectName();
       index = object_name.toInt();
   }
   sectionnum=index;   //记录当前版块号
   showModeratorName();
   postbuttons.clear();
   showPosts();
}

void MainWindow::ClickButton6()    //进入某个帖子下面
{
    int i;
    string s;
    titleinsert->setVisible(false);
    writePost->setVisible(false);
    hidecommentandpost();
    button8->setVisible(false);
    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);
    int index;
    if(push_button)
    {
        QString object_name = push_button->objectName();
        index = object_name.toInt();
    }
    int id;
    id=sections[sectionnum].getPosts()[index];
    postnum=getPostsIndex(id);    //记录当前帖子索引
    //首先放帖子内容
    QString str;


    postwindow->setGeometry(50,150,500,200);
    s+="UserName:"+posts[postnum].getuserName();
    s+="\n\nContent:"+posts[postnum].getContents();
    s+="\n----------------------------";
    str=QString::fromLocal8Bit(s.data());
    //str=QString::fromStdString(s);
    postwindow->setText(str);
    postwindow->setVisible(true);
    postwindow->setAlignment(Qt::AlignTop);
    PostUp->setStyleSheet("background-color:red");


    postTime->setGeometry(50,50,500,100);
    s="Time:"+posts[postnum].getTime();
    str=QString::fromLocal8Bit(s.data());
    //str=QString::fromStdString(s);
    postTime->setText(str);
    postTime->setVisible(true);
    postTime->setAlignment(Qt::AlignTop);

    //下面放评论

    showComments(postnum);
    writeComment->setVisible(true);
    writeComment->clear();

    if(userkind!=0&&userkind!=3)
    button11->setVisible(true);

}

void MainWindow::showModeratorName()
{
    string s;
    s="moderator:";
    s+=sections[sectionnum].getModeratorName();

    QString str=QString::fromStdString(s);
    moderatorName->setText(str);
    moderatorName->setGeometry(500,200,200,50);
    moderatorName->setVisible(true);

    button10->setGeometry(850,200,50,50);
    if(userkind==0)
    button10->setVisible(true);
}

void MainWindow::showComments(int index)  //显示评论
{
    int i;
    string s;
    QString str;
    int newindex;

    hidecommentandpost();
    paint->setGeometry(0,0,1000,400+(posts[index].getComments().size())*210);//设置画布大小

    commentshow->setText("评论:");
    commentshow->setGeometry(50,400,1100,50);
    commentshow->setVisible(true);

    for(i=0;i<posts[index].getComments().size();i++)
    {
       QLabel*comment=new QLabel(paint);
       newindex=getCommentsIndex(posts[index].getComments()[i]);
       s=comments[newindex].getContents();
       s+="\n";
       s+="userName:";
       s+=comments[newindex].getuserName();
       s+="\n";
       s+="time:";
       s+=comments[newindex].getTime();
       s+="\n--------------------------------------";
       str=QString::fromLocal8Bit(s.data());
       //QString str=QString::fromStdString(s);
       comment->setText(str);
       commentbuttons.push_back(comment);
       commentbuttons[i]->setGeometry(50,400+210*i,1100,210);
       commentbuttons[i]->setVisible(true);

       QPushButton*CommentDelete=new QPushButton("删除",paint);
       QPushButton*CommentAccuse=new QPushButton("举报",paint);
       CommentDelete->setGeometry(0,450+210*(i),50,50);
       CommentAccuse->setGeometry(0,500+210*(i),50,50);

       if(userkind==2&&posts[postnum].getuserName()==moderators[num].getuserName()||
               userkind==1&&posts[postnum].getuserName()==ordinaryusers[num].getuserName())
       CommentDelete->setVisible(true);
       CommentAccuse->setVisible(true);
       commentAccuse.push_back(CommentAccuse);
       commentbuttonsDelete.push_back(CommentDelete);
       commentAccuse[i]->setObjectName(QString::number(i));
       commentbuttonsDelete[i]->setObjectName(QString::number(i));
       connect(commentbuttonsDelete[i], SIGNAL(clicked()), this, SLOT(ClickButton11()));
       connect(commentAccuse[i], SIGNAL(clicked()), this, SLOT(ClickButton15()));
    }
}


void MainWindow::hidecommentandpost()
{
    int i;
    for(i=0;i<postbuttons.size();i++)
    {
        postbuttonsDelete[i]->setVisible(false);
        postbuttons[i]->setVisible(false);
    }
    for(i=0;i<commentbuttons.size();i++)
    {
        commentbuttonsDelete[i]->setVisible(false);
        commentbuttons[i]->setVisible(false);
        commentAccuse[i]->setVisible(false);
    }
    postbuttons.clear();
    postbuttonsDelete.clear();
    commentbuttons.clear();
    commentbuttonsDelete.clear();
    commentAccuse.clear();
    commentshow->setVisible(false);
    PostTimeShow->setVisible(false);
    PostUp->setVisible(false);
}

void MainWindow::ClickButton7()   //增加底部的评论
{
    QString strText;
    strText = writeComment->toPlainText();
    if(strText!="")
    addcomments(strText);
    else
    {
        QLabel*text=new QLabel("输入不能为空");
        text->setVisible(true);
        text->setFixedSize(300,300);
    }
}


void MainWindow::ClickButton8()    //发布新的帖子
{
    QString strText,strTitle;
    strText = writePost->toPlainText();
    strTitle= titleinsert->text();
    if(strText!=""&&strTitle!="")
    addPosts(strText,strTitle);
    else
    {
        QLabel*text=new QLabel("输入不能为空");
        text->setVisible(true);
    }
}

void MainWindow::addPosts(QString content,QString title)
{
    string s1,s2,s3;
    int id;

    time_t t = time(0);
       char tmp[64];
       strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X-%A ",localtime(&t) );
       string s4(tmp);
       id=posts[posts.size()-1].getID()+1;
    if(userkind==1)
    {
        s1=ordinaryusers[num].getuserName();
        ordinaryusers[num].addPosts(id);
    }
    else if(userkind==2)
    {
        s1=moderators[num].getuserName();
        moderators[num].addPosts(id);
    }
    sections[sectionnum].changeposts(id);
    s2=title.toStdString();

    s3=content.toStdString();
    Post p(s1,s2,s3,s4,id);
    posts.push_back(p);
    showPosts();

    addpostdatabase(id,s1,s4,s2,s3);
    examinePostdatabase();
}

void MainWindow::addpostdatabase(int id,string name, string time,string title,string content)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into Post values (?,?,?,?,?)";
    QString str;
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(id);
    str=QString::fromLocal8Bit(name.data());
    sql_query.addBindValue(str);
    str=QString::fromLocal8Bit(time.data());
    sql_query.addBindValue(str);
    str=QString::fromLocal8Bit(title.data());
    sql_query.addBindValue(str);
    str=QString::fromLocal8Bit(content.data());
    sql_query.addBindValue(str);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted ok!";
    }
}

void MainWindow::showPosts()   //显示帖子
{
    int i;
    int id;
    int index;
    QString str;
    hidecommentandpost();
    //cout<<sections[sectionnum].getPosts().size()<<"yy"<<endl;
    for(i=0;i<sections[sectionnum].getPosts().size();i++)
    {
        QPushButton*p=new QPushButton(paint);
        id=sections[sectionnum].getPosts()[i];
        index=getPostsIndex(id);
        string s=posts[index].getTitle();

        str=QString::fromLocal8Bit(s.data());
        //QString str=QString::fromStdString(s);
        p->setText(str);
        p->setStyleSheet("QPushButton{text-align : top;}");
        postbuttons.push_back(p);
        postbuttons[i]->setGeometry(120,50*(i+1),1700,50);//  显示帖子
        postbuttons[i]->setVisible(true);

        QPushButton*q=new QPushButton("delete",paint);
        postbuttonsDelete.push_back(q);
        postbuttonsDelete[i]->setGeometry(0,50*(i+1),120,50);//  显示帖子删除按钮

        if(userkind==2&&moderators[num].getSection()==sectionnum||
                (userkind==1&&posts[index].getuserName()==ordinaryusers[num].getuserName()
                 &&posts[index].getComments().size()==0)
                ||(userkind==2&&posts[index].getuserName()==moderators[num].getuserName()
                   &&posts[index].getComments().size()==0))  //判断是否是版主，判断是否是当前用户的帖子
            postbuttonsDelete[i]->setVisible(true);
        else
            postbuttonsDelete[i]->setVisible(false);

        postbuttons[i]->setVisible(true);
    }

    for(i=0;i<postbuttons.size();i++)
    {
        postbuttons[i]->setObjectName(QString::number(i));
        postbuttonsDelete[i]->setObjectName(QString::number(i));
        connect(postbuttons[i], SIGNAL(clicked()), this, SLOT(ClickButton6()));
        connect(postbuttonsDelete[i], SIGNAL(clicked()), this, SLOT(ClickButton10()));
    }
    commentshow->setVisible(false);

}


void MainWindow::addcomments(QString str)    //增加评论
{
    string s1,s2;
    int id;

    time_t t = time(0);
       char tmp[64];
       strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X-%A ",localtime(&t) );
       string s3(tmp);
       id=comments[comments.size()-1].getID()+1;
    if(userkind==1)
    {
        s1=ordinaryusers[num].getuserName();
        ordinaryusers[num].addComments(id);
    }
    else if(userkind==2)
    {
        s1=moderators[num].getuserName();
        moderators[num].addComments(id);
    }
    posts[postnum].changeComments(id);
    s2=str.toStdString();
    Comment c(s1,s2,s3,id);
    comments.push_back(c);
    showComments(postnum);

    addcommentdatabase(id,s1,s3,s2);
    examineCommentdatabase();

}

void MainWindow::addcommentdatabase(int id,string name, string time,string content)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into Comment values (?,?,?,?)";
    QString str;
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(id);
    str=QString::fromLocal8Bit(name.data());
    sql_query.addBindValue(str);
    str=QString::fromLocal8Bit(time.data());
    sql_query.addBindValue(str);
    str=QString::fromLocal8Bit(content.data());
    sql_query.addBindValue(str);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted ok!";
    }

}


bool MainWindow::ifrepeat(string userName)
{
    int i;
    for(i=0;i<administrators.size();i++)
    {
        if(administrators[i].getuserName()==userName)
            return false;
    }
    for(i=0;i<ordinaryusers.size();i++)
    {
        if(administrators[i].getuserName()==userName)
            return false;
    }
    return true;
}


void MainWindow::produceNewUser(string a,string b)
{
    string c=ordinaryusers[ordinaryusers.size()-1].getId();
    int num = atoi(c.c_str());
    num++;
    c=to_string(num);
    time_t t = time(0);
    char tmp[64];
    strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X-%A ",localtime(&t) );
     string s3(tmp);
    Ordinaryuser o(c,a,b,s3);
    ordinaryusers.push_back(o);
    ordinaryusers[ordinaryusers.size()-1].changeLevel(1);
    ordinaryusers[ordinaryusers.size()-1].addAccusationtimes(0);
}

void MainWindow::produceNewAnonymous(string a)
{
    string c=ordinaryusers[ordinaryusers.size()-1].getId();
    int num = atoi(c.c_str());
    num++;
    c=to_string(num);
    time_t t = time(0);
       char tmp[64];
       strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X-%A ",localtime(&t) );
       string s3(tmp);
    Anonymoususer o(c,"anonymous",a,s3);
    anonymoususers.push_back(o);
    insertanonylousDatabase(c,"anonymous",a,s3);
}

void MainWindow::examineanonylousDatabase()
{
    QSqlQuery sql_query;
    QString select_all_sql = "select * from anonymoususer";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {


            QString  id= sql_query.value(0).toString();
            //QString Title = sql_query.value(3).toString();
            QString name = sql_query.value(1).toString();
            QString password = sql_query.value(2).toString();
            QString lasttime = sql_query.value(3).toString();


            qDebug()<<QString("id:%1    name:%2    password:%3     lasttime:%4" ).arg(id)
                      .arg(name).arg(password).arg(lasttime);
        }
    }
}

void MainWindow::ClickButton3()   //注册状态
{

    QString nameUser = line1->text();
    QString password = line2->text();
    if(anonymousIn->isChecked())
    {
        QLabel*text=new QLabel("注册成功");  //弹出提示框注册成功
        text->setFixedSize(300,100);
        text->setVisible(true);
        produceNewAnonymous(password.toStdString());   //产生新的匿名用户
        userkind=3;
        num=anonymoususers.size()-1;
        anonymoususers[num].Online();
        startForum();

    }
    else if(ordinaryuserIn->isChecked()&&ifrepeat(nameUser.toStdString()))
    {
        QLabel*text=new QLabel("注册成功");  //弹出提示框注册成功
        text->setFixedSize(300,100);
        text->setVisible(true);
        produceNewUser(nameUser.toStdString(),password.toStdString());    //产生新用户
        userkind=1;
        num=ordinaryusers.size()-1;
        ordinaryusers[num].Online();
        startForum();
    }
}



void MainWindow::insertanonylousDatabase(string id,string name,string password,string time)
{
    QSqlQuery sql_query;
    QString str;
    QString insert_sql = "insert into anonymoususer values (?, ?, ?,?)";
    sql_query.prepare(insert_sql);
    str=QString::fromStdString(id);
    sql_query.addBindValue(str);
    str=QString::fromStdString(name);
    sql_query.addBindValue(str);
    str=QString::fromStdString(password);
    sql_query.addBindValue(str);
    str=QString::fromStdString(time);
    sql_query.addBindValue(str);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted ok!";
    }
    examineanonylousDatabase();
}

void MainWindow::insertordinaryuserDatabase(string id,string name,string password,
                                            string time,int level,int accusationtimes)
{
    QSqlQuery sql_query;
    QString str;
    QString insert_sql = "insert into ordinaryuser values (?, ?, ?,?,?,?)";
    sql_query.prepare(insert_sql);
    str=QString::fromStdString(id);
    sql_query.addBindValue(str);
    str=QString::fromStdString(name);
    sql_query.addBindValue(str);
    str=QString::fromStdString(password);
    sql_query.addBindValue(str);
    str=QString::fromStdString(time);
    sql_query.addBindValue(str);
    sql_query.addBindValue(level);
    sql_query.addBindValue(accusationtimes);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted ok!";
    }
    //examineanonylousDatabase();
}


int MainWindow::getPostsIndex(int id)
{
    int i;
    for(i=0;i<posts.size();i++)
        if(posts[i].getID()==id)
            return i;
}

int MainWindow::getCommentsIndex(int id)
{
    int i;
    for(i=0;i<comments.size();i++)
        if(comments[i].getID()==id)
            return i;
}

int MainWindow::ifconform(string userName,string password)   //判断当前用户是否存在并且密码是否正确,返回三种情况
{
    int i;
    if(!button4->isChecked()&&!anonymousIn->isChecked())//不点击按钮，代表此时是普通用户输入
    {
        for(i=0;i<ordinaryusers.size();i++)
        {
            if(ordinaryusers[i].entryUser(userName,password)==1)
            {
                num=i;
                userkind=1;
                return 0;
            }
            else if(ordinaryusers[i].entryUser(userName,password)==2)
                return 2;
        }
        for(i=0;i<moderators.size();i++)
        {

            if(moderators[i].entryUser(userName,password)==1)
            {
                num=i;
                userkind=2;
                return 0;
            }
            else if(moderators[i].entryUser(userName,password)==2)
                return 2;
        }
    }
    else if(button4->isChecked() &&!anonymousIn->isChecked())                        //点击按钮，代表此时是管理员输入
    {
        for(i=0;i<administrators.size();i++)
        {
            if(administrators[i].getuserName()==userName)
            {
                if(administrators[i].getpassword()==password)
                {
                    num=i;
                    userkind=0;
                    return 0;
                }
                else return 2;
            }
        }
    }
    else if(!button4->isChecked() &&anonymousIn->isChecked())
    {
        for(i=0;i<anonymoususers.size();i++)
        {
            if(anonymoususers[i].getuserName()==userName)
            {
                if(anonymoususers[i].getpassword()==password)
                {
                    num=i;
                    userkind=3;
                    return 0;
                }
                else return 2;
            }
        }

    }

    return 1;
}

void MainWindow::ClickButton9()    //用户注销
{
    time_t t = time(0);
   char tmp[64];
   strftime( tmp, sizeof(tmp), "%Y/%m/%d-%X-%A ",localtime(&t) );
   string s3(tmp);
   if(userkind==0)
   {
       administrators[num].changeLastOnlineTime(s3);
       administrators[num].outUser();
   }
   else if(userkind==1)
   {
       ordinaryusers[num].changeLastOnlineTime(s3);
       ordinaryusers[num].outUser();
   }
   else if(userkind==2)
   {
       moderators[num].changeLastOnlineTime(s3);
       moderators[num].outUser();
   }
   userkind=-1;
   sectionnum=-1;
   postnum=-1;
    enterForum();
}


void MainWindow::ClickButton10()    //删除帖子操作
{
    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);
    int index;
    if(push_button)
    {
        QString object_name = push_button->objectName();
        index = object_name.toInt();
    }
    int id,i,j,k;
    id=sections[sectionnum].getPosts()[index];
    index=getPostsIndex(id);
    for(i=0;i<postbuttons.size();i++)
    {
        postbuttonsDelete[i]->setVisible(false);
        postbuttons[i]->setVisible(false);
    }

    //id=posts[index].getID();
    sections[sectionnum].deletePosts(id);   //删除板块下的帖子索引
    User*u;
    for(i=0;i<ordinaryusers.size();i++)    //删除对应的帖子
    {
        if(posts[index].getuserName()==ordinaryusers[i].getuserName())
        {
            u=&ordinaryusers[i];
            u->deletePosts(id);
            for(j=0;j<posts[index].getComments().size();j++)
            {
                k=getCommentsIndex(posts[index].getComments()[j]);
                deleteUserComments(k);
                deleteComments(k);
            }
        }
    }
    for(i=0;i<moderators.size();i++)
    {
        if(posts[index].getuserName()==moderators[i].getuserName())
        {
            u=&moderators[i];
            u->deletePosts(id);
            for(j=0;j<posts[index].getComments().size();j++)
            {
                //moderators[i].deleteComments(posts[index].getComments()[j]);
                k=getCommentsIndex(posts[index].getComments()[j]);
                deleteUserComments(k);
                deleteComments(k);
            }
        }
    }
    deletePosts(index); //删除帖子
    deletepostdatabase(id);
    examinePostdatabase();
    showPosts();
}

void MainWindow::deletepostdatabase(int id)
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from Post where id = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(id);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}

void MainWindow::deleteUserComments(int index)
{
    int i;
    for(i=0;i<ordinaryusers.size();i++)
    {
        if(ordinaryusers[i].getuserName()==comments[index].getuserName())
        {
            ordinaryusers[i].deleteComments(comments[index].getID());
        }
    }
    for(i=0;i<moderators.size();i++)
    {
        if(moderators[i].getuserName()==comments[index].getuserName())
        {
            moderators[i].deleteComments(comments[index].getID());
        }
    }
}

void MainWindow::ClickButton11()     //删除评论操作
{
    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);
    int index;
    if(push_button)
    {
        QString object_name = push_button->objectName();
        index = object_name.toInt();
    }
    int i,j,k,id;
    int newindex;
    id=posts[postnum].getComments()[index];
    newindex=getCommentsIndex(id);
    for(i=0;i<ordinaryusers.size();i++)
    {
        if(ordinaryusers[i].getuserName()==comments[newindex].getuserName())
        {
            ordinaryusers[i].deleteComments(id);
        }
    }
    for(i=0;i<moderators.size();i++)
    {
        if(moderators[i].getuserName()==comments[newindex].getuserName())
        {
            moderators[i].deleteComments(id);
        }
    }
    posts[postnum].deleteComments(id);
    deleteComments(newindex);
    deletecommentdatabase(id);
    examineCommentdatabase();
    showComments(postnum);
}

void MainWindow::deletecommentdatabase(int id)
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from Comment where id = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(id);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}



void MainWindow::deletePosts(int index)
{
    vector<class Post>::iterator it =posts.begin()+index;
    posts.erase(it);
}

void MainWindow::deleteComments(int index)
{
    vector<class Comment>::iterator it =comments.begin()+index;
    comments.erase(it);
}

void MainWindow::ClickButton12()
{
    dialog->setVisible(true);
    linenewmoderator->setVisible(true);
    //cout<<"yyy"<<endl;
    changemoderator->setVisible(true);

}

void MainWindow::ClickButton13()
{
    QString str=linenewmoderator->text();
    string s=str.toStdString();
    changeModerator(s);
    showModeratorName();
    dialog->setVisible(false);
}

void MainWindow::changeModerator(string userName)    //改变版主
{
    int i,j;
    string id1,id2;
    string s;
    int sum;
    vector<int>array;
    for(i=0;i<ordinaryusers.size();i++)
    {
        if(ordinaryusers[i].getuserName()==userName)
        {
            s=userName;     //一一交换信息
            ordinaryusers[i].changeuserName(moderators[sectionnum].getuserName());
            moderators[sectionnum].changeuserName(s);
            s=ordinaryusers[i].getpassword();
            ordinaryusers[i].changepassword(moderators[sectionnum].getpassword());
            moderators[sectionnum].changepassword(s);

            id1=moderators[sectionnum].getId();
            id2=ordinaryusers[i].getId();

            s=ordinaryusers[i].getId();

            ordinaryusers[i].changeID(moderators[sectionnum].getId());
            moderators[sectionnum].changeID(s);

            s=ordinaryusers[i].getLastOnlineTime();
            ordinaryusers[i].changeLastOnlineTime(moderators[sectionnum].getLastOnlineTime());
            moderators[sectionnum].changeLastOnlineTime(s);

            sum=ordinaryusers[i].getLevel();
            ordinaryusers[i].changeLevel(moderators[sectionnum].getLevel());
            moderators[sectionnum].changeLevel(sum);


            sum=ordinaryusers[i].getAccusationtimes();
            ordinaryusers[i].addAccusationtimes(moderators[sectionnum].getAccusationtimes());
            moderators[sectionnum].addAccusationtimes(sum);



            for(j=0;j<ordinaryusers[i].getCommentId().size();j++)
            {
                array.push_back(ordinaryusers[i].getCommentId()[j]);
            }
            ordinaryusers[i].changeComments(moderators[sectionnum].getCommentId());
            moderators[sectionnum].changeComments(array);

            for(j=0;j<ordinaryusers[i].getPostId().size();j++)
            {
                array.push_back(ordinaryusers[i].getPostId()[j]);
            }
            ordinaryusers[i].changePosts(moderators[sectionnum].getPostId());
            moderators[sectionnum].changePosts(array);

            sections[sectionnum].changeModerator(userName);
            changeModeratorDatabase(id1,id2);
        }
    }
    //sections[sectionnum].changeModerator(userName);
    //changeModeratorDatabase(id1,id2);
}


void MainWindow::changeModeratorDatabase(string id1,string id2)   //改变版主数据库 id1是版主 id2是普通用户
{
    int i;
    QString s1,s2,s3,s4;

    int n1,n2,n3;

    QSqlQuery sql_query;
    QString insert_sql;
    QString str;


    str=QString::fromStdString(id1);
    QString select_all_sql = "select * from moderator";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {

            s1 = sql_query.value(0).toString();
            if(str==s1)
            {
                s2 = sql_query.value(1).toString();
                s3 = sql_query.value(2).toString();
                s4 = sql_query.value(3).toString();
                n1 = sql_query.value(4).toInt();
                n2 = sql_query.value(5).toInt();
                n3 = sql_query.value(6).toInt();
                break;
            }
        }
    }
    insertordinaryuserDatabase(s1.toStdString(),s2.toStdString(),s3.toStdString(),
                               s4.toStdString(),n1,n2);



    str=QString::fromStdString(id2);
    select_all_sql = "select * from ordinaryuser";
    sql_query.prepare(select_all_sql);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            s1 = sql_query.value(0).toString();
            if(str==s1)
            {
                s2 = sql_query.value(1).toString();
                s3 = sql_query.value(2).toString();
                s4 = sql_query.value(3).toString();
                n1 = sql_query.value(4).toInt();
                n2 = sql_query.value(5).toInt();
                break;
            }
        }
    }
    insertmoderatorDatabase(s1.toStdString(),s2.toStdString(),s3.toStdString(),s4.toStdString(),n1,n2,n3);

    deleteordinaryuserDatabase(id2);
    deletemoderatorDatabase(id1);

    insertDatabase();


}

void MainWindow::deleteordinaryuserDatabase(string id)
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from ordinaryuser where id = ?";
    QString str;
    str=QString::fromStdString(id);
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(str);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}

void MainWindow::deletemoderatorDatabase(string id)
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from moderator where id = ?";
    QString str;
    str=QString::fromStdString(id);
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(str);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }
}

void MainWindow::insertmoderatorDatabase(string id,string name,string password,string time,int level,
                             int accusationtimes,int section)
{
    QSqlQuery sql_query;
    QString str;
    QString insert_sql = "insert into moderator values (?, ?, ?,?,?,?,?)";
    sql_query.prepare(insert_sql);
    str=QString::fromStdString(id);
    sql_query.addBindValue(str);
    str=QString::fromStdString(name);
    sql_query.addBindValue(str);
    str=QString::fromStdString(password);
    sql_query.addBindValue(str);
    str=QString::fromStdString(time);
    sql_query.addBindValue(str);
    sql_query.addBindValue(level);
    sql_query.addBindValue(accusationtimes);
    sql_query.addBindValue(sectionnum);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted ok!";
    }
    insertDatabase();
}


int  MainWindow::sumOnline()
{
    int i;
    int sum=0;
    for(i=0;i<ordinaryusers.size();i++)
    if(ordinaryusers[i].getOnline()==true)
            sum++;

    for(i=0;i<administrators.size();i++)
    if(administrators[i].getOnline()==true)
            sum++;

    for(i=0;i<moderators.size();i++)
    if(moderators[i].getOnline()==true)
            sum++;

    for(i=0;i<anonymoususers.size();i++)
        if(anonymoususers[i].getOnline()==true)
            sum++;
    return sum;

}

void MainWindow::ClickButton14()   //显示用户详细信息
{
    string s,s1,s2,s3,s4,s5,s6,s7;
    int i;
    s="UserName:";
    if(userkind==1)
    {
    s+=ordinaryusers[num].getuserName();
    s1="ordinaryuser";
    s2=ordinaryusers[num].getId();
    i=ordinaryusers[num].getPostId().size();
    s3 = std::to_string(i);

    i=ordinaryusers[num].getCommentId().size();
    s4 = std::to_string(i);

    s5=ordinaryusers[num].getLastOnlineTime();

    i=ordinaryusers[num].getLevel();
    s6=std::to_string(i);
    i=ordinaryusers[num].getAccusationtimes();
    s7=std::to_string(i);

    }
    else if(userkind==2)
    {
        s+=moderators[num].getuserName();
        s1="moderator";
        s2=moderators[num].getId();

        i=moderators[num].getPostId().size();
        s3 = std::to_string(i);

        i=moderators[num].getCommentId().size();
        s4 = std::to_string(i);

        s5=moderators[num].getLastOnlineTime();

        i=moderators[num].getLevel();
        s6=std::to_string(i);
        //cout<<i<<"kkkkkkkkkk"<<endl;
        i=moderators[num].getAccusationtimes();
        s7=std::to_string(i);
    }
    else if(userkind==0)
    {
        s+=administrators[num].getuserName();
        s1="administrator";
        s2=administrators[num].getId();
    }
   else if(userkind==3)
    {
        s+="anonymous";
        s1="anonymous";
        s2=anonymoususers[num].getId();
    }

    s+="\n\nuserkind:";
    s+=s1;
    s+="\n\nid:";
    s+=s2;
    if(userkind!=0&&userkind!=3)
    {
        s+="\n\n已发表帖子数目:"+s3+"\n\n已发表评论数目:"+s4+"\n\n最后一次登录时间:"+s5;
        s+="\n\n目前等级:"+s6;
        s+="\n\n被举报次数:"+s7;
    }

    s+="\n\n当前活跃人数:"+std::to_string(sumOnline());




    QString str=QString::fromStdString(s);
    QLabel*text=new QLabel(str);
    text->setFixedSize(700,800);
    text->setVisible(true);

}



void MainWindow::ClickButton15()
{
    QObject *object = QObject::sender();
    QPushButton *push_button = qobject_cast<QPushButton *>(object);
    int index;
    if(push_button)
    {
        QString object_name = push_button->objectName();
        index = object_name.toInt();
    }
    int newindex;
    int i,id;
    id=posts[postnum].getComments()[index];
    newindex=getCommentsIndex(id);
    for(i=0;i<ordinaryusers.size();i++)
    {
        if(ordinaryusers[i].getuserName()==comments[newindex].getuserName())
        {

            ordinaryusers[i].addAccusationtimes(ordinaryusers[i].getAccusationtimes()+1);
        }
    }
    for(i=0;i<moderators.size();i++)
    {
        if(moderators[i].getuserName()==comments[newindex].getuserName())
        {
            moderators[i].addAccusationtimes(moderators[i].getAccusationtimes()+1);
        }
    }
    QLabel*text=new QLabel("举报成功");
    text->setVisible(true);
    text->setFixedSize(300,300);

}

MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::closeEvent(QCloseEvent *e)
{
    string s1,s2,s3;
    int n,m;
    int i;
    string s;
    fstream file;


    database.close();

    if(error==false)
    {

    file.open("administrator.txt",ios::out);
    if (file.is_open())
    {
        file<<endl;
        file<<administrators.size()<<endl;
        for(i=0;i<administrators.size();i++)
        {
            file<<administrators[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();


    file.open("ordinaryuser.txt",ios::out);
    if (file.is_open())
    {
        file<<endl;
        file<<ordinaryusers.size()<<endl;
        for(i=0;i<ordinaryusers.size();i++)
        {
            file<<ordinaryusers[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();

    User*mm;
    file.open("anonylous.txt",ios::out);
    if (file.is_open())
    {
        file<<endl;
        file<<anonymoususers.size()<<endl;
        for(i=0;i<anonymoususers.size();i++)
        {
            mm=&anonymoususers[i];
            file<<anonymoususers[i];
            //file<<*mm;
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();



    file.open("moderator.txt",ios::out);
    if (file.is_open())
    {
        file<<endl;
        file<<moderators.size()<<"\n";
        for(i=0;i<moderators.size();i++)
        {
            file<<moderators[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();


    file.open("posts.txt",ios::out);
    if (file.is_open())
    {
        file<<posts.size()<<"\n";
        for(i=0;i<posts.size();i++)
        {
            file<<posts[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();

    file.open("comments.txt",ios::out);
    if (file.is_open())
    {
        file<<comments.size()<<"\n";
        for(i=0;i<comments.size();i++)
        {
            file<<comments[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();


    file.open("sections.txt",ios::out);
    if (file.is_open())
    {
        file<<sections.size()<<"\n";
        for(i=0;i<sections.size();i++)
        {
            file<<sections[i];
        }
    }
    else
    {
        cout<<"error happen"<<endl;
    }
    file.close();
    }


 }
