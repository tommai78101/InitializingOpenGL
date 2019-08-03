# Initializing OpenGL: <span style="font-size: 75%">A Sadistic Approach to Modern OpenGL</span>

A book written in my own spare time, that has notes on how to begin an OpenGL project. The main goal of writing this book, is so a complete beginner can follow along and learn as much as they can with a ton of information as possible. And it is because of this goal, I need to cite a lot of references and do research to make sure the information I got is accurately represented to the readers. And it will take a while to complete each chapter.

|OpenGL versions|Goals|
|:---:|:---|
|1.X, 2.X, 3.2+, 4.X|Initialization only|
|3.1|Outlier OpenGL support|
|any|Depends on book progress|
|4.6|End goal|


Currently, the book is not done, but I am releasing an "alpha" version of the book. It's provided both as a DOCX file, and a PDF file for viewing pleasures. This is a reward for you searching and lurking on Github, or that somehow this book was found by a search engine, and you just so happened to see this book appearing in the search results. And thus, it is why this book is secretly hidden away online.

DOCX file must embed system fonts for compatibilty with Windows, MacOS X, and Ubuntu/Linux.

Scroll on down to see the future roadmap. Table of Contents will be updated whenever new contents are added to the draft.

------

## Table of Contents

```
PREFACE ........................................................................... 1 
CHAPTER 1 ......................................................................... 3 
	Installation .............................................................. 4 
	Picking Your Poison ....................................................... 5 
	Development Setup ......................................................... 6 
CHAPTER 2 ........................................................................ 11
	Choosing an OpenGL Version ............................................... 12
		Drawbacks of Very Old OpenGL Versions ............................ 13
		Consider the Not-So-Old OpenGL Versions .......................... 15
		Summarized OpenGL Initialization Steps ........................... 17
	Creation of a Window ..................................................... 18
		Using the WinMain() Entry Point .................................. 19
		Using the Main() Entry Point ..................................... 21
	A Dummy OpenGL Context ................................................... 23
		The Pixel Format Descriptor ...................................... 24
		Understanding Pixel Formats ...................................... 27
		Choosing and Setting a Pixel Format .............................. 31
	Initialization of OpenGL ................................................. 34
		Introduction to Loading Libraries ................................ 34
		Modularizing our Entry Points .................................... 36
	Hybrid Graphics Support .................................................. 37
		Brief History of Intel Integrated Graphics ....................... 37
		Handling the Consequences of Dual Graphics ....................... 39
	Summary .................................................................. 46
		Full Source Code (Including Notes) ............................... 46

REFERENCES ....................................................................... 58 

APPENDIX ......................................................................... 62 
	A Hungarian Notation Trick ................................................ i 
	Documented Quirks ........................................................ iv 
		ShowWindow Getting Ignored on First Invocation ................... iv 
		The “sprintf” History ............................................. v 
	Byte Ordering (Part 1/3) ............................................... viii 
	A Unicode Primer (Part 2/3)................................................ x 
		What is Unicode? ................................................. xi 
		UCS-2 ............................................................ xi 
		UTF-16 ........................................................... xi 
		UCS-4 and UTF-32 ................................................. xv 
		UTF-1 ........................................................... xvi 
		UTF-8 ............................................................ xx 
		What is next? ..................................................xxiii 
	Applying Unicode (Part 3/3) ............................................ xxiv 
		Making Common Functions ........................................ xxiv 
		Converting UTF-16 to UTF-8 .................................... xxvii 
		Converting UTF-8 to UTF-16 ..................................... xxxv 
		Converting UTF-32 to UTF-8 ...................................... xli 
		Converting UTF-8 to UTF-32 ..................................... xliv 
		Converting UTF-32 to UTF-16 .................................... xlix 
		Converting UTF-16 to UTF-32 ..................................... liv 
```

------

## Roadmap

(Updated: January 1, 2019 - Included scheduling conflicts with real-life into the timeline.)   
(Updated: March 20, 2019 - Adjusting schedule to update the book only on weekends.)
(Updated: August 4, 2019 - Finished Triangle/Hexagon OpenGL back in July, was about to write book, but real life got in the way.)

|Timeline|Topic of Interests|Estimated page counts|
|:---|:---|---:|
|November 8, 2018 ~ November 26, 2018|Personal Vacation Trip|N/A|
|November 28, 2018 ~ December 10, 2018|Finish the Appendix (Postponed)|10|
|January 28, 2019 ~ February 24, 2019|Finish the Appendix|10|
|***February 9, 2019 ~ February 24, 2019***|***Feedback Phase***|***N/A***|
|February 25, 2019 ~ March 1, 2019|Do tax returns (Time may change!)|N/A|
|March 1, 2019 ~ March 17, 2019|Rewrite "Initialization of OpenGL" in Chapter 2|5|
|March 1, 2019 ~ April 1, 2019|Continue creating OpenGL context|10|
|May 2019 ~ July 2019|Get triangle showing up|15|
|August 2019 ~ October 2019|Boilerplate code in C and C++ **(Delayed)**|25|
|***August 5, 2019 ~ TBD***|***Real Life Takes Over***|***N/A***|
|Future|Depends on Issues/Feedback/Real Life|N/A|

## Sneak Peek

This is what I planned to add to Chapter 3 before something happened in real life:

<img src="https://github.com/tommai78101/InitializingOpenGL/images/hexagon.gif" />

<div style="display: inline-block; height: 30px;"></div>

|Estimated final total pages count (not including Appendix)|Current total pages count (not including Appendix)|
|--:|--:|
|110|57|


------

## How to Contribute

I welcome those who contribute by reporting an Issue. **Those who do, will be listed as a co-author.**

Just state the summary of the topic and list out what you wished to read about. If possible, if you have resources and research materials provided in the Issue report, I'll gladly do my best to get all the details in.

------

## Credits

### Main Authors

* Author: Thompson Lee  
* Co-Author: wedr  

### Contributors

* solidfox  
* d3xor  
* gehn  
* rindolf  
* nitrix  
* vendu  
* niggler  
* WinterMute  
* ScrisM  
* fincs  
* yellows8  
* smea  

### Github Contributors

* nickrolfe
* gogoprog (Issue #13)

### Reddit Contributors

* PcChip
* SkyrimForSwitch
* silwr

### Other contributors

* The ##programming Freenode IRC channel  
* The ##javascript Freenode IRC channel 
* The ##opengl Freenode IRC channel 
* The Khronos Group
* Stack Overflow  
* Microsoft  
* Google
* MSDN Community  
* MSDN Docs  
* Reddit

MIT Licensed.
