#include <iostream>

struct pipe_t {
    int read_fd;
    int write_fd;

};

struct process_t {
    int current_process;
};

bool create_pipe(pipe_t& pipe);

bool create_child(const char* exec_file, const char* arg_file, pipe_t& pipe, process_t& out_process);

int write_to_pipe(pipe_t& pipe, const char* data, int lenth);

bool is_process_alive(process_t& process);

void close_pipes_ends(pipe_t& pipe, bool read_fd_to_close, bool write_fd_to_close);

int wait_child_end(process_t& child);
