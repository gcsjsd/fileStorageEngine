
# ECE180a-GroupProject
A bit more challenging, a bit more work, but a lot more rewarding!

## It's Chloe's World, We're Just Living In It

Chloe is the Director of Engineering at JobCo, a company that exists somewhere within a universe full of possibility -- so much possibility in fact -- that anything that *can* happen, probably already has.  Chloe likes to believe that she has an open mind. But the trouble with having an open mind is that people will insist on coming along and trying to put things in it. So despite the fact that everyone knows that Zombies don't exist, several are tenured and working in the Marketing Department. 

Like so many startups, JobCo. has sadly discovered that customers aren't interested in buying their namesake product. So, as is common practice in Silicon Valley, JobCo has decided to pivot. They're going to build and sell a completely _new_ product. The JobCo CEO wants to demonstrate the new product at CES. In **FIVE** weeks.  As a result, your team have been invited to submit your version of the "The Product", described below. 

## May The Best Team Win

You and your team are expected to build a program that offers the functionality summarized below. 

### Feature 1 -- command processing

Your product will run as a command line application (no GUI). Like most command-line applications, users will provide commands to your program by providing command-line arguments. The general form of the commands will be:

```
sfarchiver command <optional args>
```

As shown above, "sfarchiver" is the name of your executable. "command" is the name of the command your program is being asked to execute. This _may_ be followed by an <optional> list of arguments. Some commands require multiple arguments, while others require none at all. A complete list of commands and associated arguments is provided later in this document.
  
For example, your program must be able to respond to a command-line request to display the application version number. To show the version number, a user will initiate the following command:

```
sfarchiver -v 
```

In this example, the command name is "-v", a shorthand that is equivalent to "version". Your program would then respond by showing the current version and build information. (see more details below).


### Feature 2 -- Storage Engine

The whole point of this program is to manage a collection of resources in a single (binary) file we shall call "archives". Similar to the way a .tar or a .zip file stores a collection of compressed files. Note: Compression is not a requirement of this assignment.  However, if your team is bold, and wants to really outperform in the area of storage efficiency, you may "choose" to apply lossless compression to certain data. Again, this is NOT a requirement, and is not recommended for people with heart conditions. :)

#### Basic Storage

Your "storage engine" will create and manage binary files (archives), that are comprised of an arbitrary set of files. Users may add text files, or binary files like images or videos. Your program will not be asked to add any single file larger than 500k in size. It should go without saying, but your program must not change, alter, or corrupt the files that it stores in any way. Assuming a given file has been added to your archive, when it is extracted it must be *exactly* the same.

#### A Note on Space Management

A key goal of your storage engine is to minimize the overall size of your archive files. Imagine that a user adds 3 large files:

| FILE1 | FILE2 | FILE3 |

Then the user deletes the 2nd file. The result (in terms of storage), may look like this (dots indicate free space):

| FILE1 | ..... | FILE3 |


As you can see, your total file is 1/3 larger than it needs to be. In order to get maximum points for efficiency, your storage algorithm might choose to move the data from third file into the space previously occupied by the 2nd file, and then truncate the excess bytes from the archive:

| FILE1 | FILE2 |

A reasonable solution to reduce overall storage space, is to manage your underlying archive file in "chunks" of a fixed size that can easily be moved within the archive. If your program keeps track of which "chunks" are unused, you algorithm could automatically reclaim unused space, rather than just appending new content to the end of your archive.


### Feature 3 -- Searching for Contents

Users of your storage engine will undoubtedly want to be able to search the contents of a given archive. They may want to search in two ways:

1. They may want to find a single file that matches a given string
2. They may want to search the "contents" of the added files (presumably text files) for _content_ that matches a given string


## The Commands

Your program must be able to respond to following commands:

### 1. Add file to Archive
add (archive) "filename" -- add the named file to the archive; if archive doesn't exist, it is automatically created.
Example:
```
sfarchiver add pictures dog.png
```
### 2. Delete file from Archive
del (archive) "filename" -- delete a named file from storage
Example:
```
sfarchiver del pictures cat.png
```
### 3. List files in Archive
- sfarchiver list (archive)  -- show all the files in an archive; -l is an alias for list
- sfarchiver list (archive) "filename" -- show properties of any filename that matches given string
```
filename size date-added
filename size date-added
...
```

### 4. Find file containing "string" within Archive
sfarchiver find (archive) "string" -- show properties of any textfile that contain the given string

### 5. Extract a file from Archive
sfarchiver extract (archive) "filename"  -- emit a copy of the named file to the terminal

### 6. Show program version
sfarchiver version (show version number and build date); -v is an alias for "version"

`sfarchiver version 2.3 March 10, 2018`

### 7. Unknown commands

If asked to execute a command you don't understand, emit a clear and appropriate error message. 
 
## The Requirements

1. Your solution must be built using C++, and all of the code must be your own, original code. 
2. You MAY use the C++ STL in your solution if you deem it appropriate to do so. No "3rd party" libraries may be used. 
3. Your solution must be a stand-alone application, capable of being built (make) and run from the command line. 
4. You cannot use external applications or services to do the work; your application must implement all the functionality. 
5. As this is C++, you may manage memory as necessary using new/delete. You may not use malloc/free. Be aware that our tests will include measures of your memory usage, and track whether you properly relinquish memory you have allocated.
6. If your program experiences a crash, do all you can to catch the error and report the problem on the command line, rather than simply failing silently.

## Submitting Your Solution

1. To enter the competition, your team must submit a working (makeable) solution on GitHub, on or before the deadline.
2. Your team must submit a 1-3 page paper describing the technical design concepts you used in your solution. 
3. Submit a "students.json" file that contains the name, pid and email of each student in your group.
4. Your submission is due **no later** than Sunday, March 11, 2018 -- at 11:15pm (PST).

```
[
  {'name':'jack','email':'jack@gmail.com','pid':'xxxyyyzzz'},
  {'name':'jill','email':'jill@gmail.com','pid':'xxxyyyzzz'}
  ...
]
```

As this is a group project, we are using github classroom group project repositories. You are responsible for joining your teammates on the github group project page. The fact that you're reading this document means that you've already received the link we sent that enables you to join your group project.

## Choosing a Winner

The zombies in Marketing are awaiting your submissions. Here's how they will score your work:

### 1. Working Application (45pts)

Vlad-the-Compiler will build your application, and test it using an automated suite of tests. Your solution will recieve 10 points for each completed functional test, so long as you complete all tasks within the standard time window and without crashing.

If your solution doesn't build at all, you will receive 0 points in this category.

### 2. Performance and Efficiency (30pts)

Your solution will be measured and stack ranked along the dimensions of total performance and memory efficiency. 

#### Performance 

Performance is an aggregated measure of clock ticks to perform a set of requested actions.

- Solutions in the 1st quartile in performance will receive 10 points
- Solutions in the 2nd quartile in performance will receive 8 points
- Solutions in the 3rd quartile in performance will receive 6 points
- Solutions in the 4th quartile in performance will recieve 4 points

#### Memory Efficiency

Memory efficiency is a measure of the total memory used by your program during tests. Points will be subtracted for solutions that cause memory leaks.

- Solutions in the 1st quartile in memory efficiency will receive 10 points
- Solutions in the 2nd quartile in memory efficiency will receive 8 points
- Solutions in the 3rd quartile in memory efficiency will receive 6 points
- Solutions in the 4th quartile in memory efficiency will recieve 4 points

#### Storage Efficiency

Storage efficiency is a measure of the aggregated disk space used by your program in the test archives.

- Solutions in the 1st quartile in storage efficiency will receive 10 points
- Solutions in the 2nd quartile in storage efficiency will receive 8 points
- Solutions in the 3rd quartile in storage efficiency will receive 6 points
- Solutions in the 4th quartile in storage efficiency will recieve 4 points

### 3. Technical Design Summary (1-3 pages) (20pts)

In addition to being able to write code, or design circuits, engineers need to know how to communicate ideas. Therefore, each team will submit a "Technical Design Summary" paper that describes the approach the team took in solving the problem.  This paper should describe the design ideas, challenges, and outline your solutions. One way to think of this is, imagine that your are standing in front of a whiteboard in front of a room full of engineers trying to explain your design decisions. 

Failure to submit this paper will result in receiving 0 points in this category. And don't even think about making us grab our red correction pen.

### 4. That "Something" Extra... (5pts)

Style matters. Confidence matters too. So do bribes, but our CEO frowns on that, so they're out of bounds. Otherwise, show us some great team spirit. Show us a team who works well together. Show us rock solid code, contributed by everyone on your team.

At the end of your project, you will each take a brief survey that allows you to rate and review the contribution of your team members. It's your job to make sure you contribute fairly with your team.

### Summary Score

Your submission can recieve a total of 100 points, aggregated from points you earn in each of the main categories.

## Prize? Did you say Prize?

Why yes, we did say "Prize". Prize. Prize. Prize. As in, you get something of value for winning this competition -- for some definition of _value_ that is yet to be determined.








