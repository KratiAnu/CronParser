# Cron Parser

Cron Parser is a command-line utility designed to break down cron expressions, providing users with a clear understanding of when their scheduled tasks will execute.

## Overview

Cron strings can be complex, but Cron Parser simplifies the process. Input your cron string, and get a detailed schedule output.

## Usage

Execute the application with your cron string:

```bash
./cron-parser "*/15 0 1,15 * 1-5 /usr/bin/find"
```


### Cron String Structure
Cron strings have five fields: minute, hour, day of the month, month, and day of the week. 
The command to execute follows these time-related specifications.

### Output Format
The output is a table, showing each field's name in the first 14 columns, followed by a space-separated list of execution times.

### Example
For instance, given the input:

```bash
Copy code
./CronParser "*/15 0 1,15 * 1-5 /usr/bin/find"
```

The output would be:

``````
minute         0 15 30 45
hour           0
day of month   1 15
month          1 2 3 4 5 6 7 8 9 10 11 12
day of week    1 2 3 4 5
command        /usr/bin/find
``````

### Build And Run
1. Clone the repository and build the executable using a C++ compiler:
2. Execute the following cmd to run the Program.cpp

``````
g++ Program.cpp -o CronParser
``````

Execute the program with the desired cron string:

``````
./CronParser "*/15 0 1,15 * 1-5 /usr/bin/find"
``````