#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/list.h"

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

static struct list **list_library = NULL;
static int list_count = 0;

void list_main(int argc, char *arg[]) {
  if (arg[0] == NULL) {
    printf("未找到命令\n");
    list_help();
    return;
  }

  if (strcmp(arg[0], "c") == 0) {
    if(arg[1] == NULL) {
      if (newList()) {
        printf("添加失败\n");
      }
      return;
    }
    int num = atoi(arg[1]);
    if (num == 0) {
      printf("这不是一个有效的数量\n");
      list_help();
      return;
    }
    for (int i = 0; i < num; i++) {
      if (newList()) {
        printf("添加失败\n");
        break;
      }
    }
    return;
  }

  if (strcmp(arg[0], "p") == 0) {
    if(arg[1] == NULL) {
        printf("链表数量: %d\n", list_count);
      for (int i = 0; i < list_count; i++) {
        printf("链表编号: %d 节点数量: %d\n", list_library[i]->id, list_library[i]->size);
      }
      return;
    }
    int id = atoi(arg[1]);
    if (invalid_id(id)) return;
    print_list(list_library[id-1]->head);
    return;
  }

  if (strcmp(arg[0], "add") == 0) {
    if (arg[1] == NULL) {
      printf("缺少链表编号\n");
      return;
    }
    int id = atoi(arg[1]);
    if (invalid_id(id)) return;
    if (arg[2] == NULL) {
      printf("请提供一个值\n");
      list_help();
      return;
    }
    int value = atoi(arg[2]);
    if ((value == 0) && strcmp(arg[2], "0") != 0) {
      printf("请提供一个有效的值\n");
      list_help();
      return;
    }
    if (append_list(list_library[id-1], value)){
      printf("添加节点失败");
    }
    return;
  }

  printf("命令还未实现，或者不存在\n");
  list_help();
  
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
  } else if (id > list_count) {
    printf("这是一个无效编号\n");
    return 1;
  }
  return 0;
}

int append_list(List list, int value) {
  struct node *newNode = malloc(sizeof(struct node));
  if (newNode == NULL) {
    printf("分配新节点失败\n");
    return 1;
  }
  newNode->next = NULL;
  newNode->value = value;
  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
    list->size++;
    return 0;
  }
  struct node *curr = list->head;
  while(curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = newNode;
  list->tail = newNode;
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
  printf("请输入 ? list 查看帮助\n");
}