#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/list.h"
#include "../include/file.h"

struct node {
  int value;
  struct node *next;
};

struct list {
  int id;
  struct node *head;
  struct node *tail;
  int size;
};

int newList();
void list_help();
int invalid_id(int id);
int append_list(List list, int value);
void print_list(struct node *head);
int insert_nth_list(List list, int position, int value);
struct node *newNode(int value);

static struct list **list_library = NULL;
static int list_count = 0;

void list_main() {
  printf("欢迎来到链表操作模块\n");
  char input[MAX_INPUT];
  char *cmd;
  char *args[MAX_ARG];

  while(true) {
    printf("|-> ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
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
    int argc = 0;
    for (int i = 0; i < MAX_ARG; i++) {
      args[i] = NULL;
    }
    while ((args[argc] = strtok(NULL, " ")) != NULL && argc < MAX_ARG) {
      argc++;
    }
    if(argc > MAX_ARG) {
      continue;
    }

    if (strcmp(cmd, "c") == 0 || strcmp(cmd, "create") == 0) {
      if(args[0] == NULL) {
        if (newList()) {
          printf("添加失败\n");
          continue;
        }
        printf("添加成功\n");
        continue;
      }
      int num = atoi(args[0]);
      if (num == 0) {
        printf("这不是一个有效的数量\n");
        list_help();
        continue;
      }
      for (int i = 0; i < num; i++) {
        if (newList()) {
          printf("添加失败\n");
          break;
        }
      }
      printf("成功添加%d个链表\n", num);
      continue;
    }

    if (strcmp(cmd, "p") == 0 || strcmp(cmd, "print") == 0) {
      if(args[0] == NULL) {
          printf("链表数量: %d\n", list_count);
        for (int i = 0; i < list_count; i++) {
          printf("链表编号: %d 节点数量: %d\n", list_library[i]->id, list_library[i]->size);
        }
        continue;
      }
      int id = atoi(args[0]);
      if (invalid_id(id)) continue;
      print_list(list_library[id-1]->head);
      continue;
    }

    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "a") == 0) {
      if (args[0] == NULL) {
        printf("缺少链表编号\n");
        continue;
      }
      int id = atoi(args[0]);
      if (invalid_id(id)) continue;
      if (args[1] == NULL) {
        printf("请提供一个值\n");
        list_help();
        continue;
      }
      int value = atoi(args[1]);
      if ((value == 0) && strcmp(args[1], "0") != 0) {
        printf("请提供一个有效的值\n");
        list_help();
        continue;
      }
      if (append_list(list_library[id-1], value)){
        printf("添加节点失败");
        continue;
      }
      printf("添加新节点成功\n");
      continue;
    }

    if (strcmp(cmd, "q") == 0 || strcmp(cmd, "quit") == 0) {
      printf("感谢游玩\n");
      exit(1);
    }

    if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "e") == 0) {
      printf("退出链表操作模块\n");
      break;
    }

    if (strcmp(cmd, "?") == 0) {
      print_file("src/textfile/help_list_general.txt");
      continue;
    }

    if (strcmp(cmd, "i") == 0 || strcmp(cmd, "insert") == 0) {
      if (args[0] == NULL) {
        printf("缺少链表编号\n");
        continue;
      }
      int id = atoi(args[0]);
      if (invalid_id(id)) continue;
      if (args[1] == NULL) {
        printf("缺少位置\n");
        continue;
      }
      int position = atoi(args[1]);
      if (
        (position == 0 && strcmp(args[1], "0") != 0) ||
        position < 0
        ) {
        printf("请提供一个有效的位置\n");
        list_help();
        continue;
      }
      if (args[2] == NULL) {
        printf("缺少值\n");
        continue;
      }
      int value = atoi(args[2]);
      if (value == 0 && strcmp(args[2], "0") != 0) {
        printf("请提供一个有效的值\n");
        list_help();
        continue;
      }
      if (insert_nth_list(list_library[id-1], position, value)) {
        printf("插入元素失败\n");
        continue;
      }
      printf("插入元素成功\n");
      continue;
    }

    printf("命令还未实现，或者不存在\n");
    list_help();
  }
  
  

  

  

  

  
  
}

int newList() {
  List *new_library = realloc(list_library, (list_count + 1)* sizeof(List));
  if (new_library == NULL) {
    perror("重新分配内存失败\n");
    return 1;
  }
  list_library = new_library;
  list_library[list_count] = malloc(sizeof(struct list));
  if(list_library[list_count] == NULL) {
    perror("分配内存失败\n");
    return 1;
  }
  list_library[list_count]->head = NULL;
  list_library[list_count]->tail = NULL;
  list_library[list_count]->id = list_count + 1;
  list_library[list_count]->size = 0;
  list_count++;
  return 0;
}

int invalid_id(int id) {
  if (id == 0) {
    printf("这不是一个编号\n");
    return 1;
  } else if (id > list_count || id < 0) {
    printf("这是一个无效编号\n");
    return 1;
  } 
  return 0;
}

int append_list(List list, int value) {
  struct node *new = newNode(value);
  if (new == NULL) {
    printf("分配新节点失败\n");
    return 1;
  }
  if (list->head == NULL) {
    list->head = new;
    list->tail = new;
    list->size++;
    return 0;
  }
  struct node *curr = list->head;
  while(curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = new;
  list->tail = new;
  list->size++;
  return 0;
}

int insert_nth_list(List list, int position, int value) {
  struct node *new = newNode(value);
  if (new == NULL) return 1;

  if (position == 0) {
    new->next = list->head;
    list->head = new;
    if (list->size == 0) {
      list->tail = new;
    }
  } else if (position >= list->size) {
    list->tail->next = new;
    list->tail = new;
  } else {
    struct node *curr = list->head;
    for (int i = 0; i < position - 1; i++) {
      curr = curr->next;
    }
    new->next = curr->next;
    curr->next = new;
  }

  list->size++;
  return 0;
}

void print_list(struct node *head){
  struct node *curr = head;
  int index = 1;
  while(curr != NULL) {
    printf("节点%d 内容为: %d\n", index, curr->value);
    index++;
    curr = curr->next;
  }
}

void list_help() {
  printf("请输入 ? 查看帮助\n");
}

struct node *newNode(int value) {
  struct node *new = malloc(sizeof(struct node));
  new->value = value;
  new->next = NULL;
  return new;
}