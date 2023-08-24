#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <unistd.h>

/**
 * struct ptr_lst - A structure to hold a pointer and link to the next node.
 * @ptr: The pointer to store.
 * @next: A pointer to the next node in the list.
 */

typedef struct ptr_lst
{
	void *ptr;
	struct ptr_lst *next;
} table_lst;


char *prg_nm(char *name);
int enuml(int add);
void error_handle(char *command, int status, char *extra);
void signal_handler(int sg);
void file_handle(char *filename);
size_t __lenght_lst(table_lst *h);
table_lst *__node_insrt(table_lst **head, void *ptr);
table_lst *__node_insrt_tail(table_lst **head, void *ptr);
void __lst_free(table_lst *head);
void __lst_free_all(table_lst *head);
table_lst *__nodeget_indx(table_lst *head, unsigned int index);
table_lst *__nodeinsrt_indx(table_lst **head, unsigned int idx, void *ptr);
int __dlt_nodeindx(table_lst **head, unsigned int index);


/**
 * struct ptr_lst2 - singly linked list
 * @ptr: a malloced string
 * @next: points to the next node
 */
typedef struct ptr_lst2
{
	char *ptr;
	struct ptr_lst2 *next;
} sig_list;



size_t lenght_lst(sig_list *h);
sig_list *add_node(sig_list **head, char *ptr);
sig_list *node_insrt_tail(sig_list **head, char *ptr);
void lst_free(sig_list *head);
void lst_free_all(sig_list *head);
sig_list *node_get_index(sig_list *head, unsigned int index);
sig_list *node_insert_index(sig_list **head, unsigned int idx, char *ptr);
int delete_node_index(sig_list **head, unsigned int index);
char **arrayify_list(sig_list *);
sig_list *lstfy(char **);
void dbl_matrix_free(char **);


int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int count_strg(char *str, char *delim);
char *_strcat(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
int cmd_size(char **tokens);
int _isdigit(int c);
int nline(char *input);
void buff_shift(char *input, int newline_index, int filled);
char *_itoa(int num);
char *_strev(char *str, int n);
char *_memset(char *s, char b, int n);


void *memo_do(size_t size, void *ptr);
void exit_do(int fd, char *msg, int code);
ssize_t else_handle_input(char *lineptr, int stream, char *input, int filled);
ssize_t _getline(char *lineptr, int stream);
char **_strtok(char *str, char *delim);
char **get_dir_path();
char *get_env_val(char *name);
char *finddir_path(char **path, char *command);
char **get_env();


char **envrt_do(char *x, char *y);
char *all_cmd_get(char *path, char *command);


int setenv_builtin(char **tokens);
int builtinunsetenv(char **tokens);
int builtincd(char **tokens);
char **get_builtins();
int builtinenv(void);


int execute(char **tokens);
int nmbr_ext(char **tokens);
int ops_srch(char **tokens);
int builtinexec(char **tokens, int bcase);
int acc_check(char *comm, char *token);
char *exec_prp(char *token);
char *txtf_read(char *filename);

#endif
