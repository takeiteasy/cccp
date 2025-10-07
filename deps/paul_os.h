/* paul/paul_os.h -- https://github.com/takeiteasy/paul

 Copyright (C) 2024  George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/*!
 @header paul_os.h
 @copyright George Watson GPLv3
 @updated 2025-07-19
 @brief Cross-platform file, path, and system utilities for C/C++.
 @discussion
    Implementation is included when PAUL_OS_IMPLEMENTATION or PAUL_IMPLEMENTATION is defined. 
    On MacOS optional Cocoa support can be enabled by defining PAUL_OS_USE_COCOA and linking
    against `-framework Foundation.framework`.
*/

#ifndef PAUL_OS_H
#define PAUL_OS_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __has_include
#define __has_include(x) 0
#endif
#ifndef __has_extension
#define __has_extension(x) 0
#endif

#if __has_include(<sys/param.h>)
#include <sys/param.h>
#endif

#ifdef __EMSCRIPTEN__
#define PAUL_OS_NO_NATIVE
#endif

#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#elif defined(__linux__) || defined(__LINUX__) || \
      defined(__unix__)  || defined(__UNUX__)  || \
      defined(BSD)       || defined(__BSD__)
#define PLATFORM_NIX
#else
#define PLATFORM_UNKNOWN
#endif

#if defined(PLATFORM_MACOS) || defined(PLATFORM_NIX)
#define PLATFORM_POSIX
#endif

#if defined(__clang__) || defined(__GNUC__)
#if __has_extension(blocks)
#define PLATFORM_HAS_BLOCKS
#if __has_include(<Block.h>)
#include <Block.h>
#endif
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <wchar.h>
#include <errno.h>
#include <signal.h>
#include <poll.h>
#include <fcntl.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <io.h>
#include <processthreadsapi.h>
#include <synchapi.h>
#include <shlobj.h>
#include <objbase.h>
#include <combaseapi.h>
#include <KnownFolders.h>
#else
#ifdef PLATFORM_MACOS
#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/NSObjCRuntime.h>
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#endif

#ifndef MAX_PATH
#if defined(PLATFORM_MACOS)
#define MAX_PATH 255
#elif defined(PLATFORM_WINDOWS)
#define MAX_PATH 256
#elif defined(PLATFORM_NIX)
#define MAX_PATH 4096
#else
#define MAX_PATH 1024
#endif
#endif

#ifdef PLATFORM_WINDOWS
#define PATH_SEPARATOR '\\'
#define PATH_SEPARATOR_STR "\\"
#else
#define PATH_SEPARATOR '/'
#define PATH_SEPARATOR_STR "/"
#endif

#ifdef PLATFORM_WINDOWS
#define IO_IN STD_INPUT_HANDLE
#define IO_OUT STD_OUTPUT_HANDLE
#define IO_ERR STD_ERROR_HANDLE
#else
#define IO_IN STDIN_FILENO
#define IO_OUT STDOUT_FILENO
#define IO_ERR STDERR_FILENO
#endif

#ifdef PLATFORM_WINDOWS
typedef HANDLE file_handle_t;
#elif defined(PLATFORM_POSIX)
typedef int file_handle_t;
#else
typedef FILE* file_handle_t;
#endif

/*!
 @typedef file_t
 @field fd Underlying file handler
 @discussion file_t is a wrapper around OS specific file handlers
*/
typedef struct file {
    file_handle_t fd;
} file_t;

#ifdef PLATFORM_WINDOWS
#define INVALID_FILE_HANDLE INVALID_HANDLE_VALUE
#else
#define INVALID_FILE_HANDLE -1
#endif

/*!
 @const io_invalid
 @discussion Invalid file handler (-1)
*/
extern const file_t io_invalid;
/*!
 @const io_out
 @discussion Standard out
*/
extern const file_t io_out;
/*!
 @const io_err
 @discussion Standard error
*/
extern const file_t io_err;
/*!
 @const io_in
 @discussion Standard in
*/
extern const file_t io_in;

/*!
 @function io_print
 @param IO File stream to write to
 @param MSG Message to print
 @brief Print a message to a file stream
*/
#define io_print(IO, MSG)             \
    do                                \
    {                                 \
        if (io_valid(IO))             \
            io_write_string(IO, MSG); \
    } while (0)
/*!
 @function io_println
 @param IO File stream to write to
 @param MSG Message to print
 @brief Print a message to a file stream with a newline
*/
#define io_println(IO, MSG)     \
    do                          \
    {                           \
        io_print(IO, MSG);      \
        io_print(IO, "\n")      \
    } while(0)
/*!
 @function print
 @param MSG Message to print
 @brief Print a message to standard out
*/
#define print(MSG)       io_print(io_out, MSG)
/*!
 @function println
 @param MSG Message to print
 @brief Print a message to standard out with a newline
*/
#define println(MSG)     io_println(io_out, MSG)
/*!
 @function print_err
 @param MSG Message to print
 @brief Print a message to standard error
*/
#define print_err(MSG)   io_print(io_err, MSG)
/*!
 @function println_err
 @param MSG Message to print
 @brief Print a message to standard error with a newline
*/
#define println_err(MSG) io_println(io_err, MSG)

/*!
 @enum file_mode_t
 @constant FILE_READ File read flag (r)
 @constant FILE_WRITE File write flag (w)
 @constant FILE_APPEND File append flag (a)
 @discussion File permissions for io_open
*/
enum file_mode_t {
    FILE_READ   = 0x00000001,
    FILE_WRITE  = 0x00000002,
    FILE_APPEND = 0x00000004
};

/*!
 @enum file_seek_t
 @constant FILE_START Beginning of file marker (SEEK_SET)
 @constant FILE_CURSOR Current file position marker (SEEK_CUR)
 @constant FILE_FINISH End of file marker (SEEK_END)
 @discussion File offset positions for io_seek
*/
enum file_seek_t {
    FILE_START  = 0,
    FILE_CURSOR,
    FILE_FINISH
};

/*!
 @function io_open
 @param dst File steam destination
 @param path Path to file
 @param mode File steam access mode(s)
 @brief Open file stream
*/
bool io_open(file_t *dst, const char* path, enum file_mode_t mode);
/*!
 @function io_close
 @param file Pointer to file steam to close
 @return Returns true/false on success
 @brief Close file stream
*/
bool io_close(file_t *file);
/*!
 @function io_read
 @param file File stream to read from
 @param buffer Buffer to read to
 @param size Size of the destination buffer
 @return Returns true/false on success
 @brief Read n bytes from file stream
 @discussion Please ensure that size >= destination buffer size
*/
size_t io_read(file_t file, void *buffer, size_t size);
/*!
 @function io_write
 @param file File stream to write to
 @param buffer Source buffer to write
 @param size Number of bytes to write
 @return Returns number of bytes read, -1 on error
 @brief Write n bytes to file stream
 @discussion Please ensure that size is >= the source buffer size
*/
size_t io_write(file_t file, const void *buffer, size_t size);
/*!
 @function io_seek
 @param file File stream to modify
 @param offset The number of bytes to seek
 @param whence The offset of the seek
 @return Returns true/false on success
 @brief Seek file stream position
*/
bool io_seek(file_t file, long offset, enum file_seek_t whence);
/*!
 @function io_advance
 @param file File stream to modify
 @param offset Number of bytes to seek
 @return Returns true/false on success
 @brief Advance the file stream cursor by n bytes
*/
bool io_advance(file_t file, long offset);
/*!
 @function io_tell
 @param file File stream to check
 @return Returns the current file stream position, -1 on error
 @brief Get current position of file stream
*/
size_t io_tell(file_t file);
/*!
 @function io_eof
 @param file File stream to check
 @return Returns true is file is at the end
 @brief Check if file is at the end
*/
bool io_eof(file_t file);
/*!
 @function io_flush
 @param file File stream to flush
 @return Returns true/false on success
 @brief Flush file stream
*/
bool io_flush(file_t file);
/*!
 @function io_valid
 @param file File stream to check
 @return Check if a file stream is valid
 @brief Check if a file stream is valid
*/
bool io_valid(file_t file);
/*!
 @function io_read_line
 @param file File stream to read
 @param buffer Destination buffer
 @param size Size of destination buffer
 @return Returns true/false on success
 @brief Read until newline or end of file
*/
bool io_read_line(file_t file, char *buffer, size_t size);
/*!
 @function io_write_string
 @param file File stream to write to
 @param str String to write
 @return Returns true/false on success
 @brief Write a string to a file stream
*/
bool io_write_string(file_t file, const char *str);
/*!
 @function io_truncate
 @param file File stream to modify
 @param size Offset bytes
 @return Returns true/false on success
 @brief Truncate a file stream to a specific length
*/
bool io_truncate(file_t file, long size);

/*!
 @function environment_variable
 @param name Variable name
 @return Returns enviroment variable string or NULL on failure
 @brief Get an enviroment variable
 @discussion Return value will need to be freed on success
*/
char* environment_variable(const char *name); // !

/*!
 @enum shell_error_t
 @constant SHELL_OK No error
 @constant SHELL_ERR_GENERIC Generic error
 @constant SHELL_ERR_TOKENIZE Error tokenizing command
 @constant SHELL_ERR_EVAL Error evaluating command
 @constant SHELL_ERR_PIPE Error creating pipe
 @constant SHELL_ERR_FORK Error forking process
 @constant SHELL_ERR_READ Error reading from pipe
 @discussion Error codes for shell() function
*/
typedef enum shell_error {
    SHELL_OK = 0,
    SHELL_ERR_GENERIC = -1,
    SHELL_ERR_TOKENIZE = -2,
    SHELL_ERR_EVAL = -3,
    SHELL_ERR_PIPE = -4,
    SHELL_ERR_FORK = -5,
    SHELL_ERR_READ = -6
} shell_error_t;

/*!
 @typedef shell_stream_cb_t
 @brief Callback type for streaming output
*/
typedef void (*shell_stream_cb_t)(const char *data, size_t len, void *userdata);

/*!
 @struct shell_io
 @field out Captured stdout buffer (NUL-terminated)
 @field out_len Length of captured stdout buffer
 @field err Captured stderr buffer (NUL-terminated)
 @field err_len Length of captured stderr buffer
 @field in Input buffer to write to child's stdin
 @field in_len Length of input buffer
 @field out_cb Callback for streaming stdout chunks
 @field err_cb Callback for streaming stderr chunks
 @field userdata User data pointer passed to callbacks
 @brief I/O capture and streaming control structure
 @discussion 
    shell_io is used to control input/output capture and streaming for the shell function.
    It allows capturing stdout and stderr into buffers or streaming them via callbacks.
    Input can be provided to the child process via a buffer.
    Callbacks receive chunks of data as they arrive, useful for large outputs.
    When callbacks are used, output buffers are not populated.
    The caller is responsible for freeing captured output buffers when done.
*/
typedef struct shell_io {
    /* I/O capture and streaming control structure
     *
     * - Pass a non-NULL `shell_io *` to `shell()` to enable capture/streaming.
     * - If `out_cb` and/or `err_cb` are set, `shell()` invokes the callback
     *   as chunks of data arrive on the child's STDOUT/STDERR. When callbacks
     *   are provided, `shell()` does NOT fill the `out`/`err` buffers (they
     *   will remain NULL). Callbacks are useful for streaming large outputs
     *   without buffering everything in memory.
     * - If callbacks are NULL, `shell()` accumulates the full contents of
     *   STDOUT and STDERR into freshly allocated, NUL-terminated buffers
     *   stored in `out` and `err` respectively. The sizes are in `out_len`
     *   and `err_len`. The caller is responsible for calling `free()` on
     *   `out` and `err` when done.
     * - To provide input to the child, set `in` to a buffer of length
     *   `in_len`. `shell()` will write the contents of `in` to the child's
     *   STDIN and then close it. Ownership of `in` stays with the caller.
     * - Return values: non-negative return values are the child's exit code.
     *   Negative return values are library-level errors (see SHELL_ERR_*).
     */
    /* Captured output buffers (allocated by shell() when callbacks are NULL). */
    char *out;    /* captured stdout (NUL-terminated) */
    size_t out_len;
    char *err;    /* captured stderr (NUL-terminated) */
    size_t err_len;

    /* Input to be written to child's STDIN before closing it. Not modified by shell(). */
    const char *in;
    size_t in_len;

    /* Streaming callbacks. If non-NULL, shell() will call these with each
     * incoming chunk. Callbacks receive `userdata` as the last argument.
     * When callbacks are used, `out`/`err` buffers are not populated.
     */
    shell_stream_cb_t out_cb;
    shell_stream_cb_t err_cb;
    void *userdata;
} shell_io;

/*!
 @function shell
 @param command Command to execute
 @param io Capture structure, NULL to ignore (no capture output)
 @return Returns the exit code of the command, negative on internal error
 @brief Execute a shell command
 @discussion Execute a shell command (bourne shell syntax, |, >, <, &&, ;)
*/
int shell(const char *command, shell_io *io);

/*!
 @function shell_fmt
 @param io Capture structure, NULL to ignore (no capture output)
 @param command Command to execute (formatted)
 @param ... printf style format arguments for command
 @return Returns the exit code of the command, negative on internal error
 @discussion shell with printf formatting
*/
int shell_fmt(shell_io *io, const char *command, ...);

/*!
 @function file_exists
 @param path Path to file
 @return Returns true if file exists
 @brief Check if a file exists
 @discussion Checks if a path exists and is a file (directory will return false)
*/
bool file_exists(const char *path);
/*!
 @function file_delete
 @param path Path to file
 @return Returns true/false on success
 @brief Delete a file from file system
*/
bool file_delete(const char *path);
/*!
 @function file_rename
 @param old_path Path to file to rename
 @param new_path New path for file
 @param write_over Write over existing files when moving
 @return Returns true/false on success
 @brief Move a file
 @discussion WIP
*/
bool file_rename(const char *old_path, const char *new_path, bool write_over);
/*!
 @function file_copy
 @param src_path Path to original file
 @param dst_path Path to copy
 @param write_over Write over existing files when moving
 @return Returns true/false on success
 @brief Copy a file
 @discussion WIP
*/
bool file_copy(const char *src_path, const char *dst_path, bool write_over);
/*!
 @function file_size
 @param path Path to file
 @return Returns size of a file, -1 on error
 @brief Get file size
*/
int file_size(const char *path);
/*!
 @function file_read
 @param path Path to file
 @param size Pointer to recieve file size
 @return Returns the contents of a file
 @brief Read a file from disk
 @discussion Return value will need to be freed on success
*/
const char* file_read(const char *path, size_t *size);  // !

/*!
 @function directory_exists
 @param path Path to directory
 @return Returns true if file exists
 @brief Check if a directory exists
 @discussion Checks if a path exists and is a directory (file will return false)
*/
bool directory_exists(const char *path);
/*!
 @function directory_create
 @param path Path to directory
 @param recursive If this is true, will create any required parent directories
 @return Returns true/false on success
 @brief Create a directory
 @discussion WIP
*/
bool directory_create(const char *path, bool recursive);
/*!
 @function directory_delete
 @param path Path to directory
 @param recursive If this is true, it will delete and child directories too
 @param and_files If this is ture, it will delete and files inside the directory
 @return Returns true/false on success
 @brief Delete a directory
 @discussion WIP
*/
bool directory_delete(const char *path, bool recursive, bool and_files);
/*!
 @function directory_rename
 @param old_path Path to directory
 @param new_path Path to directory to move to
 @param write_over If this is true, write over any existing files when copying
 @return Returns true/false on success
 @brief Move a directory
 @discussion WIP
*/
bool directory_rename(const char *old_path, const char *new_path, bool write_over);
/*!
 @function directory_copy
 @param src_path Path to directory
 @param dst_path Path copy directory to
 @param write_over If this is true, write over any existing files when copying
 @param delete_src If this is true, delete the original directory and files after copy succeeds
 @return Returns true/false on success
 @brief Copy a directory and contents
*/
bool directory_copy(const char *src_path, const char *dst_path, bool write_over, bool delete_src);
/*!
 @function directory_size
 @param path Path to directory
 @return Returns size of directory contents, -1 on error
 @brief Get the size of a directory
*/
int directory_size(const char *path);
/*!
 @function directory_item_count
 @param path Path to directory
 @param recursive If this is true, child directories will also be counted
 @return Returns number of items in directory, -1 on error
 @brief Get the number of files/directories inside a directory
*/
int directory_item_count(const char *path, bool recursive);
/*!
 @function directory_file_count
 @param path Path to directory
 @param recursive If this is true, child directories will also be counted
 @return Returns number of files in directory, -1 on error
 @brief Get the number of files inside a directory
 @discussion This doesn't count directories
*/
int directory_file_count(const char *path, bool recursive);
/*!
 @function directory_glob
 @param pattern Glob pattern to match
 @param count Pointer to an integer to store the number of matches
 @return Returns an array of strings containing the matched file paths, or NULL on error
 @brief Glob a directory for files matching a pattern
 @discussion The result must be freed by the caller.
             The count will be set to the number of matches.
             The array and its elements must be freed by the caller.
*/
const char** directory_glob(const char *pattern, int *count); // !!

/*!
 @typedef dir_t
 @field path Path to directory
 @discussion dir_t is a wrapper around OS specific directory iterators
*/
typedef struct dir {
    const char *path;
#ifdef PLATFORM_WINDOWS
    WIN32_FIND_DATA findData;
    HANDLE hFind;
#elif defined(PLATFORM_POSIX)
    DIR *dir;
#endif
} dir_t;

/*!
 @function directory_iter
 @param dir Pointer to dir_t structure
 @param is_dir Pointer to bool to store if the current item is a directory
 @return Returns the name of the next item in the directory, or NULL if there are no more items
 @brief Iterate through a directory
 @discussion If you need to exit an iteration early, call directory_iter_end(dir)
*/
const char* directory_iter(dir_t *dir, bool *is_dir);
/*!
 @function directory_iter_end
 @param dir Pointer to dir_t structure
 @brief End a directory iteration prematurely
 @discussion This will close the directory iterator and free any resources used.
             Normally this will be done at the end of the iteration.
*/
void directory_iter_end(dir_t *dir);

/*!
 @typedef glob_callback
 @param pattern The glob pattern
 @param filename The filename that matches the pattern
 @param userdata User data pointer
 @return Returns 0 to continue iteration, non-zero to stop
*/
typedef int(*glob_callback)(const char* pattern, const char* filename, void* userdata);
/*!
 @typedef walk_callback
 @param path The current path being walked
 @param filename The filename in the current path
 @param userdata User data pointer
 @return Returns 0 to continue walking, non-zero to stop
*/
typedef int(*walk_callback)(const char* path, const char* filename, void* userdata);
/*!
 @function path_glob
 @param pattern The glob pattern to match
 @param callback Callback function to call for each match
 @param userdata User data pointer to pass to the callback
 @return Returns true/false on success
 @brief Glob a pattern and call a callback for each match
*/
bool path_glob(const char *pattern, glob_callback callback, void *userdata);
/*!
 @function path_walk
 @param path The path to walk
 @param recursive If this is true, it will walk recursively
 @param callback Callback function to call for each file/directory
 @param userdata User data pointer to pass to the callback
 @return Returns true/false on success
 @brief Walk a directory and call a callback for each file/directory
*/
bool path_walk(const char *path, bool recursive, walk_callback callback, void *userdata);

#ifdef PLATFORM_HAS_BLOCKS
/*!
 @typedef glob_block
 @param pattern The glob pattern
 @param filename The filename that matches the pattern
 @param userdata User data pointer
 @return Returns 0 to continue iteration, non-zero to stop
 @discussion This is a block version of glob_callback. Blocks are a clang/gcc extension. -fblocks must be enabled to use this.
*/
typedef int(^glob_block)(const char* pattern, const char* filename, void* userdata);
/*!
 @typedef walk_block
 @param path The current path being walked
 @param filename The filename in the current path
 @param userdata User data pointer
 @return Returns 0 to continue walking, non-zero to stop
 @discussion This is a block version of walk_callback. Blocks are a clang/gcc extension. -fblocks must be enabled to use this.
*/
typedef int(^walk_block)(const char* path, const char* filename, void* userdata);
/*!
 @function path_glob_block
 @param pattern The glob pattern to match
 @param callback Block to call for each match
 @param userdata User data pointer to pass to the block
 @return Returns true/false on success
 @brief Glob a pattern and call a block for each match
 @discussion Blocks are a clang/gcc extension. -fblocks must be enabled to use this.
*/
bool path_glob_block(const char *pattern, glob_block callback, void *userdata);
/*!
 @function path_walk_block
 @param path The path to walk
 @param recursive If this is true, it will walk recursively
 @param callback Block to call for each file/directory
 @param userdata User data pointer to pass to the block
 @return Returns true/false on success
 @brief Walk a directory and call a block for each file/directory
 @discussion Blocks are a clang/gcc extension. -fblocks must be enabled to use this.
*/
bool path_walk_block(const char *path, bool recursive, walk_block callback, void *userdata);
#endif

/*!
 @function path_exists
 @param path The path to check
 @return Returns true/false on success
 @brief Check if a path exists. This will return true for both files and directories.
*/
bool path_exists(const char *path);
/*!
 @function path_get_working_directory
 @return Returns the current working directory
 @brief Get the current working directory
*/
const char* path_get_working_directory(void);
/*!
 @function path_set_working_directory
 @param path The path to set as the working directory
 @return Returns true/false on success
 @brief Set the current working directory
*/
bool path_set_working_directory(const char *path);

/*!
 @function path_get_root_dir
 @return Returns the root directory
 @brief Get the root directory
*/
const char* path_get_root_dir(void);
/*!
 @function path_get_home_dir
 @return Returns the home directory
 @brief Get the home directory
*/
const char* path_get_home_dir(void);
/*!
 @function path_get_documents_dir
 @return Returns the documents directory
 @brief Get the documents directory
*/
const char* path_get_documents_dir(void);
/*!
 @function path_get_downloads_dir
 @return Returns the downloads directory
 @brief Get the downloads directory
*/
const char* path_get_downloads_dir(void);
/*!
 @function path_get_video_dir
 @return Returns the video directory
 @brief Get the video directory
*/
const char* path_get_video_dir(void);
/*!
 @function path_get_music_dir
 @return Returns the music directory
 @brief Get the music directory
*/
const char* path_get_music_dir(void);
/*!
 @function path_get_picture_dir
 @return Returns the picture directory
 @brief Get the picture directory
*/
const char* path_get_picture_dir(void);
/*!
 @function path_get_application_dir
 @return Returns the application directory
 @brief Get the application directory
*/
const char* path_get_application_dir(void);
/*!
 @function path_get_desktop_dir
 @return Returns the desktop directory
 @brief Get the desktop directory
*/
const char* path_get_desktop_dir(void);

/*!
 @function path_get_file_extension
 @param path The path to get the file extension from
 @return Returns the file extension or NULL if there is no extension
 @brief Get the file extension from a path
*/
const char* path_get_file_extension(const char *path);
/*!
 @function path_get_file_name
 @param path The path to get the file name from
 @return Returns the file name or NULL if there is no file name
 @brief Get the file name from a path
*/
const char* path_get_file_name(const char *path);
/*!
 @function path_get_file_name_no_extension
 @param path The path to get the file name without extension from
 @return Returns the file name without extension or NULL if there is no file name
 @brief Get the file name without extension from a path
 @discussion The result must be freed by the caller.
*/
const char* path_get_file_name_no_extension(const char *path);  // !
/*!
 @function path_without_file_name
 @param path The path to get the directory name from
 @return Returns the directory name or NULL if there is no directory name
 @brief Get the directory name from a path
 @discussion The result must be freed by the caller.
*/
const char* path_without_file_name(const char *path);  // !
/*!
 @function path_get_directory_name
 @param path The path to get the directory name from
 @return Returns the directory name or NULL if there is no directory name
 @brief Get the directory name from a path
 @discussion The result must be freed by the caller.
*/
const char* path_get_directory_name(const char *path); // !
/*!
 @function path_get_parent_directory
 @param path The path to get the parent directory from
 @return Returns the parent directory or NULL if there is no parent directory
 @brief Get the parent directory from a path
 @discussion The result must be freed by the caller.
*/
const char* path_get_parent_directory(const char *path); // !

/*!
 @function path_resolve
 @param path The path to resolve
 @return Returns the resolved path or NULL on error
 @brief Resolve a path to an absolute path
 @discussion This will attempt to resolve ~ to the user's home directory and ".." to the parent directory. The result must be freed by the caller. WIP.
*/
const char* path_resolve(const char *path); // !
/*!
 @function path_join
 @param a The first path
 @param b The second path
 @return Returns the joined path or NULL on error
 @brief Join two paths together
 @discussion The result must be freed by the caller.
*/
const char* path_join(const char *a, const char *b); // !
/*!
 @function path_join_va
 @param n The number of paths to join
 @param ... The paths to join
 @return Returns the joined path or NULL on error
 @brief Join multiple paths together
 @discussion The result must be freed by the caller.
*/
const char* path_join_va(int n, ...); // !
/*!
 @function path_split
 @param path The path to split
 @param count Pointer to an integer to store the number of parts
 @return Returns an array of strings containing the parts of the path, or NULL on error
 @brief Split a path into its components
 @discussion The result must be freed by the caller.
             The count will be set to the number of parts.
             The array and its elements must be freed by the caller.
*/
const char** path_split(const char *path, size_t *count); // !!

#ifdef __cplusplus
}
#endif
#endif // PAUL_OS_H

#if defined(PAUL_OS_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION)
const file_t io_invalid = {.fd=INVALID_FILE_HANDLE};
const file_t io_out = {.fd=IO_OUT};
const file_t io_err = {.fd=IO_ERR};
const file_t io_in  = {.fd=IO_IN};

bool io_open(file_t *dst, const char* path, enum file_mode_t mode) {
    if (!dst || !path)
        return false;
#ifdef PLATFORM_WINDOWS
    DWORD access = 0;
    DWORD creation = 0;
    if (mode & FILE_READ)
        access |= GENERIC_READ;
    if (mode & FILE_WRITE)
        access |= GENERIC_WRITE;
    if (mode & FILE_APPEND)
        access |= FILE_APPEND_DATA;
        if (!(mode & FILE_WRITE))
            access |= GENERIC_WRITE;
    }

    if ((mode & FILE_READ) && !(mode & (FILE_WRITE | FILE_APPEND)))
        creation = OPEN_EXISTING;
    else if ((mode & (FILE_WRITE | FILE_APPEND))) {
        creation = OPEN_ALWAYS & (((mode & FILE_WRITE) && !(mode & FILE_APPEND)) ? CREATE_ALWAYS : OPEN_ALWAYS);
    else
        return false;

    if ((dst->fd = CreateFileA(path, access,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               creation,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL)) == INVALID_FILE_HANDLE)
        return false;
    if (mode & FILE_APPEND)
        SetFilePointer(dst->fd, 0, NULL, FILE_END);
#elif defined(PLATFORM_POSIX)
    int flags = 0;
    mode_t file_permissions = 0644;
    if (mode & FILE_READ)
        flags |= mode & (FILE_WRITE | FILE_APPEND) ? O_RDWR : O_RDONLY;
    else if (mode & (FILE_WRITE | FILE_APPEND))
        flags |= O_WRONLY;
    else
        return false;

    if (mode & (FILE_WRITE | FILE_APPEND))
        flags |= O_CREAT;
    if (mode & FILE_WRITE && !(mode & FILE_APPEND))
        flags |= O_TRUNC;
    if (mode & FILE_APPEND)
        flags |= O_APPEND;
    if ((dst->fd = open(path, flags, file_permissions)) == INVALID_FILE_HANDLE)
        return false;
#else
    char buffer[3];
    if (mode & FILE_READ) {
        buffer[0] = 'r';
        buffer[1] = mode & FILE_APPEND ? '+' : '\0';
    } else if (mode & FILE_WRITE) {
        buffer[0] = 'w';
        buffer[1] = mode & FILE_APPEND ? '+' : '\0';
    } else if (mode & FILE_APPEND) {
        buffer[0] = 'a';
        buffer[1] = '\0';
    }
    buffer[2] = '\0';
    if (!(dst->fd = fopen(path, buffer)))
        return false;
#endif
    return true;
}


bool io_close(file_t *file) {
    if (!file || !io_valid(*file))
        return false;
    bool result = false;
#ifdef PLATFORM_WINDOWS
    result = CloseHandle(file->fd) != 0;
#elif defined(PLATFORM_POSIX)
    result = close(file->fd) == 0;
#else
    result = fclose(file->fd) == 0;
#endif
    file->fd = INVALID_FILE_HANDLE;
    return result;
}

size_t io_read(file_t file, void *buffer, size_t size) {
    if (!io_valid(file) || !buffer || size <= 0)
        return 0;
#ifdef PLATFORM_WINDOWS
    DWORD bytes_read;
    BOOL result = ReadFile(file.fd, buffer, (DWORD)size, &bytes_read, NULL);
    return result ? bytes_read : 0;
#elif defined(PLATFORM_POSIX)
    return read(file.fd, buffer, size);
#else
    return fread(buffer, size, 1, file.fd);
#endif
}

size_t io_write(file_t file, const void *buffer, size_t size) {
    if (!io_valid(file) || !buffer || size <= 0)
        return 0;
#ifdef PLATFORM_WINDOWS
    DWORD bytes_written;
    BOOL result = WriteFile(file.fd, buffer, (DWORD)size, &bytes_written, NULL);
    return result ? bytes_written : 0;
#elif defined(PLATFORM_POSIX)
    return write(file.fd, buffer, size);
#else
    return fwrite(buffer, size, 1, file.fd);
#endif
}

bool io_seek(file_t file, long offset, enum file_seek_t whence) {
    if (!io_valid(file))
        return false;
#ifdef PLATFORM_WINDOWS
    DWORD move_method;
    switch (whence) {
        case FILE_START:
            move_method = FILE_BEGIN;
            break;
        case FILE_CURSOR:
            move_method = FILE_CURRENT;
            break;
        case FILE_FINISH:
            move_method = FILE_END;
            break;
        default:
            return false;
    }
    return SetFilePointer(file.fd, offset, NULL, move_method) != INVALID_SET_FILE_POINTER;
#elif defined(PLATFORM_POSIX)
    return lseek(file.fd, offset, whence) != -1;
#else
    return fseek(file.fd, offset, whence) == 0;
#endif
}

bool io_advance(file_t file, long offset) {
    return io_seek(file, offset, FILE_CURSOR);
}

size_t io_tell(file_t file) {
    if (!io_valid(file))
        return -1;
#ifdef PLATFORM_WINDOWS
    return (size_t)SetFilePointer(file.fd, 0, NULL, FILE_CURRENT);
    if (pos == INVALID_SET_FILE_POINTER)
        return false;
    if (position)
        *position = (long)pos;
#elif defined(PLATFORM_POSIX)
    return (size_t)lseek(file.fd, 0, FILE_CURSOR);
#else
    return (size_t)fseek(file.fd);
#endif
    return -1;
}

bool io_eof(file_t file) {
    if (!io_valid(file))
        return true;
#ifdef PLATFORM_WINDOWS
    DWORD current_pos = SetFilePointer(file.fd, 0, NULL, FILE_CURRENT);
    if (current_pos == INVALID_SET_FILE_POINTER)
        return true;
    DWORD fsize = GetFileSize(file.fd, NULL);
    if (fsize == INVALID_FILE_SIZE)
        return true;
    return current_pos >= fsize;
#elif defined(PLATFORM_POSIX)
    off_t current_pos = lseek(file.fd, 0, FILE_CURSOR);
    if (current_pos == -1)
        return true;
    off_t end_pos = lseek(file.fd, 0, FILE_FINISH);
    if (end_pos == -1)
        return true;
    lseek(file.fd, current_pos, FILE_START);
    return current_pos >= end_pos;
#else
    return feof(file.fd);
#endif
}

bool io_flush(file_t file) {
    if (!io_valid(file))
        return false;
#ifdef PLATFORM_WINDOWS
    return FlushFileBuffers(file.fd) != 0;
#elif defined(PLATFORM_POSIX)
    return fsync(file.fd) == 0;
#else
    return fflush(file.fd) == 0;
#endif
}

bool io_valid(file_t file) {
#ifdef PLATFORM_UNKNOWN
    return file.fd != NULL;
#else
    return file.fd >= 0;
#endif
}

bool io_read_line(file_t file, char *buffer, size_t buffer_size) {
    if (!io_valid(file) || !buffer || buffer_size <= 0)
        return false;
    size_t pos = 0;
    char ch;
    while (pos < buffer_size - 1) {
        if (io_read(file, &ch, 1) != 1)
            break;
        if (ch == '\n')
            break;
        if (ch != '\r')
            buffer[pos++] = ch;
    }
    buffer[pos] = '\0';
    return pos > 0 || !io_eof(file);
}

bool io_write_string(file_t file, const char *str) {
    if (!io_valid(file) || !str)
        return false;
    size_t len = strlen(str);
    if (!len)
        return true;
    return io_write(file, str, len) == len;
}

bool io_truncate(file_t file, long size) {
    if (!io_valid(file) || size < 0)
        return false;
#ifdef PLATFORM_WINDOWS
    if (SetFilePointer(file.fd, size, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        return false;
    return SetEndOfFile(file.fd) != 0;
#elif defined(PLATFORM_POSIX)
    return ftruncate(file.fd, size) == 0;
#else
    long fsize, pos;
    if ((pos = io_tell(file)) == -1||
        !io_seek(file, 0, FILE_FINISH) ||
        (fsize = io_tell(file)) == -1)
        return false;
    return size > fsize ? true : io_seek(file, pos <= size ? pos : size, FILE_CURSOR);
#endif
}

#if defined(PLATFORM_POSIX)
extern char **environ;
#endif

char* environment_variable(const char *var_name) {
    if (!var_name)
        return NULL;
#ifdef PLATFORM_WINDOWS
    DWORD buffer_size = GetEnvironmentVariableA(var_name, NULL, 0);
    if (!buffer_size)
        return NULL;
    char* value = (char*)malloc(buffer_size * sizeof(char));
    if (!value)
        return NULL;
    DWORD result = GetEnvironmentVariableA(var_name, value, buffer_size);
    if (result == 0 || result >= buffer_size) {
        free(value);
        return NULL;
    }
    return value;
#elif defined(PLATFORM_POSIX)
    for (int i = 0; environ[i] != NULL; i++) {
        char* env_str = environ[i];
        char* equals_sign = NULL;
        for (int j = 0; env_str[j] != '\0'; j++)
            if (env_str[j] == '=') {
                equals_sign = &env_str[j];
                break;
            }
        if (!equals_sign)
            continue;
        size_t name_len = equals_sign - env_str;
        /* Compare names correctly: strncmp == 0 when equal */
        if (strlen(var_name) == name_len && strncmp(env_str, var_name, name_len) == 0) {
            const char* env_value = equals_sign + 1;
            size_t value_len = strlen(env_value);
            char *value = (char*)malloc(value_len + 1);
            if (!value)
                return NULL;
            for (size_t k = 0; k <= value_len; k++)
                value[k] = env_value[k];
            return value;
        }
    }
#endif
    return NULL;
}

typedef enum shell_token_type {
    SHELL_TOKEN_ERROR,
    SHELL_TOKEN_EOL,
    SHELL_TOKEN_ATOM,
    SHELL_TOKEN_PIPE = '|',
    SHELL_TOKEN_AMPERSAND = '&',
    SHELL_TOKEN_GREATER = '>',
    SHELL_TOKEN_LESSER = '<',
    SHELL_TOKEN_SEMICOLON = ';'
} shell_token_type;

typedef struct shell_token {
    shell_token_type type;
    unsigned char *begin;
    int length;
} shell_token_t;

typedef struct shell_lexer {
    unsigned char *begin;
    struct {
        unsigned char *ptr;
        wchar_t ch;
        int ch_length;
    } cursor;
    char *error;
    unsigned char *input_begin; /* original input start for position reporting */
    size_t error_pos; /* byte offset into input where error occurred */
} shell_lexer_t;

typedef enum shell_ast_type {
    SHELL_AST_CMD,
    SHELL_AST_BACKGROUND,
    SHELL_AST_SEQ,
    SHELL_AST_REDIR_IN,
    SHELL_AST_REDIR_OUT,
    SHELL_AST_PIPE
} shell_ast_type_t;

typedef struct shell_ast {
    shell_ast_type_t type;
    shell_token_t *token;
    struct shell_ast *left, *right;
} shell_ast_t;

typedef struct shell_token_array {
    shell_token_t *data;
    size_t count;
    size_t capacity;
} shell_token_array_t;

typedef struct shell_parser {
    shell_token_array_t tokens;
    shell_token_t *current;
    size_t cursor;
} shell_parser;

static void eprintf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

static void _perror(const char *msg) {
    eprintf("esh: %s: %s\n", msg, strerror(errno));
}

static void die(const char *msg) {
    if (errno)
        _perror(msg);
    exit(EXIT_FAILURE);
}

static void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (!p)
        die("malloc");
    return p;
}

static void *xrealloc(void *ptr, size_t size) {
    void *p = realloc(ptr, size);
    if (!p)
        die("realloc");
    return p;
}

static int xopen(const char *path, int flags, mode_t mode) {
    int fd = open(path, flags, mode);
    if (fd == -1)
        die("open");
    return fd;
}

static int utf8read(const unsigned char* c, wchar_t* out) {
    wchar_t u = *c, l = 1;
    if ((u & 0xC0) == 0xC0) {
        int a = (u & 0x20) ? ((u & 0x10) ? ((u & 0x08) ? ((u & 0x04) ? 6 : 5) : 4) : 3) : 2;
        if (a < 6 || !(u & 0x02)) {
            u = ((u << (a + 1)) & 0xFF) >> (a + 1);
            for (int b = 1; b < a; ++b)
                u = (u << 6) | (c[l++] & 0x3F);
        }
    }
    if (out)
        *out = u;
    return l;
}

static void shell_lexer(shell_lexer_t *l, unsigned char* line) {
    l->begin = line;
    l->cursor.ptr = line;
    l->cursor.ch_length = utf8read(line, &l->cursor.ch);
    l->error = NULL;
    l->input_begin = line;
    l->error_pos = (size_t)-1;
}

static inline wchar_t peek(shell_lexer_t *l) {
    return l->cursor.ch;
}

static inline bool is_eof(shell_lexer_t *l) {
    return peek(l) == '\0';
}

static inline void update(shell_lexer_t *l) {
    l->begin = l->cursor.ptr;
    l->cursor.ch_length = utf8read(l->cursor.ptr, &l->cursor.ch);
    l->error = NULL;
}

static inline wchar_t advance(shell_lexer_t *l) {
    l->cursor.ptr += utf8read(l->cursor.ptr, NULL);
    l->cursor.ch_length = utf8read(l->cursor.ptr, &l->cursor.ch);
    return l->cursor.ch;
}

#define ADVANCE(L, N) \
    do { \
        int n = (N); \
        while (!is_eof((L)) && n-- > 0) \
            advance((L)); \
    } while(0)

static inline wchar_t next(shell_lexer_t *l) {
    if (is_eof(l))
        return '\0';
    wchar_t next;
    utf8read(l->cursor.ptr + l->cursor.ch_length, &next);
    return next;
}

static void skip_whitespace(shell_lexer_t *l) {
    for (;;) {
        if (is_eof(l))
            return;
        switch (peek(l)) {
            case ' ':
            case '\t':
            case '\v':
            case '\r':
            case '\n':
            case '\f':
                advance(l);
                break;
            default:
                return;
        }
    }
}

static shell_token_t new_token(shell_lexer_t *l, shell_token_type type) {
    return (shell_token_t) {
        .type = type,
        .begin = l->begin,
        .length = (int)(l->cursor.ptr - l->begin)
    };
}

static shell_token_t read_atom(shell_lexer_t *l) {
    for (;;) {
        if (is_eof(l))
            goto BAIL;
        switch (peek(l)) {
            case ' ':
            case '\t':
            case '\v':
            case '\r':
            case '\n':
            case '\f':
            case '|':
            case '&':
            case '<':
            case '>':
            case ';':
                goto BAIL;
            default:
                advance(l);
                break;
        }
    }
BAIL:
    return new_token(l, SHELL_TOKEN_ATOM);
}

static shell_token_t read_token(shell_lexer_t *l) {
    if (is_eof(l))
        return new_token(l, SHELL_TOKEN_EOL);
    update(l);
    wchar_t wc = peek(l);
    switch (wc) {
        case ' ':
        case '\t':
        case '\v':
        case '\r':
        case '\n':
        case '\f':
            skip_whitespace(l);
            update(l);
            return read_token(l);
        case '"':
        case '\'': {
            wchar_t quote = wc;
            /* start after opening quote */
            unsigned char *start = l->cursor.ptr + l->cursor.ch_length;
            unsigned char *p = start;
            for (;;) {
                wchar_t ch;
                int len = utf8read(p, &ch);
                if (ch == '\0') {
                    /* unterminated quote -> error token */
                    l->error = "unterminated quote";
                    l->begin = start;
                    l->cursor.ptr = p;
                    /* report error position as byte offset from input_begin */
                    if (l->input_begin)
                        l->error_pos = (size_t)(p - l->input_begin);
                    return new_token(l, SHELL_TOKEN_ERROR);
                }
                if (ch == quote) {
                    /* set token begin/ptr to produce length without quotes */
                    l->begin = start;
                    l->cursor.ptr = p; /* points at closing quote */
                    shell_token_t tok = new_token(l, SHELL_TOKEN_ATOM);
                    /* consume closing quote */
                    advance(l);
                    return tok;
                }
                p += len;
            }
        }
        case '|':
        case '&':
        case '<':
        case '>':
        case ';':
            advance(l);
            return new_token(l, (shell_token_type)wc);
        default:
            return read_atom(l);
    }
    return new_token(l, SHELL_TOKEN_ERROR);
}

static inline const char* token_string(shell_token_t *t) {
    switch (t->type) {
        case SHELL_TOKEN_ERROR:
            return "ERROR";
        case SHELL_TOKEN_EOL:
            return "END";
        case SHELL_TOKEN_ATOM:
            return "ATOM";
        case SHELL_TOKEN_PIPE:
            return "PIPE";
        case SHELL_TOKEN_AMPERSAND:
            return "AMPERSAND";
        case SHELL_TOKEN_GREATER:
            return "GREATER";
        case SHELL_TOKEN_LESSER:
            return "LESSER";
        case SHELL_TOKEN_SEMICOLON:
            return "SEMICOLON";
    }
}

static void shell_token_array_init(shell_token_array_t *arr) {
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

static bool shell_token_array_append(shell_token_array_t *arr, shell_token_t token) {
    if (arr->count + 1 > arr->capacity) {
        size_t new_capacity = arr->capacity == 0 ? 8 : arr->capacity * 2;
        shell_token_t *new_data = (shell_token_t*)xrealloc(arr->data, sizeof(shell_token_t) * new_capacity);
        if (!new_data)
            return false;
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->count++] = token;
    return true;
}

static shell_token_array_t shell_parse(shell_lexer_t *l) {
    shell_token_array_t tokens;
    shell_token_array_init(&tokens);
    for (;;) {
        shell_token_t token = read_token(l);
        switch (token.type) {
            default:
                l->error = "unknown token";
            case SHELL_TOKEN_ERROR:
            case SHELL_TOKEN_EOL:
                goto BAIL;
            case SHELL_TOKEN_ATOM:
            case SHELL_TOKEN_PIPE:
            case SHELL_TOKEN_AMPERSAND:
            case SHELL_TOKEN_GREATER:
            case SHELL_TOKEN_LESSER:
            case SHELL_TOKEN_SEMICOLON:
                if (!shell_token_array_append(&tokens, token))
                    l->error = "out of memory";
                break;
        }
    }
BAIL:
    return tokens;
}

static inline shell_ast_t* new_ast(void) {
    shell_ast_t *result = (shell_ast_t*)malloc(sizeof(shell_ast_t));
    memset(result, 0, sizeof(shell_ast_t));
    return result;
}

static void free_ast(shell_ast_t *node) {
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

static inline const char* ast_string(shell_ast_type_t t) {
    switch (t) {
        case SHELL_AST_CMD:
            return "COMMAND";
        case SHELL_AST_BACKGROUND:
            return "BACKGROUND";
        case SHELL_AST_SEQ:
            return "SEQUENCE";
        case SHELL_AST_REDIR_IN:
            return "REDIRECT_IN";
        case SHELL_AST_REDIR_OUT:
            return "REDIRECT_OUT";
        case SHELL_AST_PIPE:
            return "PIPE";
    }
}

static inline void shell_dump(shell_ast_t *node, int level) {
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    if (!node->token)
        printf("[%s]\n", ast_string(node->type));
    else
        printf("[%s(%s)]\n", token_string(node->token), ast_string(node->type));

    shell_dump(node->right, level + 1);
    shell_dump(node->left, level + 1);
}

static shell_token_t* parser_peek(shell_parser *p) {
    return p->cursor < p->tokens.count ? &p->tokens.data[p->cursor] : NULL;
}

static shell_token_t* parser_next(shell_parser *p) {
    if (p->cursor + 1 >= p->tokens.count)
        return NULL;
    ++p->cursor;
    return &p->tokens.data[p->cursor];
}

static int match_token(shell_parser *p, shell_token_type type) {
        shell_token_t *t = parser_peek(p);
        return t != NULL && t->type == type;
}

static int expect_token(shell_parser *p, shell_token_type type) {
    shell_token_t *t = parser_peek(p);
    return t != NULL && t->type == type;
}

static shell_ast_t *simple_command(shell_parser *p) {
    shell_token_t *t = parser_peek(p);
    if (t->type != SHELL_TOKEN_ATOM)
        return NULL;
    shell_ast_t *ast = new_ast();
    ast->type = SHELL_AST_CMD;
    ast->token = t;
    if (parser_next(p) != NULL)
        ast->right = simple_command(p);
    return ast;
}

static inline shell_ast_t *handle_redirection(shell_parser *p, shell_ast_type_t type, shell_ast_t *simple) {
    if (!expect_token(p, SHELL_TOKEN_ATOM))
        return NULL;
    shell_ast_t *ast = new_ast();
    ast->type = type;
    ast->right = simple;
    ast->token = parser_next(p);
    parser_next(p);
    return ast;
}

static shell_ast_t *command(shell_parser *p) {
    shell_ast_t *simple = simple_command(p);
    if (!simple)
        return NULL;
    if (match_token(p, SHELL_TOKEN_GREATER)) {
        // <simple command> '>' <filename>
        shell_ast_t *ast = handle_redirection(p, SHELL_AST_REDIR_OUT, simple);
        if (ast == NULL)
            free_ast(simple);
        return ast;
    }
    if (match_token(p, SHELL_TOKEN_LESSER)) {
        // <simple command> '<' <filename>
        shell_ast_t *ast = handle_redirection(p, SHELL_AST_REDIR_IN, simple);
        if (!ast)
            free_ast(simple);
        return ast;
    }
    // <simple command>
    return simple;
}

static shell_ast_t *_pipe(shell_parser *p) {
    shell_ast_t *left = command(p);
    if (left == NULL)
        return NULL;
    // <command> '|' <pipe>
    if (match_token(p, SHELL_TOKEN_PIPE)) {
        if (!expect_token(p, SHELL_TOKEN_ATOM)) {
            free_ast(left);
            return NULL;
        }
        shell_ast_t *ast = new_ast();
        ast->type = SHELL_AST_PIPE;
        ast->left = left;
        parser_next(p);
        ast->right = _pipe(p);
        return ast;
    }
    // <command>
    return left;
}

static shell_ast_t *full_command(shell_parser *p) {
    shell_ast_t *left = _pipe(p);
    if (left == NULL)
        return NULL;
    // <pipe> '&' <full command> | <pipe> '&'
    if (match_token(p, SHELL_TOKEN_AMPERSAND)) {
        if (!expect_token(p, SHELL_TOKEN_ATOM) && parser_peek(p) != NULL) {
            free_ast(left);
            return NULL;
        }
        shell_ast_t *ast = new_ast();
        ast->type = SHELL_AST_BACKGROUND;
        ast->left = left;
        parser_next(p);
        ast->right = full_command(p);
        return ast;
    }
    // <pipe> ';' <full command> | <pipe> ';'
    if (match_token(p, SHELL_TOKEN_SEMICOLON)) {
        if (!expect_token(p, SHELL_TOKEN_ATOM) && parser_peek(p) != NULL) {
            free_ast(left);
            return NULL;
        }
        shell_ast_t *ast = new_ast();
        ast->type = SHELL_AST_SEQ;
        ast->left = left;
        parser_next(p);
        ast->right = full_command(p);
        return ast;
    }
    return left;
}

static shell_ast_t* shell_eval(shell_token_array_t tokens) {
    shell_parser parser = {
        .tokens = tokens,
        .cursor = 0
    };
    shell_ast_t *result = full_command(&parser);
    return tokens.count == 0 ? NULL : parser.cursor == tokens.count - 1 ? result : NULL;
}

typedef struct shell_command {
    int argc;
    char **argv;
    int input_fd;
    int output_fd;
    int bg;
} shell_command_t;

static int input_fd = -1;
static int output_fd = -1;
static int bg = 0;

static void command_argv_from_ast(shell_command_t *cmd, shell_ast_t *ast) {
    // Initialize command fields
    cmd->argc = 0;
    cmd->argv = NULL;

    // Count arguments safely
    for (shell_ast_t *n = ast; n != NULL; n = n->right)
        cmd->argc++;

    if (cmd->argc == 0) {
        cmd->argv = (char **)xmalloc(sizeof(char *));
        cmd->argv[0] = NULL;
        return;
    }

    cmd->argv = (char **)xmalloc(sizeof(char *) * (cmd->argc + 1));

    // Copy each token into a NUL-terminated C string
    for (int i = 0; i < cmd->argc; i++) {
        if (ast == NULL || ast->token == NULL) {
            // Defensive: ensure we don't dereference a NULL ast/token
            cmd->argv[i] = (char *)xmalloc(1);
            cmd->argv[i][0] = '\0';
        } else {
            size_t len = (size_t)ast->token->length;
            size_t size = len + 1; // room for terminating NUL
            cmd->argv[i] = (char *)xmalloc(size);
            memcpy(cmd->argv[i], ast->token->begin, len);
            cmd->argv[i][len] = '\0';
        }
        ast = ast ? ast->right : NULL;
    }
    cmd->argv[cmd->argc] = NULL;
}

typedef struct shell_builtin {
  char *name;
  void (*func)(int argc, char **argv);
} shell_builtin_t;

static void builtin_exit(int argc, char **argv) {
    (void)argc;
    (void)argv;
    exit(0);
}

static void builtin_cd(int argc, char **argv) {
    if (argc == 1) {
        if (chdir(getenv("HOME")) == -1)
            perror("cd");
    } else if (argc == 2) {
        if (chdir(argv[1]) == -1)
            perror("cd");
    } else
        eprintf("cd: too many arguments\n");
}

static void builtin_pwd(int argc, char **argv) {
    (void)argv;
    if (argc > 1) {
        eprintf("pwd: too many arguments\n");
        return;
    }
    char *cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    free(cwd);
}

static shell_builtin_t builtins[] = {
    {"exit", &builtin_exit},
    {"cd", &builtin_cd},
    {"pwd", &builtin_pwd},
};

static shell_builtin_t *builtin_find_by_name(char *name) {
    for (size_t i = 0; i < sizeof(builtins) / sizeof(shell_builtin_t); i++)
        if (strcmp(builtins[i].name, name) == 0)
            return &builtins[i];
    return NULL;
}

static void builtin_execute(shell_builtin_t *builtin, int argc, char **argv) {
    if (builtin)
        builtin->func(argc, argv);
}

static void command_execute(shell_command_t *cmd) {
    if (cmd->argc == 0)
        return;

    // Builtins
    shell_builtin_t *builtin = builtin_find_by_name(cmd->argv[0]);
    if (builtin) {
        builtin_execute(builtin, cmd->argc, cmd->argv);
        return;
    }

    // Fork
    pid_t pid = fork();
    if (pid == -1) {
        _perror("fork");
        return;
    }

    // Child
    if (pid == 0) {
        if (cmd->bg) {
            printf("\n[BACKGROUND] started backgroundjob: %s\n", cmd->argv[0]);
            setpgid(0, 0);

            int fd = xopen("/dev/null", O_RDONLY, 0);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // Pipe
        if (cmd->input_fd != -1) {
            dup2(cmd->input_fd, STDIN_FILENO);
            close(cmd->input_fd);
        }
        if (cmd->output_fd != -1) {
            dup2(cmd->output_fd, STDOUT_FILENO);
            close(cmd->output_fd);
        }

        // Execute
        if (execvp(cmd->argv[0], cmd->argv) == -1) {
            die("execvp");
        }
    }
    // Wait for child
    if (!cmd->bg) {
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        return;
    }

    // Background process
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP; // Restart interrupted syscalls,
    // don't handle stopped children
    sigaction(SIGCHLD, &sa, NULL);
}

static void command_destroy(shell_command_t *cmd) {
    if (cmd->argv) {
        for (int i = 0; i < cmd->argc; i++)
            free(cmd->argv[i]);
        free(cmd->argv);
    }
}

static void eval_commandtail(shell_ast_t *ast) {
    shell_command_t cmd;
    command_argv_from_ast(&cmd, ast);
    cmd.input_fd = input_fd;
    cmd.output_fd = output_fd;
    cmd.bg = bg;
    command_execute(&cmd);
    command_destroy(&cmd);
}

static int shell_exec(shell_ast_t *ast);

static void eval_sequence(shell_ast_t *ast) {
    if (ast->type == SHELL_AST_BACKGROUND)
        bg = 1;
    shell_exec(ast->left);
    shell_exec(ast->right);
    if (ast->type == SHELL_AST_BACKGROUND)
        bg = 0;
}

static void eval_redirection(shell_ast_t *ast) {
    int fd;
    unsigned char c = ast->token->begin[ast->token->length];
    ast->token->begin[ast->token->length] = '\0';
    if (ast->type == SHELL_AST_REDIR_IN) {
        fd = open((const char*)ast->token->begin, O_RDONLY);
        if (fd == -1) {
            _perror("open");
            return;
        }
        input_fd = fd;
    } else {
        fd = open((const char*)ast->token->begin,
                  O_WRONLY | O_CREAT | O_TRUNC,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            _perror("open");
            return;
        }
        output_fd = fd;
    }
    ast->token->begin[ast->token->length] = c;

    shell_exec(ast->right);
    close(fd);
    input_fd = -1;
    output_fd = -1;
}

static void eval_pipeline(shell_ast_t *ast) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        _perror("pipe");
        return;
    }

    input_fd = -1;
    output_fd = pipefd[1];
    shell_exec(ast->left);
    close(pipefd[1]);

    ast = ast->right;

    input_fd = pipefd[0];

    while (ast->type == SHELL_AST_PIPE) {
        if (pipe(pipefd) == -1) {
            _perror("pipe");
            return;
        }
        output_fd = pipefd[1];
        shell_exec(ast->left);
        close(pipefd[1]);
        close(input_fd);
        input_fd = pipefd[0];
        ast = ast->right;
    }
    output_fd = -1;
    input_fd = pipefd[0];
    shell_exec(ast);
    close(pipefd[0]);
}

static int shell_exec(shell_ast_t *ast) {
    if (!ast)
        goto BAIL;
    switch (ast->type) {
        case SHELL_AST_PIPE:
            eval_pipeline(ast);
            break;
        case SHELL_AST_REDIR_IN:
        case SHELL_AST_REDIR_OUT:
            eval_redirection(ast);
            break;
        case SHELL_AST_SEQ:
        case SHELL_AST_BACKGROUND:
            eval_sequence(ast);
            break;
        case SHELL_AST_CMD:
            eval_commandtail(ast);
            break;
        default:
            break;
    }
BAIL:
    return EXIT_SUCCESS;
}

#if defined(_WIN32) || defined(_WIN64)
/* Windows-specific implementation */

typedef struct {
    HANDLE handle;
    shell_stream_cb_t callback;
    void *userdata;
    char **buffer;
    size_t *length;
    size_t *capacity;
    int use_callback;
} win_reader_args_t;

static DWORD WINAPI win_reader_thread(LPVOID arg) {
    win_reader_args_t *args = (win_reader_args_t*)arg;
    char buffer[4096];
    DWORD bytes_read = 0;
    
    while (ReadFile(args->handle, buffer, sizeof(buffer), &bytes_read, NULL) && bytes_read > 0)
        if (args->use_callback) {
            args->callback(buffer, bytes_read, args->userdata);
        } else {
            // Ensure buffer has enough capacity
            if (*args->capacity - *args->length < bytes_read) {
                size_t new_capacity = (*args->capacity == 0) ? 4096 : *args->capacity * 2;
                while (new_capacity - *args->length < bytes_read) {
                    new_capacity *= 2;
                }
                *args->buffer = xrealloc(*args->buffer, new_capacity + 1);
                *args->capacity = new_capacity;
            }
            memcpy(*args->buffer + *args->length, buffer, bytes_read);
            *args->length += bytes_read;
        }
    return 0;
}

static int create_pipe_pair(HANDLE *read_handle, HANDLE *write_handle, int inherit_read) {
    SECURITY_ATTRIBUTES sa = {
        .nLength = sizeof(SECURITY_ATTRIBUTES),
        .bInheritHandle = TRUE,
        .lpSecurityDescriptor = NULL
    };
    
    if (!CreatePipe(read_handle, write_handle, &sa, 0))
        return SHELL_ERR_PIPE;
    
    // Set inheritance based on parameter
    HANDLE non_inherit = inherit_read ? *write_handle : *read_handle;
    SetHandleInformation(non_inherit, HANDLE_FLAG_INHERIT, 0);
    
    return SHELL_OK;
}

static void cleanup_handles(HANDLE *handles, size_t count) {
    for (size_t i = 0; i < count; i++)
        if (handles[i] != NULL && handles[i] != INVALID_HANDLE_VALUE) {
            CloseHandle(handles[i]);
            handles[i] = NULL;
        }
}

static int win_shell_implementation(const char *cmd, shell_io *io) {
    if (!cmd)
        return SHELL_ERR_GENERIC;

    HANDLE pipes[6] = {0}; // stdin_r, stdin_w, stdout_r, stdout_w, stderr_r, stderr_w
    HANDLE *stdin_r = &pipes[0], *stdin_w = &pipes[1];
    HANDLE *stdout_r = &pipes[2], *stdout_w = &pipes[3]; 
    HANDLE *stderr_r = &pipes[4], *stderr_w = &pipes[5];
    
    // Create pipes
    int result;
    if ((result = create_pipe_pair(stdout_r, stdout_w, 0)) != SHELL_OK ||
        (result = create_pipe_pair(stderr_r, stderr_w, 0)) != SHELL_OK ||
        (result = create_pipe_pair(stdin_r, stdin_w, 0)) != SHELL_OK) {
        cleanup_handles(pipes, 6);
        return result;
    }
    
    // Prepare command line
    size_t cmd_len = strlen(cmd);
    char *cmdline = xmalloc(cmd_len + 1);
    strcpy(cmdline, cmd);
    
    // Setup process creation structures
    STARTUPINFOA si = {
        .cb = sizeof(STARTUPINFOA),
        .dwFlags = STARTF_USESTDHANDLES,
        .hStdInput = *stdin_r,
        .hStdOutput = *stdout_w,
        .hStdError = *stderr_w
    };
    
    PROCESS_INFORMATION pi = {0};
    
    // Create process
    BOOL success = CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    free(cmdline);
    
    if (!success) {
        cleanup_handles(pipes, 6);
        return SHELL_ERR_FORK;
    }
    
    // Close child's handles in parent
    CloseHandle(*stdout_w); *stdout_w = NULL;
    CloseHandle(*stderr_w); *stderr_w = NULL;
    CloseHandle(*stdin_r); *stdin_r = NULL;
    
    // Setup reader threads
    char *outbuf = NULL, *errbuf = NULL;
    size_t out_len = 0, out_cap = 0, err_len = 0, err_cap = 0;
    int use_out_cb = io && io->out_cb != NULL;
    int use_err_cb = io && io->err_cb != NULL;
    
    win_reader_args_t out_args = {
        .handle = *stdout_r,
        .callback = io ? io->out_cb : NULL,
        .userdata = io ? io->userdata : NULL,
        .buffer = &outbuf,
        .length = &out_len,
        .capacity = &out_cap,
        .use_callback = use_out_cb
    };
    
    win_reader_args_t err_args = {
        .handle = *stderr_r,
        .callback = io ? io->err_cb : NULL,
        .userdata = io ? io->userdata : NULL,
        .buffer = &errbuf,
        .length = &err_len,
        .capacity = &err_cap,
        .use_callback = use_err_cb
    };
    
    HANDLE threads[2];
    threads[0] = CreateThread(NULL, 0, win_reader_thread, &out_args, 0, NULL);
    threads[1] = CreateThread(NULL, 0, win_reader_thread, &err_args, 0, NULL);
    
    // Write input if provided
    if (io && io->in && io->in_len > 0) {
        DWORD written;
        WriteFile(*stdin_w, io->in, (DWORD)io->in_len, &written, NULL);
    }
    CloseHandle(*stdin_w); *stdin_w = NULL;
    
    // Wait for completion
    WaitForSingleObject(pi.hProcess, INFINITE);
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);
    
    // Get exit code
    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    
    // Populate io structure
    if (io) {
        if (!use_out_cb) {
            io->out = outbuf ? (outbuf[out_len] = '\0', outbuf) : (outbuf = xmalloc(1), outbuf[0] = '\0', outbuf);
            io->out_len = out_len;
        } else {
            io->out = NULL;
            io->out_len = 0;
        }
        
        if (!use_err_cb) {
            io->err = errbuf ? (errbuf[err_len] = '\0', errbuf) : (errbuf = xmalloc(1), errbuf[0] = '\0', errbuf);
            io->err_len = err_len;
        } else {
            io->err = NULL;
            io->err_len = 0;
        }
    }
    
    // Cleanup
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    cleanup_handles(pipes, 6);
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
    
    return (int)exit_code;
}

#else
/* POSIX implementation */

static int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    return flags == -1 ? -1 : fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static void close_pipe_pair(int pipe_fds[2]) {
    if (pipe_fds[0] != -1) {
        close(pipe_fds[0]);
        pipe_fds[0] = -1;
    }
    if (pipe_fds[1] != -1) {
        close(pipe_fds[1]);
        pipe_fds[1] = -1;
    }
}

static int write_input_to_child(int write_fd, const char *input, size_t input_len) {
    size_t written = 0;
    while (written < input_len) {
        ssize_t result = write(write_fd, input + written, input_len - written);
        if (result == -1) {
            if (errno == EAGAIN || errno == EINTR)
                continue;
            return -1;
        }
        written += result;
    }
    return 0;
}

static int ensure_buffer_capacity(char **buffer, size_t *capacity, size_t current_len, size_t needed) {
    if (*capacity - current_len >= needed)
        return 0;

    size_t new_capacity = (*capacity == 0) ? 4096 : *capacity * 2;
    while (new_capacity - current_len < needed)
        new_capacity *= 2;
    
    *buffer = (char*)xrealloc(*buffer, new_capacity + 1);
    *capacity = new_capacity;
    return 0;
}

static int posix_shell_with_io(const char *cmd, shell_io *io) {
    int pipes[6] = {-1, -1, -1, -1, -1, -1}; // in[2], out[2], err[2]
    int *inpipe = &pipes[0], *outpipe = &pipes[2], *errpipe = &pipes[4];
    
    // Create pipes
    if (pipe(inpipe) == -1 || pipe(outpipe) == -1 || pipe(errpipe) == -1) {
        for (int i = 0; i < 6; i += 2)
            close_pipe_pair(&pipes[i]);
        return SHELL_ERR_PIPE;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        for (int i = 0; i < 6; i += 2)
            close_pipe_pair(&pipes[i]);
        return SHELL_ERR_FORK;
    }
    
    if (pid == 0) {
        // Child process
        close(inpipe[1]);   // Close write end of input
        close(outpipe[0]);  // Close read end of output
        close(errpipe[0]);  // Close read end of error
        
        // Redirect standard file descriptors
        if (dup2(inpipe[0], STDIN_FILENO) == -1 ||
            dup2(outpipe[1], STDOUT_FILENO) == -1 ||
            dup2(errpipe[1], STDERR_FILENO) == -1) {
            die("dup2");
        }
        
        close(inpipe[0]);
        close(outpipe[1]);
        close(errpipe[1]);
        
        // Parse and execute command
        shell_lexer_t lexer;
        shell_lexer(&lexer, (unsigned char*)cmd);
        shell_token_array_t tokens = shell_parse(&lexer);
        
        if (!tokens.data || lexer.error) {
            if (tokens.data)
                free(tokens.data);
            _exit(SHELL_ERR_TOKENIZE);
        }
        
        shell_ast_t *ast = shell_eval(tokens);
        if (!ast) {
            free(tokens.data);
            _exit(SHELL_ERR_EVAL);
        }
        
        int result = shell_exec(ast);
        free(tokens.data);
        free_ast(ast);
        _exit(result == 0 ? SHELL_OK : result);
    }
    
    // Parent process
    close(inpipe[0]);   // Close read end of input
    close(outpipe[1]);  // Close write end of output  
    close(errpipe[1]);  // Close write end of error
    
    // Set pipes to non-blocking
    set_nonblocking(inpipe[1]);
    set_nonblocking(outpipe[0]);
    set_nonblocking(errpipe[0]);
    
    // Write input if provided
    if (io->in && io->in_len > 0)
        write_input_to_child(inpipe[1], io->in, io->in_len);
    close(inpipe[1]);
    
    // Setup buffers and callbacks
    char *outbuf = NULL, *errbuf = NULL;
    size_t out_len = 0, out_cap = 0, err_len = 0, err_cap = 0;
    int use_out_cb = io->out_cb != NULL;
    int use_err_cb = io->err_cb != NULL;
    
    // Poll for output
    struct pollfd fds[2] = {
        {.fd = outpipe[0], .events = POLLIN | POLLHUP},
        {.fd = errpipe[0], .events = POLLIN | POLLHUP}
    };
    
    int active_fds = 2;
    while (active_fds > 0) {
        int poll_result = poll(fds, 2, -1);
        if (poll_result == -1) {
            if (errno == EINTR)
                continue;
            break; // Fatal error
        }
        
        for (int i = 0; i < 2; i++) {
            if (!(fds[i].revents & (POLLIN | POLLHUP)) || fds[i].fd == -1)
                continue;

            char buffer[4096];
            ssize_t bytes_read;
            
            while ((bytes_read = read(fds[i].fd, buffer, sizeof(buffer))) > 0) {
                if (i == 0) { // stdout
                    if (use_out_cb)
                        io->out_cb(buffer, bytes_read, io->userdata);
                    else {
                        ensure_buffer_capacity(&outbuf, &out_cap, out_len, bytes_read);
                        memcpy(outbuf + out_len, buffer, bytes_read);
                        out_len += bytes_read;
                    }
                } else { // stderr
                    if (use_err_cb)
                        io->err_cb(buffer, bytes_read, io->userdata);
                    else {
                        ensure_buffer_capacity(&errbuf, &err_cap, err_len, bytes_read);
                        memcpy(errbuf + err_len, buffer, bytes_read);
                        err_len += bytes_read;
                    }
                }
            }
            
            if (bytes_read == 0 || (bytes_read == -1 && errno != EAGAIN && errno != EINTR)) {
                fds[i].fd = -1;
                active_fds--;
            }
        }
    }
    
    // Finalize buffers
    if (!use_out_cb) {
        io->out = outbuf ? (outbuf[out_len] = '\0', outbuf) : (outbuf = (char *)xmalloc(1), outbuf[0] = '\0', outbuf);
        io->out_len = out_len;
    } else {
        io->out = NULL;
        io->out_len = 0;
    }
    
    if (!use_err_cb) {
        io->err = errbuf ? (errbuf[err_len] = '\0', errbuf) : (errbuf = (char *)xmalloc(1), errbuf[0] = '\0', errbuf);
        io->err_len = err_len;
    } else {
        io->err = NULL;
        io->err_len = 0;
    }
    
    close(outpipe[0]);
    close(errpipe[0]);
    
    // Wait for child and get exit status
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

static int posix_shell_inline(const char *cmd) {
    shell_lexer_t lexer;
    shell_lexer(&lexer, (unsigned char*)cmd);
    
    shell_token_array_t tokens = shell_parse(&lexer);
    if (!tokens.data || lexer.error) {
        if (lexer.error) {
            const char *error_fmt = (lexer.error_pos != (size_t)-1) 
                ? "error: '%s' at byte %zu\n" 
                : "error: '%s'\n";
            printf(error_fmt, lexer.error, lexer.error_pos);
        } else
            printf("error: failed to tokenize\n");
        if (tokens.data)
            free(tokens.data);
        return -1;
    }
    
    shell_ast_t *ast = shell_eval(tokens);
    if (!ast) {
        printf("error: failed to evaluate\n");
        free(tokens.data);
        return -1;
    }
    
    int result = shell_exec(ast);
    free(tokens.data);
    free_ast(ast);
    return result;
}

#endif /* _WIN32 */

int shell(const char *cmd, shell_io *io) {
    if (!cmd)
        return SHELL_ERR_GENERIC;

#if defined(_WIN32) || defined(_WIN64)
    return win_shell_implementation(cmd, io);
#else
    return io ? posix_shell_with_io(cmd, io) : posix_shell_inline(cmd);
#endif
}

int shell_fmt(shell_io *io, const char *fmt, ...) {
    if (!fmt)
        return SHELL_ERR_GENERIC;

    va_list args;
    va_start(args, fmt);
    char *cmd = NULL;
    if (vasprintf(&cmd, fmt, args) == -1) {
        va_end(args);
        return SHELL_ERR_GENERIC;
    }
    va_end(args);

    int result = shell(cmd, io);
    free(cmd);
    return result;
}

bool file_exists(const char *path) {
    if (!path)
        return false;
#ifdef PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return attrs != INVALID_FILE_ATTRIBUTES && !attrs & FILE_ATTRIBUTE_DIRECTORY;
#elif defined(PLATFORM_POSIX)
    struct stat st;
    if (stat(path, &st) == -1)
        return false;
    return S_ISREG(st.st_mode);
#else
    return false;
#endif
}

bool file_delete(const char *path) {
    if (!path || !file_exists(path))
        return false;
#ifdef PLATFORM_WINDOWS
    return DeleteFileA(path) != 0;
#elif defined(PLATFORM_POSIX)
    return unlink(path) == 0;
#else
    return false;
#endif
}

bool file_rename(const char *old_path, const char *new_path, bool write_over) {
    if (!old_path || !file_exists(old_path) || !new_path || (!write_over && file_exists(new_path)))
        return false;
#ifdef PLATFORM_WINDOWS
    return MoveFileA(old_path, new_path) != 0;
#elif defined(PLATFORM_POSIX)
    if (link(old_path, new_path) == 0)
        return unlink(old_path) == 0;
#endif
    return false;
}

int file_size(const char *path) {
    if (!path)
        return -1;
#ifdef PLATFORM_WINDOWS
    WIN32_FILE_ATTRIBUTE_DATA file_data;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &file_data))
        return -1;
    return ((long long)file_data.nFileSizeHigh << 32) | file_data.nFileSizeLow;
#elif defined(PLATFORM_POSIX)
    struct stat st;
    if (stat(path, &st) == -1)
        return -1;
    return (int)st.st_size;
#else
    return -1;
#endif
}

bool file_copy(const char *src_path, const char *dst_path, bool write_over) {
    if (!src_path || !dst_path || !file_exists(src_path) || (path_exists(dst_path) && !write_over))
        return false;

    static const size_t buffer_size = 4096;
    file_t src_fd = {-1}, dst_fd = {-1};
    ssize_t bytes_read, bytes_written;
    char buffer[buffer_size];
    bool result = false;

    if (!io_open(&src_fd, src_path, FILE_READ))
        goto BAIL;
    if (!io_open(&dst_fd, dst_path, FILE_WRITE))
        goto BAIL;

    while ((bytes_read = io_read(src_fd, buffer, buffer_size)) > 0)
        if ((bytes_written = io_write(dst_fd, buffer, bytes_read)) != bytes_read)
            goto BAIL;
    if (bytes_read == -1)
        goto BAIL;
    result = true;

BAIL:
    if (io_valid(src_fd))
        io_close(&src_fd);
    if (io_valid(dst_fd))
        io_close(&dst_fd);
    return result;
}

const char* file_read(const char *path, size_t *size) {
    char *result = NULL;
    long _size = -1;
    file_t file = io_invalid;
    if (!path || !file_exists(path) || !io_open(&file, path, FILE_READ))
        goto BAIL;
    io_seek(file, 0, FILE_START);
    io_seek(file, 0, FILE_FINISH);
    if ((_size = io_tell(file)) == -1)
        goto BAIL;
    io_seek(file, 0, FILE_START);
    if (!(result = (char*)malloc(_size * sizeof(char))))
        goto BAIL;
    if (!io_read(file, result, _size)) {
        free(result);
        goto BAIL;
    }
BAIL:
    if (io_valid(file))
        io_close(&file);
    if (size)
        *size = _size;
    return result;
}

bool directory_exists(const char *path) {
    if (!path)
        return false;
#ifdef PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return attrs != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_DIRECTORY;
#elif defined(PLATFORM_POSIX)
    struct stat st;
    if (stat(path, &st) == -1)
        return false;
    return S_ISDIR(st.st_mode);
#else
    return false;
#endif
}

bool directory_create(const char *path, bool recursive) {
    if (!path)
        return false;
    if (directory_exists(path))
        return true;
#ifdef PLATFORM_WINDOWS
    return CreateDirectoryA(path, NULL) != 0;
#elif defined(PLATFORM_POSIX)
    if (recursive) {
        const char *resolved = path_resolve(path);
        if (!resolved)
            return false;
        while (true) {
            const char *parent = path_get_parent_directory(resolved);
            if (!parent) {
                free((void*)resolved);
                return false;
            }
            if (directory_exists(resolved)) {
                free((void*)resolved);
                free((void*)parent);
                return true;
            } else {
                if (mkdir(resolved, 0755) != 0) {
                    free((void*)resolved);
                    free((void*)parent);
                    return false;
                }
            }
            free((void*)resolved);
            resolved = parent;
        }
        free((void*)resolved);
        return true;
    } else
        return mkdir(path, 0755) == 0;
#else
    return false;
#endif
}

bool directory_delete(const char *path, bool recursive, bool and_files) {
    if (!path || !directory_exists(path))
        return false;

#ifndef PLATFORM_UNKNOWN
    if (recursive) {
        dir_t d = {.path=path};
        const char *name = NULL;
        bool is_dir = false;
        while ((name = directory_iter(&d, &is_dir)) != NULL) {
            const char *full_path = path_join(path, name);
            if (is_dir) {
                if (!directory_delete(full_path, true, and_files)) {
                    directory_iter_end(&d);
                    free((void*)full_path);
                    return false;
                }
            } else {
                if (!file_delete(full_path)) {
                    directory_iter_end(&d);
                    free((void*)full_path);
                    return false;
                }
            }
            free((void *)full_path);
        }
    } else {
        if (and_files) {
            dir_t d = {.path=path};
            const char *name = NULL;
            bool is_dir = false;
            const char **files = (const char**)malloc(0);
            size_t files_size = 0;
            if (!files)
                return false;
            while ((name = directory_iter(&d, &is_dir)) != NULL) {
                if (is_dir) {
                    for (int i = 0; i < (int)files_size; i++)
                        free((void *)files[i]);
                    free((void*)files);
                    directory_iter_end(&d);
                    return false;
                }
                const char *full_path = path_join(path, name);
                if (!full_path) {
                    directory_iter_end(&d);
                    return false;
                }
                if (!(files = (const char**)realloc(files, ++files_size * sizeof(char *)))) {
                    free((void *)full_path);
                    directory_iter_end(&d);
                    return false;
                }
                files[files_size - 1] = full_path;
            }
            bool success = true;
            if (files_size > 0) {
                for (size_t i = 0; i < files_size; i++) {
                    if (!file_delete(files[i])) {
                        success = false;
                        break;
                    }
                }
            }
            for (size_t i = 0; i < files_size; i++)
                free((void *)files[i]);
            free((void *)files);
            if (!success)
                return false;
        }
    }
#endif

#ifdef PLATFORM_WINDOWS
    return RemoveDirectoryA(path) != 0;
#elif defined(PLATFORM_POSIX)
    return rmdir(path) == 0;
#else
    return false;
#endif
}

bool directory_rename(const char *old_path, const char *new_path, bool write_over) {
    return directory_copy(old_path, new_path, write_over, true);
}

bool directory_copy(const char *src_path, const char *dst_path, bool write_over, bool delete_src) {
    if (!src_path || !directory_exists(src_path) || !dst_path)
        return false;

    bool result = false;
    const char *parent = path_get_parent_directory(dst_path);
    const char *dir_name = NULL, *dst = NULL;
    dir_t d = {.path=src_path};
    const char *name = NULL;
    bool is_dir = false;
    if (!parent || !directory_exists(parent))
        goto BAIL;
    if (!(dir_name = path_get_directory_name(src_path)))
        goto BAIL;
    if (!(dst = path_join(dst_path, dir_name)) || !directory_create(dst, false))
        goto BAIL;

    while ((name = directory_iter(&d, &is_dir)) != NULL) {
        const char *src_full = path_join(src_path, name);
        const char *dst_full = path_join(dst_path, name);
        bool die = false;
        if (is_dir)
            if (directory_create(dst_full, false)) {
                if (!directory_copy(src_full, dst_full, write_over, delete_src))
                    die = true;
            } else
                die = true;
        else
            if (file_copy(src_full, dst_full, write_over))
                if (delete_src)
                    file_delete(src_full);
        free((void *)src_full);
        free((void *)dst_full);
        if (die) {
            directory_iter_end(&d);
            goto BAIL;
        }
    }

    if (delete_src)
        directory_delete(src_path, true, true);
    result = true;
BAIL:
    if (parent)
        free((void*)parent);
    if (dir_name)
        free((void*)dir_name);
    if (dst)
        free((void*)dst);
    return result;
}

int directory_size(const char *path) {
    if (!path || !directory_exists(path))
        return -1;
    dir_t d = {.path=path};
    const char *name = NULL;
    bool is_dir = false;
    int total = 0;
    while ((name = directory_iter(&d, &is_dir)) != NULL) {
        const char *full_path = path_join(path, name);
        if (!full_path) {
            directory_iter_end(&d);
            return -1;
        }
        total += is_dir ? directory_size(full_path) : file_size(full_path);
        free((void *)full_path);
    }
    return total;
}

int directory_item_count(const char *path, bool recursive) {
    if (!path || !directory_exists(path))
        return -1;
    dir_t d = {.path=path};
    const char *name = NULL;
    bool is_dir = false;
    int total = 0;
    while ((name = directory_iter(&d, &is_dir)) != NULL) {
        total++;
        if (is_dir && recursive) {
            const char *full_path = path_join(path, name);
            if (!full_path) {
                directory_iter_end(&d);
                return -1;
            }
            total += directory_file_count(full_path, true);
            free((void *)full_path);
        }
    }
    return total;
}

int directory_file_count(const char *path, bool recursive) {
    if (!path || !directory_exists(path))
        return -1;
    dir_t d = {.path=path};
    const char *name = NULL;
    bool is_dir = false;
    int total = 0;
    while ((name = directory_iter(&d, &is_dir)) != NULL) {
        if (is_dir) {
            if (recursive) {
                const char *full_path = path_join(path, name);
                if (!full_path) {
                    directory_iter_end(&d);
                    return -1;
                }
                total += directory_file_count(full_path, true);
                free((void*)full_path);
            }
        } else
            total++;
    }
    return total;
}

/* simple glob matcher supporting '*' and '?' sufficient for tests */
static int simple_match(const char *pat, const char *s) {
    if (!pat)
        return s && *s == '\0';
    if (*pat == '\0')
        return *s == '\0';
    if (*pat == '*') {
        while (*(pat + 1) == '*')
            pat++;
        if (*(pat+1) == '\0') return 1;
        for (const char *p = s; *p; ++p)
            if (simple_match(pat + 1, p))
                return 1;
        return 0;
    } else if (*pat == '?') {
        return *s && simple_match(pat+1, s+1);
    } else {
        if (*pat == *s)
            return simple_match(pat + 1, s + 1);
        return 0;
    }
}

struct collect_ctx {
    char **out;
    int n;
    int cap;
};

static void collect_add(struct collect_ctx *c, const char *full) {
    if (c->n >= c->cap) {
        int newcap = c->cap == 0 ? 8 : c->cap * 2;
        char **tmp = (char **)realloc(c->out, newcap * sizeof(char*));
        if (!tmp)
            return;
        c->out = tmp;
        c->cap = newcap;
    }
    c->out[c->n++] = strdup(full);
}

static void walk_and_match(const char *base, const char *suffix_pat, struct collect_ctx *c) {
    DIR *d = opendir(base);
    if (!d)
        return;
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
        char full[4096];
        snprintf(full, sizeof(full), "%s/%s", base, ent->d_name);
        struct stat st;
        if (stat(full, &st) == -1)
            continue;
        if (S_ISDIR(st.st_mode))
            walk_and_match(full, suffix_pat, c);
        else if (S_ISREG(st.st_mode) && simple_match(suffix_pat, ent->d_name))
            collect_add(c, full);
    }
    closedir(d);
}

const char** directory_glob(const char *pattern, int *count) {
    if (!pattern) return NULL;
    struct collect_ctx c = {0};
    const char *ddstar = strstr(pattern, "**");
    if (ddstar) {
        const char *slash_before = ddstar;
        while (slash_before > pattern && *slash_before != '/')
            --slash_before;
        size_t base_len = 0;
        const char *suffix_pat = NULL;
        if (*slash_before == '/') {
            base_len = slash_before - pattern;
            suffix_pat = ddstar + 2;
            if (*suffix_pat == '/')
                suffix_pat++;
        } else {
            base_len = 0;
            suffix_pat = ddstar + 2;
            if (*suffix_pat == '/')
                suffix_pat++;
        }
        char base[4096];
        if (base_len == 0)
            strcpy(base, ".");
        else {
            strncpy(base, pattern, base_len);
            base[base_len] = '\0';
        }
        walk_and_match(base, suffix_pat, &c);
    } else {
        const char *last = strrchr(pattern, '/');
        char dir[4096];
        const char *filepat = NULL;
        if (last) {
            size_t dlen = last - pattern;
            if (dlen == 0)
                strcpy(dir, "/");
            else {
                strncpy(dir, pattern, dlen);
                dir[dlen] = '\0';
            }
            filepat = last + 1;
        } else { strcpy(dir, "."); filepat = pattern; }
        DIR *d = opendir(dir);
        if (d) {
            struct dirent *ent;
            while ((ent = readdir(d)) != NULL) {
                if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
                char full[4096];
                snprintf(full, sizeof(full), "%s/%s", dir, ent->d_name);
                struct stat st;
                if (stat(full, &st) == -1)
                    continue;
                if (S_ISREG(st.st_mode)) {
                    if (simple_match(filepat, ent->d_name))
                        collect_add(&c, full);
                } else if (S_ISDIR(st.st_mode))
                    walk_and_match(full, filepat, &c);
            }
            closedir(d);
        }
    }
    if (count)
        *count = c.n;
    if (c.n == 0)
        return NULL;
    char **out = (char **)realloc(c.out, c.n * sizeof(char *));
    if (out)
        c.out = out;
    return (const char**)c.out;
}

const char* directory_iter(dir_t *dir, bool *is_dir) {
#ifdef PLATFORM_UNKNOWN
    return NULL;
#else
    if (!dir || !dir->path)
        return NULL;
#ifdef PLATFORM_WINDOWS
NEXT:
    if (dir->hFind <= 0) {
        if (!directory_exists(dir->path) ||
            (hFind = FindFirstFile(dir->path, &dir->findData)) == INVALID_HANDLE_VALUE)
            return NULL;
    } else {
        if (!FindNextFile(hFind, &findData)) {
            FindClose(dir->hFind);
            return NULL;
        }
    }

    if (!strcmp(dir->findData.cFileName, ".") ||
        !strcmp(dir->findData.cFileName, ".."))
        goto NEXT;
    if (dir->findData.dwFileAttributes == INVALID_FILE_ATTRIBUTES)
        goto NEXT;
    if (is_dir)
        *is_dir = (dir->findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    return dir->findData.cFileName;
#else
    if (!dir->dir)
        if (!directory_exists(dir->path) || !(dir->dir = opendir(dir->path)))
            return NULL;

    struct dirent* entry = NULL;
NEXT:
    if (!(entry = readdir(dir->dir))) {
        closedir(dir->dir);
        return NULL;
    }

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        goto NEXT;
    const char *full_path = path_join(dir->path, entry->d_name);
    struct stat _stat;
    if (stat(full_path, &_stat) == -1) {
        free((void*)full_path);
        goto NEXT;
    }
    free((void*)full_path);

    if (is_dir)
        *is_dir = S_ISDIR(_stat.st_mode);
    return entry->d_name;
#endif
#endif
}

void directory_iter_end(dir_t *dir) {
    if (!dir)
        return;
#ifdef PLATFORM_WINDOWS
    FindClose(dir->hFind);
#elif defined(PLATFORM_POSIX)
    closedir(dir->dir);
#endif
}

static bool _paul_wildcard_match(const char *pattern, const char *str);
static bool _paul_path_glob_from_pattern(const char *pattern, glob_callback callback, void *userdata);

bool path_glob(const char *pattern, glob_callback callback, void *userdata) {
    // Use file-scope helper
    if (!pattern || !callback)
        return false;

    // Split pattern into directory part and file pattern part
    const char *last_sep = strrchr(pattern, PATH_SEPARATOR);
    char *tmp_dir = NULL;

    if (last_sep) {
        size_t dirlen = last_sep - pattern;
        tmp_dir = (char*)malloc(dirlen + 1);
        if (!tmp_dir)
            return false;
        memcpy(tmp_dir, pattern, dirlen);
        tmp_dir[dirlen] = '\0';
    }

    bool result = false;
    // call helper implemented below
    result = _paul_path_glob_from_pattern(pattern, callback, userdata);

    if (tmp_dir)
        free(tmp_dir);
    return result;
}

// Static wildcard matcher supporting '*' and '?'
static bool _paul_wildcard_match(const char *pattern, const char *str) {
    const char *p = pattern, *s = str;
    const char *star = NULL, *ss = NULL;

    while (*s) {
        if (*p == '*') {
            star = p++;
            ss = s;
        } else if (*p == '?') {
            p++; s++;
        } else if (*p == '[') {
            // Character class
            bool neg = false;
            p++;
            if (*p == '!' || *p == '^') { neg = true; p++; }
            bool matched = false;
            while (*p && *p != ']') {
                if (p[1] == '-' && p[2] && p[2] != ']') {
                    char start = *p;
                    char end = p[2];
                    if (start <= *s && *s <= end) matched = true;
                    p += 3;
                } else {
                    if (*p == *s) matched = true;
                    p++;
                }
            }
            if (*p == ']') p++;
            if (neg) matched = !matched;
            if (matched) { s++; continue; }
            if (star) { p = star + 1; s = ++ss; continue; }
            return false;
        } else if (*p == *s) {
            p++; s++;
        } else if (star) {
            p = star + 1;
            s = ++ss;
        } else {
            return false;
        }
    }
    while (*p == '*') p++;
    return *p == '\0';
}
// Split a pattern into components by PATH_SEPARATOR. Returns a newly
// allocated array of strings (components) and sets count. Caller must free each
// component and the array.
static char** _paul_split_pattern(const char *pattern, int *count) {
    if (!pattern) return NULL;
    int cap = 8;
    char **parts = (char**)malloc(cap * sizeof(char*));
    if (!parts) return NULL;
    int n = 0;
    const char *start = pattern;
    const char *p = pattern;
    while (*p) {
        if (*p == PATH_SEPARATOR) {
            if (p > start) {
                int len = (int)(p - start);
                parts[n] = (char*)malloc(len + 1);
                if (!parts[n]) goto fail;
                memcpy(parts[n], start, len);
                parts[n][len] = '\0';
                n++;
                if (n >= cap) { cap *= 2; char **tmp = (char**)realloc(parts, cap * sizeof(char*)); if (!tmp) goto fail; parts = tmp; }
            }
            start = p + 1;
        }
        p++;
    }
    if (p > start) {
        int len = (int)(p - start);
        parts[n] = (char*)malloc(len + 1);
        if (!parts[n]) goto fail;
        memcpy(parts[n], start, len);
        parts[n][len] = '\0';
        n++;
    }
    *count = n;
    return parts;
fail:
    for (int i = 0; i < n; ++i) free(parts[i]);
    free(parts);
    *count = 0;
    return NULL;
}

// Recursive component-based glob helper.
// comps: array of pattern components, comp_count number of components.
// idx: current component index to match within dirpath.
static bool _paul_path_glob_comp_helper(const char *dirpath, char **comps, int comp_count, int idx, glob_callback callback, void *userdata) {
    if (!dirpath || !comps || !callback) return false;
    if (idx >= comp_count) return false;

    bool is_last = (idx == comp_count - 1);
    const char *comp = comps[idx];

    dir_t d = {.path = dirpath};
    const char *name = NULL;
    bool is_dir = false;
    bool ok = true;

    // Special handling for '**'
    if (strcmp(comp, "**") == 0) {
        // First try zero-length match: advance to next component without descending
        if (idx + 1 < comp_count) {
            if (!_paul_path_glob_comp_helper(dirpath, comps, comp_count, idx + 1, callback, userdata))
                return false;
        } else {
            // '**' is the last component: match everything recursively under dirpath
            while ((name = directory_iter(&d, &is_dir)) != NULL) {
                if (!is_dir) {
                    int r = callback(dirpath, name, userdata);
                    if (r != 0) { ok = false; break; }
                } else {
                    char *subdir = (char*)path_join(dirpath, name);
                    if (!subdir) { ok = false; break; }
                    if (!_paul_path_glob_comp_helper(subdir, comps, comp_count, idx, callback, userdata)) {
                        free((void*)subdir);
                        ok = false;
                        break;
                    }
                    free((void*)subdir);
                    continue;
                }
            }
            directory_iter_end(&d);
            return ok;
        }

        // Then, for each subdirectory, let '**' match one or more components by
        // recursing with the same idx (so '**' can match multiple components).
        while ((name = directory_iter(&d, &is_dir)) != NULL) {
            if (is_dir) {
                char *subdir = (char*)path_join(dirpath, name);
                if (!subdir) { ok = false; break; }
                if (!_paul_path_glob_comp_helper(subdir, comps, comp_count, idx, callback, userdata)) {
                    free((void*)subdir);
                    ok = false;
                    break;
                }
                free((void*)subdir);
            } else {
                /* nothing to free for name */
            }
        }
        directory_iter_end(&d);
        return ok;
    }

    // Normal component (may contain '*' or '?')
    while ((name = directory_iter(&d, &is_dir)) != NULL) {
        if (_paul_wildcard_match(comp, name)) {
            if (is_last) {
                // Last component -> match files (and possibly directories?)
                int r = callback(dirpath, name, userdata);
                if (r != 0) { ok = false; break; }
                continue;
            } else {
                if (is_dir) {
                    char *subdir = (char*)path_join(dirpath, name);
                    if (!subdir) { ok = false; break; }
                    if (!_paul_path_glob_comp_helper(subdir, comps, comp_count, idx + 1, callback, userdata)) {
                        free((void*)subdir);
                        ok = false;
                        break;
                    }
                    free((void*)subdir);
                    continue;
                } else {
                    continue;
                }
            }
        }
        /* nothing to free for name */
    }
    directory_iter_end(&d);
    return ok;
}

// Entry point: split pattern into components and start recursion.
static bool _paul_path_glob_from_pattern(const char *pattern, glob_callback callback, void *userdata) {
    if (!pattern || !callback) return false;

    int comp_count = 0;
    char **comps = _paul_split_pattern(pattern, &comp_count);
    if (!comps || comp_count == 0) return false;

    // If pattern contains no PATH_SEPARATOR and recursive is true and the pattern
    // does not include '**', we still allow recursion by searching subdirs for
    // matches (compat mode). To keep semantics simple, respect explicit '**'.

    // Determine starting directory: if pattern begins with separator, start at root
    const char *start_dir = ".";
    if (pattern[0] == PATH_SEPARATOR)
        start_dir = path_get_root_dir();

    bool ok = _paul_path_glob_comp_helper(start_dir, comps, comp_count, 0, callback, userdata);

    for (int i = 0; i < comp_count; ++i) free(comps[i]);
    free(comps);
    return ok;
}

#define _WALK(FN, PATH, RECURSIVE, CALLBACK, USERDATA)                     \
    if (!(PATH) || !directory_exists(PATH))                                \
        return false;                                                      \
    dir_t d = {.path = (PATH)};                                            \
    const char *name = NULL;                                               \
    bool is_dir = false;                                                   \
    while ((name = directory_iter(&d, &is_dir)) != NULL)                   \
    {                                                                      \
        const char *full_path = path_join((PATH), name);                   \
        if (is_dir)                                                        \
        {                                                                  \
            if (RECURSIVE)                                                 \
                if (FN(full_path, RECURSIVE, CALLBACK, USERDATA) == false) \
                    goto BAIL;                                             \
        }                                                                  \
        else if (!CALLBACK((PATH), name, USERDATA))                        \
            goto BAIL;                                                     \
        free((void *)full_path);                                           \
        continue;                                                          \
    BAIL:                                                                  \
        directory_iter_end(&d);                                            \
        free((void *)full_path);                                           \
        return false;                                                      \
    }                                                                      \
    return true;

bool path_walk(const char *path, bool recursive, walk_callback callback, void *userdata) {
    _WALK(path_walk, path, recursive, callback, userdata);
}

#ifdef PLATFORM_HAS_BLOCKS
struct _block_ctx {
    glob_block block;
    void *userdata;
};

static int _block_adaptor(const char *pattern, const char *filename, void *ud) {
    struct _block_ctx *c = (struct _block_ctx *)ud;
    return c->block(pattern, filename, c->userdata);
}

bool path_glob_block(const char *pattern, glob_block callback, void *userdata) {
    if (!pattern || !callback)
        return false;
    struct _block_ctx ctx = { callback, userdata };
    return path_glob(pattern, _block_adaptor, &ctx);
}

bool path_walk_block(const char *path, bool recursive, walk_block callback, void *userdata) {
    _WALK(path_walk_block, path, recursive, callback, userdata);
}
#endif // PLATFORM_HAS_BLOCKS

bool path_exists(const char *path) {
    if (!path)
        return false;
#ifdef PLATFORM_WINDOWS
    DWORD attrs = GetFileAttributesA(path);
    return attrs != INVALID_FILE_ATTRIBUTES;
#elif defined(PLATFORM_POSIX)
    struct stat st;
    if (stat(path, &st) == -1)
        return false;
    return S_ISDIR(st.st_mode) || S_ISREG(st.st_mode);
#else
    return false;
#endif
}

const char* path_get_working_directory(void) {
    static char buffer[MAX_PATH];
    memset(buffer, 0, MAX_PATH * sizeof(char));
#ifdef PLATFORM_WINDOWS
    DWORD result = GetCurrentDirectoryA((DWORD)MAX_PATH, buffer);
    return result > 0 && result < buffer_size;
#elif defined(PLATFORM_POSIX)
    return getcwd(buffer, MAX_PATH);
#endif
}

bool path_set_working_directory(const char *path) {
    if (!path || !directory_exists(path))
        return false;
#ifdef PLATFORM_WINDOWS
    return SetCurrentDirectoryA(path) != 0;
#elif defined(PLATFORM_POSIX)
    return chdir(path) == 0;
#endif
}

const char* path_get_root_dir(void) {
#ifdef PLATFORM_WINDOWS
    static char root[4]  = {'\0'};
    if (root[0] == '\0') {
        char tmp[MAX_PATH];
        GetWindowsDirectory(tmp, MAX_PATH);
        memcpy(root, tmp, 4 * sizeof(char));
    }
    return root;
#elif defined(PLATFORM_POSIX)
    return "/";
#else
    return NULL;
#endif
}

#ifdef PLATFORM_WINDOWS
static const char* __get_path(const GUID* folderid) {
    LPWSTR path;
    HRESULT result = SHGetKnownFolderPath(folderid, 0, NULL, &path);
    if (result != S_OK)
        return NULL;
    int size = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
    if (size == 0) {
        CoTaskMemFree(path);
        return NULL;
    }
    static const char root[MAX_PATH];
    WideCharToMultiByte(CP_UTF8, 0, path, -1, root, size, NULL, NULL);
    CoTaskMemFree(path);
    return root;
}
#endif

// Check if we can use Cocoa APIs
#if defined(COCOA_FOUNDATION)
#define PAUL_OS_USE_COCOA
#endif

#ifdef PLATFORM_MACOS
#ifdef PAUL_OS_USE_COCOA
#if __LP64__ || (TARGET_OS_EMBEDDED && !TARGET_OS_IPHONE) || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
#define NSIntegerEncoding "q"
#define NSUIntegerEncoding "L"
#else
#define NSIntegerEncoding "i"
#define NSUIntegerEncoding "I"
#endif

#ifdef __arm64__
#define abi_objc_msgSend_stret objc_msgSend
#else
#define abi_objc_msgSend_stret objc_msgSend_stret
#endif
#ifdef __i386__
#define abi_objc_msgSend_fpret objc_msgSend_fpret
#else
#define abi_objc_msgSend_fpret objc_msgSend
#endif

#define __STRINGIFY(s) #s

#define sel(NAME) sel_registerName(__STRINGIFY(NAME))
#define class(NAME) ((id)objc_getClass(__STRINGIFY(NAME)))
#define protocol(NAME) objc_getProtocol(__STRINGIFY(NAME))

#define ObjC(RET, ...) ((RET(*)(id, SEL, ##__VA_ARGS__))objc_msgSend)

#ifndef __OBJC__
typedef enum {
    NSApplicationDirectory  = 1,
    NSDocumentDirectory     = 9,
    NSDesktopDirectory      = 12,
    NSDownloadsDirectory    = 15,
    NSMoviesDirectory       = 17,
    NSMusicDirectory        = 18,
    NSPicturesDirectory     = 19,
} NSSearchPathDirectory;

typedef enum {
    NSUserDomainMask        = 1UL << 0,
    NSLocalDomainMask       = 1UL << 1,
    NSNetworkDomainMask     = 1UL << 2,
    NSSystemDomainMask      = 1UL << 3,
    NSAllDomainsMask        = 0x0FFFFFFF
} NSSearchPathDomainMask;
#endif

static const char* __get_path(NSSearchPathDirectory directory) {
    id file_manager = ObjC(id)(class(NSFileManager), sel(defaultManager));
    id urls = ObjC(id, NSUInteger, NSUInteger)(file_manager, sel(URLForDirectory:inDomains:), directory, 1);
    id url = ObjC(id)(urls, sel(firstObject));
    const char *path = (const char*)ObjC(id)(ObjC(id)(url, sel(absoluteString)), sel(UTF8String));
    long path_length = strlen(path);
    static char _path[MAX_PATH];
    memcpy(_path, path, path_length * sizeof(char));
    if (path_length < MAX_PATH)
        _path[path_length] = '\0';
    return _path;
}
#else
// Fallback implementation without Cocoa, using $HOME + standard folder names
static const char* __secret_macos_get_path(const char *name) {
    // Turn name from `NSApplicationDirectory` to `Application`
    if (strncmp(name, "NS", 2) != 0)
        return NULL;
    name += 2;
    const char *end = name;
    // Check until find string "Directory"
    while (*end && strncmp(end, "Directory", 9) != 0)
        end++;
    if (!*end)
        return NULL;
    size_t len = end - name;
    char *tmp = (char*)malloc(len + 1);
    if (!tmp)
        return NULL;
    memcpy(tmp, name, len);
    tmp[len] = '\0';
    // Get from $HOME and append tmp
    const char *home = environment_variable("HOME");
    if (!home)
        return NULL;
    const char *join = path_join(home, tmp);
    free((void*)tmp);
    // Check if directory exists
    if (directory_exists(join))
        return join;
    free((void*)join);
    return NULL;
}

#define __get_path(NAME) __secret_macos_get_path(#NAME)
#endif
#endif

#ifdef PLATFORM_NIX
static const char* __get_path_ptr(const char *name) {
    const char *home = path_get_home_dir();
    const char *join = path_join(home, name);
    const char *_name = strdup(name);
    size_t name_len = strlen(name);
    file_t ud = io_invalid;

    if (directory_exists(join))
        goto BAIL;

    for (char *p = _name; *p; p++)
        if (*p >= 'a' && *p <= 'z')
            *p -= 32;
    const char *user_dirs = path_join(home, ".config/user-dirs.dirs");
    if (!io_open(&ud, user_dirs, FILE_READ))
        goto BAIL;

    char line[1024];
    while (!io_eof(ud)) {
        memset(line, 0, 1024 * sizeof(char));
        if (!io_read_line(ud, line, 1024))
            break;
        if (!strncmp("XDG_", line, 3) &&
            !strncmp(_name, line + 4, name_len)) {
            free((void*)join);
            free((void*)_name);
            char *l = line;
            for (; *l && *l != '\n'; l++);
            if (*l == '\n')
                *l = '\0';

            char *off = line + (7 + name_len);
            bool is_home = false;
            if (!strncmp("$HOME", off, 5)) {
                is_home = true;
                off += 5;
            }
            if (off[0] == PATH_SEPARATOR)
                off++;
            char *p = off;
            for (; *p && *p != '"'; p++);
            size_t diff = p - off;
            memcpy(line, off, diff * sizeof(char));
            memset(line + diff, 0, (1024 - diff) * sizeof(char));
            if (is_home)
                return path_join(home, line);
            else
                return strdup(line);
        }
    }

BAIL:
    if (io_valid(ud))
        io_close(&ud);
    if (_name)
        free((void*)_name);
    return join;
}

static const char* __get_path(const char *name) {
    static char path[MAX_PATH];
    memset(path, 0, MAX_PATH * sizeof(char));
    const char *tmp = __get_path_ptr(name);
    if (tmp) {
        memcpy(path, tmp, strlen(tmp) * sizeof(char));
        free((void*)tmp);
    }
    return path;
}
#endif

const char* path_get_home_dir(void) {
#ifdef PLATFORM_UNKNOWN
    return NULL;
#else
    static char home[MAX_PATH] = {'\0'};
    if (home[0] == '\0') {
        const char *_home = NULL;
        size_t _size = 0;
#ifdef PLATFORM_WINDOWS
        _home = __get_path(&FOLDERID_Profile);
        _size = strlen(_home);
#elif defined(PLATFORM_MACOS)
#ifdef PAUL_OS_USE_COCOA
        id file_manager = ObjC(id)(class(NSFileManager), sel(defaultManager));
        id url = ObjC(id)(file_manager, sel(homeDirectory));
        _home = (const char*)ObjC(id)(ObjC(id)(url, sel(absoluteString)), sel(UTF8String));
        _size = strlen(_home);
#else
        if (!(_home = environment_variable("HOME")))
            return NULL;
        _size = strlen(_home);
#endif
#elif defined(PLATFORM_NIX)
        if (!(_home = environment_variable("HOME")))
            return NULL;
        _size = strlen(_home);
#endif
        if (_size > MAX_PATH)
            _size = MAX_PATH;
        memcpy(home, _home, _size * sizeof(char));
        memset(home + _size, 0, MAX_PATH - _size * sizeof(char));
#ifdef PLATFORM_NIX
        free((void*)_home);
#endif
    }
    return home;
#endif
}

const char* path_get_documents_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Documents);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSDocumentDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Documents");
#else
    return NULL;
#endif
}

const char* path_get_downloads_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Downloads);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSDownloadsDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Downloads");
#else
    return NULL;
#endif
}

const char* path_get_video_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Videos);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSMoviesDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Videos");
#else
    return NULL;
#endif
}

const char* path_get_music_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Music);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSMusicDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Music");
#else
    return NULL;
#endif
}

const char* path_get_picture_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Pictures);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSPicturesDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Pictures");
#else
    return NULL;
#endif
}

const char* path_get_application_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_ProgramFiles);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSApplicationDirectory);
#else
    return NULL;
#endif
}

const char* path_get_desktop_dir(void) {
#ifdef PLATFORM_WINDOWS
    return __get_path(&FOLDERID_Desktop);
#elif defined(PLATFORM_MACOS)
    return __get_path(NSDesktopDirectory);
#elif defined(PLATFORM_NIX)
    return __get_path("Desktop");
#else
    return NULL;
#endif
}

const char* path_get_file_extension(const char *path) {
    if (!path)
        return NULL;
    char *dot = strrchr((char*)path, '.');
    return dot ? dot + 1 : NULL;
}

const char* path_get_file_name(const char *path) {
    if (!path)
        return NULL;
    const char *last_slash = strrchr(path, PATH_SEPARATOR);
    return last_slash ? last_slash + 1 : path;
}

const char* path_get_file_name_no_extension(const char *path) {
    if (!path)
        return NULL;
    const char *file_name = path_get_file_name(path);
    if (!file_name)
        return NULL;
    size_t length = strlen(file_name);
    char *dot = strrchr((char*)file_name, '.');
    if (dot) {
        length = dot - file_name;
        if (length == 0)
            return NULL;
    }
    char *result = (char*)malloc(length + 1);
    if (!result)
        return NULL;
    strncpy(result, file_name, length);
    result[length] = '\0';
    return result;
}

const char* path_without_file_name(const char *path) {
    if (!path)
        return NULL;
    const char *last_slash = strrchr(path, PATH_SEPARATOR);
    if (!last_slash)
        return NULL;
    size_t length = last_slash - path;
    char *result = (char*)malloc(length + 1);
    if (!result)
        return NULL;
    strncpy(result, path, length);
    result[length] = '\0';
    return result;
}

const char* path_get_directory_name(const char *path) {
    const char *stem = path_without_file_name(path);
    if (!stem)
        return NULL;
    const char *last_slash = strrchr(stem, PATH_SEPARATOR);
    return last_slash ? last_slash + 1 : stem;
}

const char* path_get_parent_directory(const char *path) {
    if (!path)
        return NULL;
    const char *last_slash = strrchr(path, PATH_SEPARATOR);
    if (!last_slash || last_slash == path)
        return path_get_root_dir();
    size_t length = last_slash - path;
    char *result = (char*)malloc(length + 1);
    if (!result)
        return NULL;
    strncpy(result, path, length);
    result[length] = '\0';
    return NULL;
}

const char* path_resolve(const char *path) {
    if (!path)
        return NULL;

    const char *full_path = NULL;
    char *result = NULL;
    
    // Handle tilde expansion
    if (path[0] == '~') {
        const char *home = path_get_home_dir();
        if (!home)
            return NULL;

        if (path[1] == '\0')
            return home;  // Just "~"
        else if (path[1] == PATH_SEPARATOR)
            full_path = path_join(home, path + 2);  // Skip "~/"
        else
            full_path = path_join(home, path + 1);  // "~something"

        if (!full_path)
            return NULL;
    }
    // Handle absolute paths
    else if (path[0] == PATH_SEPARATOR) {
        full_path = strdup(path);
        if (!full_path)
            return NULL;
    } else { // Handle relative paths
        const char *cwd = path_get_working_directory();
        if (!cwd)
            return NULL;
        full_path = path_join(cwd, path);
        if (!full_path)
            return NULL;
    }
    
    // Now resolve . and .. components
    // Split path into components
    int component_count = 0;
    int capacity = 16;
    char **components = (char**)malloc(capacity * sizeof(char*));
    if (!components) {
        free((void*)full_path);
        return NULL;
    }
    
    // Tokenize the path
    char *path_copy = strdup(full_path);
    if (!path_copy) {
        free(components);
        free((void*)full_path);
        return NULL;
    }
    
    char *token = strtok(path_copy, "/");
    while (token) {
        // Expand capacity if needed
        if (component_count >= capacity) {
            capacity *= 2;
            char **new_components = (char**)realloc(components, capacity * sizeof(char*));
            if (!new_components) {
                // Cleanup
                for (int i = 0; i < component_count; i++)
                    free(components[i]);
                free(components);
                free(path_copy);
                free((void*)full_path);
                return NULL;
            }
            components = new_components;
        }
        
        if (strcmp(token, ".") == 0) {
            // Skip current directory references
        } else if (strcmp(token, "..") == 0) {
            // Go back one directory
            if (component_count > 0) {
                free(components[component_count - 1]);
                component_count--;
            }
        } else {
            // Regular component
            if (!(components[component_count] = strdup(token))) {
                // Cleanup on error
                for (int i = 0; i < component_count; i++)
                    free(components[i]);
                free(components);
                free(path_copy);
                free((void*)full_path);
                return NULL;
            }
            component_count++;
        }
        
        token = strtok(NULL, "/");
    }
    
    // Build the final path
    size_t total_length = 1;  // Start with 1 for root "/"
    for (int i = 0; i < component_count; i++) {
        total_length += strlen(components[i]);
        if (i < component_count - 1 || component_count > 0)
            total_length++;  // For separator
    }
    
    if (!(result = (char*)malloc(total_length + 1))) {
        // Cleanup
        for (int i = 0; i < component_count; i++)
            free(components[i]);
        free(components);
        free(path_copy);
        free((void*)full_path);
        return NULL;
    }
    
    // Start with root
    result[0] = PATH_SEPARATOR;
    result[1] = '\0';
    
    // Add components
    for (int i = 0; i < component_count; i++) {
        if (i > 0)
            strcat(result, "/");
        strcat(result, components[i]);
    }
    
    // Handle special case of root directory
    if (component_count == 0)
        strcpy(result, "/");
    
    // Cleanup
    for (int i = 0; i < component_count; i++)
        free(components[i]);
    free(components);
    free(path_copy);
    free((void*)full_path);
    
    return result;
}

const char* path_join(const char *a, const char *b) {
    if (!a || !b)
        return NULL;
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);
    if (!a_len || !b_len)
        return NULL;
    /* allocate a_len + 1 (sep) + b_len + 1 (NUL) */
    size_t total_len = a_len + 1 + b_len;
    char *result = (char*)malloc(total_len + 1);
    if (!result)
        return NULL;
    /* copy a */
    memcpy(result, a, a_len);
    /* separator */
    result[a_len] = PATH_SEPARATOR;
    /* copy b */
    memcpy(result + a_len + 1, b, b_len);
    result[total_len] = '\0';
    return result;
}

const char* path_join_va(int n, ...) {
    if (n <= 0)
        return NULL;
    va_list args;
    va_start(args, n);
    size_t total_length = 0;
    for (int i = 0; i < n; i++) {
        const char *part = va_arg(args, const char*);
        if (part) {
            total_length += strlen(part);
            if (i < n - 1)
                total_length += 1;
        }
    }
    va_end(args);
    if (total_length == 0)
        return NULL;
    char *result = (char*)malloc(total_length + 1);
    if (!result)
        return NULL;

    va_start(args, n);
    size_t pos = 0;
    for (int i = 0; i < n; i++) {
        const char *part = va_arg(args, const char*);
        if (part) {
            size_t part_length = strlen(part);
            memcpy(result + pos, part, part_length);
            pos += part_length;
            if (i < n - 1)
                result[pos++] = PATH_SEPARATOR;
        }
    }
    va_end(args);
    result[pos] = '\0';
    return result;
}

const char** path_split(const char *path, size_t *count) {
    const char **parts = NULL;
    int parts_count = 0;
    const char *start = path;
    int index = 0;

    if (!path)
        goto BAIL;
    for (const char *p = path; *p; p++)
        if (*p == PATH_SEPARATOR) {
            if (p > start)
                parts_count++;
            start = p + 1;
        }
    if (start < path + strlen(path))
        parts_count++;
    if (parts_count == 0)
        goto BAIL;

    if (!(parts = (const char**)malloc(parts_count * sizeof(char*))))
        goto BAIL;
    start = path;
    for (const char *p = path; *p; p++)
        if (*p == PATH_SEPARATOR) {
            if (p > start) {
                size_t length = p - start;
                parts[index] = (char*)malloc(length + 1);
                if (!parts[index])
                    goto DEAD;
                strncpy((char*)parts[index], start, length);
                ((char*)parts[index])[length] = '\0';
                index++;
            }
            start = p + 1;
        }
    if (start < path + strlen(path)) {
        size_t length = path + strlen(path) - start;
        parts[index] = (char*)malloc(length + 1);
        if (!parts[index])
            goto DEAD;
        strncpy((char*)parts[index], start, length);
        ((char*)parts[index])[length] = '\0';
        index++;
    }
    goto BAIL;
DEAD:
    if (parts) {
        for (int i = 0; i < index; i++)
            if (parts[i])
                free((void*)parts[i]);
        free(parts);
    }
    parts = NULL;
    parts_count = -1;
BAIL:
    if (count)
        *count = parts_count;
    return parts;
}
#endif