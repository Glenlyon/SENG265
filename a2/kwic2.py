'''
Created on Mar 2, 2018

@author: Yiliang Liu V00869672
'''
import sys

#This read only the upper part of text
def readKeyWord():
      keyWord = []
      count = 0
      for lines in sys.stdin:
           if(lines == '::\n'):
                count += 1
           keyWord.append(lines)
           keyWord = [x.strip() for x in keyWord] 
           if(count == 2):
                break
      return keyWord

#This read the lower part of text          
def readContent(keyWord):
      content = []
      notKeyWord = []
      temp = []
      x = 0
      ifKeyWord = 0
      for lines in sys.stdin:
           content.append(lines)
           content = [x.strip() for x in content]
           temp = lines.strip().split(" ")
           for words in temp:
                ifKeyWord = 0;
                for x in range(0, len(keyWord)):
                     if(words == keyWord[x]):
                          if words != " ":
                              ifKeyWord = 1;
                if(ifKeyWord == 0):
                     notKeyWord.append(words)
      return (content, notKeyWord)
              
#This sort the words in order, number first than letters
def sortNotKeyWord(notKeyWord):
    for i in range(len(notKeyWord)-1,0,-1):
         for j in range(i):
              if notKeyWord[j] > notKeyWord[j+1]:
                   temp = notKeyWord[j]
                   notKeyWord[j] = notKeyWord[j+1]
                   notKeyWord[j+1] = temp

#This capitalize the word format the output                   
def capitalization(contentIndex, y, z, target, lines):
     outputLines = lines.split(" ")
     s = " "
     count = 0
     for words in outputLines:
          if words == target and contentIndex[y][z] != 1:
               outputLines[count] = words.upper()
          count += 1
     countLetter = 0
     countWord = 0
     for wordOrder in outputLines:
          if wordOrder.lower() == target:
               break 
          else:
               countWord += 1
          for letterOrder in wordOrder:
                countLetter += 1
     while countWord+countLetter > 20:
          outputLines, countWord, countLetter = isFrontTwenty(countWord, countLetter, outputLines, target)
     countBackLetter = 0
     countBackWord = 0
     j = countWord + 1
     for j in range(j, len(outputLines)):
          countBackWord += 1
          for letterBackOrder in outputLines[j]:
                countBackLetter += 1
     while countBackLetter+countBackWord > 20:
          outputLins, countBackLetter, countBackWord = isBackTwenty(countBackLetter, countBackWord, j, outputLines, target)       
     spaceRange = 20 - countWord - countLetter
     spaceArea = []
     for i in range(0 , spaceRange-1):
          spaceArea.append(" ")
     print ("".join(spaceArea), s.join(outputLines))

#This checks if the front space is twenty     
def isFrontTwenty(countWord, countLetter, lines, target):
     lines.pop(0)
     countWord = 0
     countLetter = 0
     for wordOrder in lines:
          if wordOrder.lower() == target:
               break 
          else:
               countWord += 1
          for letterOrder in wordOrder:
               countLetter += 1   
     return (lines, countWord, countLetter)

#This checks if the rear space is twenty 
def isBackTwenty(countBackLetter, countBackWord, j, lines, target):
     lines.pop()
     countBackWord = 0
     passnum = j
     countBackLetter = 0
     for passnum in range(passnum, len(lines)):
          countBackWord += 1
          for letterBackOrder in lines[passnum]:
                countBackWord += 1  
     return (lines, countBackLetter, countBackWord)

if __name__ == '__main__':
     notKeyWord = []
     keyWord = []
     content = []
     isKeyWord = 0
     keyWord = readKeyWord()
     content, notKeyWord = readContent (keyWord)
     sortNotKeyWord(notKeyWord)
     x = 0
     contentIndex = []
     for lines in content:
         contentIndex.append([])
         for words in lines.split(" "):
              contentIndex[x].append(0)
         x += 1
     for words in notKeyWord:
          y = 0
          isIndexed = 0
          for lines in content:
              if isIndexed == 0:
                   z = 0
                   for passWords in lines.split(" "):
                       if passWords == words and contentIndex[y][z] != 1:
                            capitalization(contentIndex, y, z, words, lines)
                            isIndexed = 1
                            contentIndex[y][z] = 1
                       z += 1
              y += 1