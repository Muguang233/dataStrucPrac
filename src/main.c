#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file.h"
//////////////////////////////////////
              //宏定义
/////////////////////////////////////
#define MAX_BUFFER 2048
#define MAX_CMD 256
#define FAIL_MEM "分配内存失败\n"
#define MAX_ARG 5
#define command_count 4
//////////////////////////////////////
              //结构体
//////////////////////////////////////
struct command {
  char *cmd;
  int max_arg;
  char *arg_example;
  char *help_msg;
  bool strict_args;
};

static struct command Command_list[] = {
  {"q",     0, "{N/A}",               "退出程序", },
  {"?",     2, "{类型} {进阶}",       "获取帮助(数据结构指令为类型)"},
  {"list",  2, "{行动} {值}",         "链表操作"},
  {"t",     3, "{N/A} {N/A} {N/A}",   "测试测试"}
};




//////////////////////////////////////
            //函数命名
/////////////////////////////////////

//打印介绍
int intro();

//执行指令
void command();

//获取指令索引
int get_command_index();

//测试参数
void test_arg(int argc, char *arg[]);

//执行指令
void run_command(int argc, char *arg[], char *cmd);

//帮助指令
void help(int argc, char *arg[]);


//////////////////////////////////////
              //主函数
//////////////////////////////////////
int main() {
  if (intro()) {
    perror("无法打开文件");
    return 1;
  }
  command();
  int test;
  while (scanf(" %d", &test) != EOF) {
    printf("测试第二EOF");
  }
  return 0;
}




//////////////////////////////////////
              //辅助函数
//////////////////////////////////////
int intro() {

  printf("================ 欢迎界面 ================\n");

  print_file("src/textfile/intro.txt");

  for (int i = 0; i < 2; i++) {
    char *cmd = Command_list[i].cmd;
    char *help = Command_list[i].help_msg;
    printf("\n输入%s %s", cmd, help);
  }

  printf("\n==========================================\n");

  return 0;
}

void command() {
  char input[MAX_CMD];
  char *cmd;
  char *args[MAX_ARG];
  while(true) {
    printf("> ");
    if (fgets(input, MAX_CMD, stdin) == NULL) {
      return;
    }
    input[strcspn(input, "\n")] = '\0';
    if(input[0] == '\0') {
      continue;
    }
    cmd = strtok(input, " ");
    if (cmd == NULL) {
      continue;
    }
    int cmd_index = get_command_index(cmd);
    int argc = 0;
    for (int i = 0; i < Command_list[cmd_index].max_arg; i++) {
      args[i] = NULL;
    }
    while ((args[argc] = strtok(NULL, " ")) != NULL && argc < Command_list[cmd_index].max_arg) {
      argc++;
    }
    if(argc > Command_list[cmd_index].max_arg) {
      continue;
    }
    run_command(argc, args, cmd);
  }
}

void test_arg(int argc, char *arg[]) {
  for (int i = 0; i < argc; i++) {
    printf("这个指令的第%d个参数是%s\n", i, arg[i]);
  }
}

void run_command(int argc, char *arg[], char *cmd) {
  if (strcmp(cmd, "q") == 0) {
    printf("感谢游玩\n");
    exit(1);
  }
  if (strcmp(cmd, "?") == 0) {
    help(argc, arg);
    return;
  }
}

void help(int argc, char *arg[]) {
  if (arg[0] == NULL) {
    print_file("src/textfile/help_command.txt");
    return;
  }
  if (strcmp(arg[0], "list") == 0) {
    
  }
}

int get_command_index(char *cmd) {
  size_t command_list_length = sizeof(Command_list) / sizeof(Command_list[0]);
  int index = 0;
  for (int i = 0; i < command_list_length; i++) {
    if (strcmp(cmd, Command_list[i].cmd) == 0) {
      break;
    }
    index++;
  }
  return index;
}