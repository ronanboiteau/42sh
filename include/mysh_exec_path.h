#ifndef MYSH_EXEC_PATH_H_
# define MYSH_EXEC_PATH_H_

char		*get_exec_full_path(char *input, char **path);
t_uchar		chck_exec_path(char *exec_path, char **argv);

#endif /* !MYSH_EXEC_PATH_H_ */
