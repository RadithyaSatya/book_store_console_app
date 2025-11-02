# Bookstore Console App

## Features

- Add new books to inventory
- Record sales transactions
- View book inventory and sales history
- Delete books and transaction history
- Sort books using various algorithms
- Automatic data persistence

## How to Compile and Run

### Prerequisites
- C Compiler
- Terminal/Command line access

### Compilation

#### For Linux/Unix Systems (GCC)
```bash
# Navigate to the project directory
cd /path/to/book_store_console_app

# Compile all source files into an executable
gcc -o bookstore_app main_program.c bookstore.c viewHistory.c deleteBook.c deleteHistory.c sorting_Algo.c utils.c
```

#### For macOS (GCC)
```bash
gcc -o bookstore_app main_program.c bookstore.c viewHistory.c deleteBook.c deleteHistory.c sorting_Algo.c utils.c
```

#### Generic C Compiler
```bash
# Replace 'cc' with your available C compiler (gcc, clang, icc, etc.)
cc -o bookstore_app main_program.c bookstore.c viewHistory.c deleteBook.c deleteHistory.c sorting_Algo.c utils.c
```

### Running the Program

#### On Linux/macOS/Unix:
```bash
# Run the compiled executable
./bookstore_app
```

#### On Windows:
```cmd
# Run the compiled executable
bookstore_app.exe

# Or simply
bookstore_app
```
