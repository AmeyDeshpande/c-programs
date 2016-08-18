#include "goldchase.h"
#include "Map.h"
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include <semaphore.h>
#include <signal.h>
#include <mqueue.h>
#include <stdlib.h>

using namespace std;

  struct GameBoard {
  int rows;
  int cols;
  unsigned char players;
  pid_t pid[5];
  unsigned char map[0];
  };
  Map *mapPtr;
  GameBoard* goldmap;
  mqd_t readqueue_fd; //message queue file descriptor
  string mq_name;
  int pos;
  unsigned char current_player;
  void map_refresh(int)
  {
    mapPtr->drawMap();
  }
  void read_message(int)
  {
    struct sigevent mq_notification_event;
    mq_notification_event.sigev_notify=SIGEV_SIGNAL;
    mq_notification_event.sigev_signo=SIGUSR2;
    mq_notify(readqueue_fd, &mq_notification_event);

    int err;
    char msg[121];
    memset(msg, 0, 121);//set all characters to '\0'
    while((err=mq_receive(readqueue_fd, msg, 120, NULL))!=-1)
    {
      mapPtr->postNotice(msg);
      memset(msg, 0, 121);//set all characters to '\0'
    }
    if(errno!=EAGAIN)
    {
      perror("mq_receive");
      exit(1);
    }
  }
  void clean_up(int)
  {
    //cerr << "Cleaning up message queue" << endl;
    mq_close(readqueue_fd);
    mq_unlink(mq_name.c_str());
      if(goldmap->pid[0] == getpid())
      {
        goldmap->players &= ~current_player;
        goldmap->pid[0] = 0;
        goldmap->map[pos] &= ~current_player;
      }
      else if(goldmap->pid[1] == getpid())
      {
        goldmap->players &= ~current_player;
        goldmap->pid[1] = 0;
        goldmap->map[pos] &= ~current_player;
      }
      else if(goldmap->pid[2] == getpid())
      {
        goldmap->players &= ~current_player;
        goldmap->pid[2] = 0;
        goldmap->map[pos] &= ~current_player;
      }
      else if(goldmap->pid[3] == getpid())
      {
        goldmap->players &= ~current_player;
        goldmap->pid[3] = 0;
        goldmap->map[pos] &= ~current_player;
      }
      else if(goldmap->pid[4] == getpid())
      {
        goldmap->players &= ~current_player;
        goldmap->pid[4] = 0;
        goldmap->map[pos] &= ~current_player;
      }
    endwin();
    for(int i=0;i<5;i++)
    {
      if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
        kill(goldmap->pid[i],SIGUSR1);
    }
    if(goldmap->players == 0)
    {
      sem_unlink("/AMDgoldchase");
      shm_unlink("sharedmem");
    }
    exit(1);
  }
  void write_message(string player_mq,string msg)
  {
    mqd_t writequeue_fd; //message queue file descriptor
    if((writequeue_fd=mq_open(player_mq.c_str(), O_WRONLY|O_NONBLOCK))==-1)
    {
      perror("mq_open");
      exit(1);
    }
    char message_text[121];
    memset(message_text, 0, 121);
    strncpy(message_text, msg.c_str(), 120);

    if(mq_send(writequeue_fd, message_text, strlen(message_text), 0)==-1)
    {
      perror("mq_send");
      exit(1);
    }
    mq_close(writequeue_fd);
  }

int main()
{
  struct sigaction refresh_map;
  refresh_map.sa_handler=map_refresh;
  sigemptyset(&refresh_map.sa_mask);
  refresh_map.sa_flags=0;
  refresh_map.sa_restorer=NULL;

  sigaction(SIGUSR1, &refresh_map, NULL);


  struct sigaction exit_handler;
  exit_handler.sa_handler=clean_up;
  sigemptyset(&exit_handler.sa_mask);
  exit_handler.sa_flags=0;
  sigaction(SIGINT, &exit_handler, NULL);
  sigaction(SIGTERM,&exit_handler,NULL);
  sigaction(SIGHUP,&exit_handler,NULL);


  struct sigaction action_to_take;
  action_to_take.sa_handler=read_message;
  sigemptyset(&action_to_take.sa_mask);
  action_to_take.sa_flags=0;
  sigaction(SIGUSR2, &action_to_take, NULL);

  struct mq_attr mq_attributes;
  mq_attributes.mq_flags=0;
  mq_attributes.mq_maxmsg=10;
  mq_attributes.mq_msgsize=120;



  current_player=0;
  sem_t *my_sem_ptr;
  bool found=false;
  my_sem_ptr= sem_open(
    "/AMDgoldchase", O_CREAT|O_EXCL, S_IROTH| S_IWOTH| S_IRGRP| S_IWGRP| S_IRUSR| S_IWUSR,1);
    if(my_sem_ptr==SEM_FAILED)
    {
      if(errno!=EEXIST)
      {
        perror("Opening semaphore");
        exit(1);
      }
    }
   //sem_unlink("/AMDgoldchase");
     //   shm_unlink("sharedmem");
    if(my_sem_ptr!=SEM_FAILED)
    {
      int cnt=0;char x;
      sem_wait(my_sem_ptr);
      int fd = shm_open("sharedmem", O_RDWR|O_CREAT|O_EXCL, S_IRUSR | S_IWUSR);
      if(fd==-1)
      {
        perror("Opening shared memory");
        exit(1);
      }
      fstream file("mymap.txt",std::ios::out|std::ios::in);
      int row=0,col=0,number_of_gold=0;
      string line;

      while(getline(file,line))
      {
        col++;
        if(col==2)
          row=line.length();
      }
      col--;
      int trunc=ftruncate(fd,row*col+sizeof(GameBoard));
      goldmap= (GameBoard*)mmap(NULL, row*col, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
      for(int i=0;i<5;i++)
        goldmap->pid[i] = 0;
      goldmap->rows=row;
      goldmap->cols=col;
      if(goldmap==MAP_FAILED)
        perror("Mapping to shared memory");
      file.clear();
      file.seekg(0);int incrementer=0;
      int i=0;
      while(file.get(x))
      {
        if(cnt==0)
        {
          number_of_gold=x-'0';
          cnt++;
        }
        else
        {
          if(x==' ')
          {
            goldmap->map[i] = 0;
            i++;
          }
          else if(x=='*')
          {
            goldmap->map[i] = G_WALL;
            i++;
          }
        }
      }
      int mapsize=goldmap->cols*goldmap->rows;
      srand(time(NULL));
      for(int i=0;i<number_of_gold;i++)
      {
        int pos=rand()%mapsize;
        if(goldmap->map[pos]!=0)
          i--;
        else
        {
          if(i==(number_of_gold-1))
            goldmap->map[pos] |= G_GOLD;
          else
            goldmap->map[pos] |= G_FOOL;
        }
      }
      sem_post(my_sem_ptr);
    }
    else
    {
      int row=0,col=0;
      my_sem_ptr= sem_open("/AMDgoldchase", O_RDWR,S_IROTH| S_IWOTH| S_IRGRP| S_IWGRP| S_IRUSR| S_IWUSR,1);
      sem_wait(my_sem_ptr);
      int fd = shm_open("sharedmem", O_RDWR, S_IRUSR | S_IWUSR);
      if(fd==-1)
      {
        perror("Opening shared memory");
        exit(0);
      }
      read(fd, &col, sizeof(int));
      read(fd, &row, sizeof(int));
      goldmap= (GameBoard*)mmap(NULL, row*col, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
      sem_post(my_sem_ptr);
    }
    sem_wait(my_sem_ptr);
    int mapsize=goldmap->cols*goldmap->rows;
    srand(time(NULL));
    pos=rand()%mapsize;
    while(goldmap->map[pos]!=0)
      pos=rand()%mapsize;
      if(goldmap->pid[0] == 0)
      {
        goldmap->pid[0]=getpid();
        current_player |= G_PLR0;
        goldmap->map[pos] = G_PLR0;
        goldmap->players |= G_PLR0;
        mq_name="/ameyd_plr1";
        for(int i=0;i<5; i++)
        {
          if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
            kill(goldmap->pid[i],SIGUSR1);
        }
      }
      else if(goldmap->pid[1] == 0)
      {
        goldmap->pid[1]=getpid();
        current_player |= G_PLR1;
        goldmap->map[pos] = G_PLR1;
        goldmap->players |= G_PLR1;
        mq_name="/ameyd_plr2";
        for(int i=0;i<5; i++)
        {
          if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
            kill(goldmap->pid[i],SIGUSR1);
        }
      }
      else if(goldmap->pid[2] == 0)
      {
        goldmap->pid[2]=getpid();
        current_player |= G_PLR2;
        goldmap->map[pos] = G_PLR2;
        goldmap->players |= G_PLR2;
        mq_name="/ameyd_plr3";
        for(int i=0;i<5; i++)
        {
          if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
            kill(goldmap->pid[i],SIGUSR1);
        }
      }
      else if(goldmap->pid[3] == 0)
      {
        goldmap->pid[3]=getpid();
        current_player |= G_PLR3;
        goldmap->map[pos] = G_PLR3;
        goldmap->players |= G_PLR3;
        mq_name="/ameyd_plr4";
        for(int i=0;i<5; i++)
        {
          if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
            kill(goldmap->pid[i],SIGUSR1);
        }
      }
      else if(goldmap->pid[4] == 0)
      {
        goldmap->pid[4]=getpid();
        current_player |= G_PLR4;
        goldmap->map[pos] = G_PLR4;
        goldmap->players |= G_PLR4;
        mq_name="/ameyd_plr5";
        for(int i=0;i<5; i++)
        {
          if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
            kill(goldmap->pid[i],SIGUSR1);
        }
      }
      else
      {
        cout<<"Sorry! We are currently full. Please try again later";
        exit(0);
      }
      sem_post(my_sem_ptr);
      if((readqueue_fd=mq_open(mq_name.c_str(), O_RDONLY|O_CREAT|O_EXCL|O_NONBLOCK,
              S_IRUSR|S_IWUSR, &mq_attributes))==-1)
      {
        perror("mq_open");
        exit(1);
      }
      //set up message queue to receive signal whenever message comes in
      struct sigevent mq_notification_event;
      mq_notification_event.sigev_notify=SIGEV_SIGNAL;
      mq_notification_event.sigev_signo=SIGUSR2;
      mq_notify(readqueue_fd, &mq_notification_event);

      Map goldMine(goldmap->map,goldmap->cols,goldmap->rows);
      mapPtr = &goldMine;
      int a=0;
      bool gameover=false;
      while((a=goldMine.getKey())!='Q')
      {
        int curr_pos;
        if(a == 'h' || a == 'a')
        {
	  curr_pos=pos;
          curr_pos--;
          sem_wait(my_sem_ptr);
          if(!(goldmap->map[curr_pos] & G_WALL) && (pos % goldmap->rows != 0))
          {
            goldmap->map[curr_pos] |= current_player;
            goldmap->map[pos] &= ~current_player;
            goldMine.drawMap();
            for(int i=0;i<5; i++)
            {
              if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
                kill(goldmap->pid[i],SIGUSR1);
            }
            pos=curr_pos;
            if(goldmap->map[curr_pos] & G_FOOL)
              goldMine.postNotice("You have found fool's gold");
            else if(goldmap->map[curr_pos] & G_GOLD)
            {
              found=true;
              goldMine.postNotice("You have found gold !!");
              goldmap->map[curr_pos] &= ~G_GOLD;
            }

            if(found)
            {
              if(curr_pos%(goldmap->rows) == 0)
              {
                goldMine.postNotice("You are a winner !!");
                gameover=true;
                break;
              }
            }
          }
          sem_post(my_sem_ptr);
        }
        if(a == 'l' || a == 'd')
        {
	  curr_pos=pos;
          curr_pos++;
          sem_wait(my_sem_ptr);
          if(!(goldmap->map[curr_pos] & G_WALL) && (pos % goldmap->rows != (goldmap->rows-1)))
          {
            goldmap->map[curr_pos] |= current_player;
            goldmap->map[pos] &= ~current_player;
            goldMine.drawMap();
            for(int i=0;i<5; i++)
            {
              if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
                kill(goldmap->pid[i],SIGUSR1);
            }
            pos=curr_pos;
            if(goldmap->map[curr_pos] & G_FOOL)
              goldMine.postNotice("You have found fool's gold");
            else if(goldmap->map[curr_pos] & G_GOLD)
            {
              found=true;
              goldMine.postNotice("You have found gold !!");
              goldmap->map[curr_pos] &= ~G_GOLD;
            }
            if(found)
            {
              if(curr_pos%(goldmap->rows) == (goldmap->rows-1))
              {
                goldMine.postNotice("You are a winner !!");
                gameover=true;
                break;
              }
            }
          }
          sem_post(my_sem_ptr);
        }
        if(a == 'j' || a == 's')
        {
          curr_pos=pos;
          curr_pos=curr_pos+goldmap->rows;
          sem_wait(my_sem_ptr);
          if(!(goldmap->map[curr_pos] & G_WALL) && !(curr_pos >= goldmap->rows*goldmap->cols))
          {
            goldmap->map[curr_pos] |= current_player;
            goldmap->map[pos] &= ~current_player;
            goldMine.drawMap();
            for(int i=0;i<5; i++)
            {
              if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
                kill(goldmap->pid[i],SIGUSR1);
            }
            pos=curr_pos;
            if(goldmap->map[curr_pos] & G_FOOL)
              goldMine.postNotice("You have found fool's gold");
            else if(goldmap->map[curr_pos] & G_GOLD)
            {
              found=true;
              goldMine.postNotice("You have found gold !!");
              goldmap->map[curr_pos] &= ~G_GOLD;
            }
            if(found)
            {
              int curr_row=curr_pos/goldmap->rows;
              if(curr_row==(goldmap->cols)-1)
              {
                goldMine.postNotice("You are a winner !!");
                gameover=true;
                break;
              }
            }
          }
          sem_post(my_sem_ptr);
        }
        if(a == 'k' || a == 'w')
        {
          curr_pos=pos;
          curr_pos=curr_pos-goldmap->rows;
          sem_wait(my_sem_ptr);
          if((curr_pos >= 0) && !(goldmap->map[curr_pos] & G_WALL))
          {
            goldmap->map[curr_pos] |= current_player;
            goldmap->map[pos] &= ~current_player;
            goldMine.drawMap();
            for(int i=0;i<5; i++)
            {
              if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
                kill(goldmap->pid[i],SIGUSR1);
            }
            pos=curr_pos;
            if(goldmap->map[curr_pos] & G_FOOL)
              goldMine.postNotice("You have found fool's gold");
            else if(goldmap->map[curr_pos] & G_GOLD)
            {
              found=true;
              goldMine.postNotice("You have found gold !!");
              goldmap->map[curr_pos] &= ~G_GOLD;
            }
            if(found)
            {
              int curr_row=curr_pos/(goldmap->rows-1);
              if(curr_row==0)
              {
                goldMine.postNotice("You are a winner !!");
                gameover=true;
                break;
              }
            }
          }
        }
        if(a == 'm')
        {
          string player_mq;
          int p;
          unsigned int players;
          players= goldmap->players;
          players &= ~current_player;
          unsigned int plr=goldMine.getPlayer(players);
          if(plr == G_PLR0)
            player_mq="/ameyd_plr1";
          else if(plr == G_PLR1)
            player_mq="/ameyd_plr2";
          else if(plr == G_PLR2)
            player_mq="/ameyd_plr3";
          else if(plr == G_PLR3)
            player_mq="/ameyd_plr4";
          else if(plr == G_PLR4)
            player_mq="/ameyd_plr5";
          string msg = goldMine.getMessage();
          int player_id;
          for(int i = 0; i < 5; i++)
          {
            if(goldmap->pid[i] == getpid())
              player_id=i;
          }
          msg= "Message from Player " + to_string(player_id+1) + string(" - ") + msg;
          write_message(player_mq,msg);
        }
        if(a == 'b')
        {
          string msg = goldMine.getMessage();
          int player_id;
          string player_mq;
          for(int i = 0; i < 5; i++)
          {
            if(goldmap->pid[i] == getpid())
              player_id=i;
          }
          msg= "Message from Player " + to_string(player_id+1) + string(" - ") + msg;
          for(int i=0;i<5;i++)
          {
            if(i==0)
              player_mq="/ameyd_plr1";
            else if(i == 1)
              player_mq="/ameyd_plr2";
            else if(i == 2)
              player_mq="/ameyd_plr3";
            else if(i == 3)
              player_mq="/ameyd_plr4";
            else if(i == 4)
              player_mq="/ameyd_plr5";
            if((goldmap->pid[i] != getpid()) && (goldmap->pid[i] != 0))
              write_message(player_mq,msg);
          }
        }
        sem_post(my_sem_ptr);
      }
      sem_post(my_sem_ptr);
      sem_wait(my_sem_ptr);
      if(gameover)
      {
         int player_id;
         string msg;
          string player_mq;
          for(int i = 0; i < 5; i++)
          {
            if(goldmap->pid[i] == getpid())
              player_id=i;
          }
          msg= "Player " + to_string(player_id+1) + string(" is a winner");
          for(int i=0;i<5;i++)
          {
            if(i==0)
              player_mq="/ameyd_plr1";
            else if(i == 1)
              player_mq="/ameyd_plr2";
            else if(i == 2)
              player_mq="/ameyd_plr3";
            else if(i == 3)
              player_mq="/ameyd_plr4";
            else if(i == 4)
              player_mq="/ameyd_plr5";
            if((goldmap->pid[i] != getpid()) && (goldmap->pid[i] != 0))
            {
              kill(goldmap->pid[i],SIGUSR1);
              write_message(player_mq,msg);
            }
          }
      }
      for(int i=0;i<5; i++)
      {
        if(goldmap->pid[i]==getpid())
            goldmap->pid[i]=0;
      }
      goldmap->map[pos] &= ~current_player;
      for(int i=0;i<5; i++)
      {
        if((goldmap->pid[i] != 0) && (goldmap->pid[i] != getpid()))
          kill(goldmap->pid[i],SIGUSR1);
      }
      bool empty=true;
      for(int i=0;i<5; i++)
      {
        if(goldmap->pid[i] != 0)
            empty=false;
      }
      sem_post(my_sem_ptr);
      if(empty)
      {
        sem_unlink("/AMDgoldchase");
        shm_unlink("sharedmem");
      }
      mq_close(readqueue_fd);
      mq_unlink(mq_name.c_str());
  return 0;
}
