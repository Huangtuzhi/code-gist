#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>

#define MAXSIZE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8787
#define FDSIZE        1024
#define EPOLLEVENTS 20

using namespace std;

static void handle_connection(int sockfd);
static void
handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf);
static void do_read(int epollfd,int fd,int sockfd,char *buf);
static void do_read(int epollfd,int fd,int sockfd,char *buf);
static void do_write(int epollfd,int fd,int sockfd,char *buf);
static void add_event(int epollfd,int fd,int state);
static void delete_event(int epollfd,int fd,int state);
static void modify_event(int epollfd,int fd,int state);

int main(int argc,char *argv[])
{
    int                 sockfd;
    struct sockaddr_in  servaddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,IPADDRESS,&servaddr.sin_addr);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    //处理连接
    handle_connection(sockfd);
    close(sockfd);
    return 0;
}


static void handle_connection(int sockfd)
{
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    int ret;
	// 创建 epoll 的文件描述符
    epollfd = epoll_create(FDSIZE);
	// 用 epoll 监听
    add_event(epollfd,STDIN_FILENO,EPOLLIN);
    for ( ; ; )
    {
		cout << "--------------------begin for loop" << endl;
        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);
        handle_events(epollfd,events,ret,sockfd,buf);
		cout << "--------------------end for loop" << endl;
    }
    close(epollfd);
}

static void
handle_events(int epollfd,struct epoll_event *events,int num,int sockfd,char *buf)
{
    int fd;
    int i;
    for (i = 0;i < num;i++)
    {
        fd = events[i].data.fd;
        if (events[i].events & EPOLLIN) {
            // 有键盘的输入数据到来 || 有 socket 的数据到来
			do_read(epollfd,fd,sockfd,buf);
		}
        else if (events[i].events & EPOLLOUT) {
            cout << "EPOLLOUT" << endl;
			do_write(epollfd,fd,sockfd,buf);
		}
    }
}

static void do_read(int epollfd,int fd,int sockfd,char *buf)
{
    int nread;
    nread = read(fd,buf,MAXSIZE);
	cout << "Read data:" << buf << endl;
    if (nread == -1)
    {
        perror("read error:");
        close(fd);
    }
    else if (nread == 0)
    {
        fprintf(stderr,"server close.\n");
        close(fd);
    }
    else
    {
        if (fd == STDIN_FILENO)
			// 如果有来自键盘的数据输入，把 socket 描述符加入到 epoll 监听中
            add_event(epollfd,sockfd,EPOLLOUT);
        else
        {
			// 如果有来自 socket 的数据输入
            delete_event(epollfd,sockfd,EPOLLIN);
            add_event(epollfd,STDOUT_FILENO,EPOLLOUT);
        }
    }
}

static void do_write(int epollfd,int fd,int sockfd,char *buf)
{
    int nwrite;
	// 1、写数据到 socket 2、写数据到 STDOUT 
    nwrite = write(fd,buf,strlen(buf));
	cout << "Write data:" << buf << endl;
	if (nwrite == -1)
    {
        perror("write error:");
        close(fd);
    }
    else
    {
        if (fd == STDOUT_FILENO)
            delete_event(epollfd,fd,EPOLLOUT);
        else
            modify_event(epollfd,fd,EPOLLIN);
    }
    memset(buf,0,MAXSIZE);
}

static void add_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
	// 往 epoll 监听描述符添加对 fd state 状态的监听
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}

static void delete_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}

static void modify_event(int epollfd,int fd,int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}
