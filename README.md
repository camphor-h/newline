# newline
A simple newline change tool.  

To convert text file with different newline characters from my windows system to FreeBSD system in a simple way, I wrote this simple program, which is also a refactoring of a program I wrote on Windows.  

Use:  

  newline -[source_type] [filename] -[target_type]  
  
It supports DOS/WIN(CR/LF)  Unix-Like(LF) Classic Mac-OS (CR)  

When I finished the program, I did some search. There are also many usable newline convertor in Unix-Like system. Such as unix2dos mac2unix. But they are not universal. And yet A old program called flip seems exist in some Unix-Like system. It even coincidentally has similar parameter to my program (-d for DOS/WIN -u for Unix-Like, I'm for sure that I didn't know this program when I was designing parameter format for my program). However I cannot find this program and its source codes. So I reinvented this wheel, again. But I think that it's worth it. (～￣▽￣)～
