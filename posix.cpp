#include "process_wrapper.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

bool create_pipe(pipe_t& p) {
    int pipe_fd[2];
    int cr_p = pipe(pipe_fd);
    if(cr_p == 0) {
        p.read_fd = pipe_fd[0];
        p.write_fd = pipe_fd[1];
        return true;
    } else {
        return false;
    }
}

bool create_child(const char* program_file, const char* out_file, pipe_t& p, process_t& child_process) {
    int f = fork();
    if(f == -1) {
        return false;
    }
    if(f > 0) {
        child_process.current_process = f;
        return true;
    }
    if(f == 0) {
        dup2(p.read_fd, 0);
        close(p.read_fd);
        close(p.write_fd);
        execlp(program_file, program_file, out_file, nullptr);
        _exit(1);
    }
}

int write_to_pipe(pipe_t& p, const char* data, int lenth) {
    return write(p.write_fd, data, lenth);
}

bool is_process_alive(process_t& pr) {
    int status;
    int w = waitpid(pr.current_process, &status, WNOHANG);
    if(w == 0) return true;
    return false;
}

void close_pipes_ends(pipe_t& p, bool read_fd_to_close, bool write_fd_to_close) {
    if(read_fd_to_close) {
        close(p.read_fd);
    }
    if(write_fd_to_close) {
        close(p.write_fd);
    }
}

int wait_child_end(process_t& child) {
    int status;
    return waitpid(child.current_process, &status, 0);
}

